/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

/* Copyright (c) 2001-2019, The Ohio State University. All rights
 * reserved.
 *
 * This file is part of the MVAPICH2 software package developed by the
 * team members of The Ohio State University's Network-Based Computing
 * Laboratory (NBCL), headed by Professor Dhabaleswar K. (DK) Panda.
 *
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level MVAPICH2 directory.
 *
 */

/* style: allow:fprintf:1 sig:0 */

#include "mpiimpl.h"
#include "mpi_init.h"

#if (defined(CHANNEL_MRAIL)||defined(CHANNEL_PSM))
#include "coll_shmem.h"
#endif

/*
=== BEGIN_MPI_T_CVAR_INFO_BLOCK ===

categories:
    - name        : DEVELOPER
      description : useful for developers working on MPICH itself

cvars:
    - name        : MPIR_CVAR_MEMDUMP
      category    : DEVELOPER
      type        : boolean
      default     : true
      class       : device
      verbosity   : MPI_T_VERBOSITY_MPIDEV_DETAIL
      scope       : MPI_T_SCOPE_LOCAL
      description : >-
        If true, list any memory that was allocated by MPICH and that
        remains allocated when MPI_Finalize completes.

=== END_MPI_T_CVAR_INFO_BLOCK ===
*/

/* -- Begin Profiling Symbol Block for routine MPI_Finalize */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Finalize = PMPI_Finalize
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Finalize  MPI_Finalize
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Finalize as PMPI_Finalize
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Finalize(void) __attribute__((weak,alias("PMPI_Finalize")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Finalize
#define MPI_Finalize PMPI_Finalize

/* Any internal routines can go here.  Make them static if possible */

/* The following routines provide a callback facility for modules that need 
   some code called on exit.  This method allows us to avoid forcing 
   MPI_Finalize to know the routine names a priori.  Any module that wants to 
   have a callback calls MPIR_Add_finalize( routine, extra, priority ).
   
 */
PMPI_LOCAL void MPIR_Call_finalize_callbacks( int, int );
typedef struct Finalize_func_t {
    int (*f)( void * );      /* The function to call */
    void *extra_data;        /* Data for the function */
    int  priority;           /* priority is used to control the order
				in which the callbacks are invoked */
} Finalize_func_t;
/* When full debugging is enabled, each MPI handle type has a finalize handler
   installed to detect unfreed handles.  */
#define MAX_FINALIZE_FUNC 64
static Finalize_func_t fstack[MAX_FINALIZE_FUNC];
static int fstack_sp = 0;
static int fstack_max_priority = 0;

void MPIR_Add_finalize( int (*f)( void * ), void *extra_data, int priority )
{
    /* --BEGIN ERROR HANDLING-- */
    if (fstack_sp >= MAX_FINALIZE_FUNC) {
	/* This is a little tricky.  We may want to check the state of
	   MPIR_Process.mpich_state to decide how to signal the error */
	(void)MPL_internal_error_printf( "overflow in finalize stack! "
		"Is MAX_FINALIZE_FUNC too small?\n" );
    if (OPA_load_int(&MPIR_Process.mpich_state) == MPICH_IN_INIT ||
        OPA_load_int(&MPIR_Process.mpich_state) == MPICH_POST_INIT)
    {
	    MPID_Abort( NULL, MPI_SUCCESS, 13, NULL );
	}
	else {
	    exit(1);
	}
    }
    /* --END ERROR HANDLING-- */
    fstack[fstack_sp].f            = f;
    fstack[fstack_sp].priority     = priority;
    fstack[fstack_sp++].extra_data = extra_data;

    if (priority > fstack_max_priority) 
	fstack_max_priority = priority;
}

/* Invoke the registered callbacks */
PMPI_LOCAL void MPIR_Call_finalize_callbacks( int min_prio, int max_prio )
{
    int i, j;

    if (max_prio > fstack_max_priority) max_prio = fstack_max_priority;
    for (j=max_prio; j>=min_prio; j--) {
	for (i=fstack_sp-1; i>=0; i--) {
	    if (fstack[i].f && fstack[i].priority == j) {
		fstack[i].f( fstack[i].extra_data );
		fstack[i].f = 0;
	    }
	}
    }
}
#else
#ifndef USE_WEAK_SYMBOLS
PMPI_LOCAL void MPIR_Call_finalize_callbacks( int, int );
#endif
#endif

/* Cleanup the registered callbacks */
void MPIR_Call_cleanup_finalize_callbacks( void )
{
    memset(fstack, 0, MAX_FINALIZE_FUNC*sizeof(Finalize_func_t));
    fstack_sp = 0;
    fstack_max_priority = 0;
}

#undef FUNCNAME
#define FUNCNAME MPI_Finalize

/*@
   MPI_Finalize - Terminates MPI execution environment

   Notes:
   All processes must call this routine before exiting.  The number of
   processes running `after` this routine is called is undefined; 
   it is best not to perform much more than a 'return rc' after calling
   'MPI_Finalize'.

Thread and Signal Safety:
The MPI standard requires that 'MPI_Finalize' be called `only` by the same 
thread that initialized MPI with either 'MPI_Init' or 'MPI_Init_thread'.

.N Fortran

.N Errors
.N MPI_SUCCESS
@*/
int MPI_Finalize( void )
{
#ifdef ENABLE_SCR
    PRINT_DEBUG( DEBUG_CR_verbose, "Calling SCR_Finalize\n");
    SCR_Finalize();
#endif

    static const char FCNAME[] = "MPI_Finalize";
    int mpi_errno = MPI_SUCCESS;
#if defined(HAVE_USLEEP) && defined(USE_COVERAGE)
    int rank=0;
#endif
    MPID_MPI_FINALIZE_STATE_DECL(MPID_STATE_MPI_FINALIZE);

    MPIR_ERRTEST_INITIALIZED_ORDIE();

    /* Note: Only one thread may ever call MPI_Finalize (MPI_Finalize may
       be called at most once in any program) */
    MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    MPID_MPI_FINALIZE_FUNC_ENTER(MPID_STATE_MPI_FINALIZE);
    
    /* ... body of routine ... */

    /* If the user requested for asynchronous progress, we need to
     * shutdown the progress thread */
    if (MPIR_async_thread_initialized) {
        mpi_errno = MPIR_Finalize_async_thread();
        if (mpi_errno) goto fn_fail;
    }
    
#if defined(HAVE_USLEEP) && defined(USE_COVERAGE)
    /* We need to get the rank before freeing MPI_COMM_WORLD */
    rank = MPIR_Process.comm_world->rank;
#endif    

    /* Remove the attributes, executing the attribute delete routine.
       Do this only if the attribute functions are defined. */ 
    /* The standard (MPI-2, section 4.8) says that the attributes on 
       MPI_COMM_SELF are deleted before almost anything else happens */
    /* Note that the attributes need to be removed from the communicators 
       so that they aren't freed twice. (The communicators are released
       in MPID_Finalize) */
    if (MPIR_Process.attr_free && MPIR_Process.comm_self->attributes) {
        mpi_errno = MPIR_Process.attr_free( MPI_COMM_SELF,
					    &MPIR_Process.comm_self->attributes);
        if (mpi_errno) MPIR_ERR_POP(mpi_errno);
	MPIR_Process.comm_self->attributes = 0;
    }
    if (MPIR_Process.attr_free && MPIR_Process.comm_world->attributes) {
        mpi_errno = MPIR_Process.attr_free( MPI_COMM_WORLD, 
                                            &MPIR_Process.comm_world->attributes);
        if (mpi_errno) MPIR_ERR_POP(mpi_errno);
	MPIR_Process.comm_world->attributes = 0;
    }

    



    /* 
     * Now that we're finalizing, we need to take control of the error handlers
     * At this point, we will release any user-defined error handlers on 
     * comm self and comm world
     */
    if (MPIR_Process.comm_world->errhandler && 
	! (HANDLE_GET_KIND(MPIR_Process.comm_world->errhandler->handle) == 
	   HANDLE_KIND_BUILTIN) ) {
	int in_use;
	MPIR_Errhandler_release_ref( MPIR_Process.comm_world->errhandler,
				     &in_use);
	if (!in_use) {
	    MPIU_Handle_obj_free( &MPID_Errhandler_mem, 
				  MPIR_Process.comm_world->errhandler );
	}
        /* always set to NULL to avoid a double-release later in finalize */
        MPIR_Process.comm_world->errhandler = NULL;
    }
    if (MPIR_Process.comm_self->errhandler && 
	! (HANDLE_GET_KIND(MPIR_Process.comm_self->errhandler->handle) == 
	   HANDLE_KIND_BUILTIN) ) {
	int in_use;
	MPIR_Errhandler_release_ref( MPIR_Process.comm_self->errhandler,
				     &in_use);
	if (!in_use) {
	    MPIU_Handle_obj_free( &MPID_Errhandler_mem, 
				  MPIR_Process.comm_self->errhandler );
	}
        /* always set to NULL to avoid a double-release later in finalize */
        MPIR_Process.comm_self->errhandler = NULL;
    }

    /* FIXME: Why is this not one of the finalize callbacks?.  Do we need
       pre and post MPID_Finalize callbacks? */
    MPIU_Timer_finalize();

    /* Call the high-priority callbacks */
    MPIR_Call_finalize_callbacks( MPIR_FINALIZE_CALLBACK_PRIO+1, 
				  MPIR_FINALIZE_CALLBACK_MAX_PRIO );

    /* Signal the debugger that we are about to exit. */
    /* FIXME: Should this also be a finalize callback? */
#ifdef HAVE_DEBUGGER_SUPPORT
    MPIR_DebuggerSetAborting( (char *)0 );
#endif

#ifdef _OSU_MVAPICH_
    /* Check to see if shmem_collectives were enabled. If yes, the
    specific entries need to be freed. */
    MPID_Comm *comm_ptr = NULL;
    MPIR_Errflag_t errflag = MPIR_ERR_NONE;
    MPID_Comm_get_ptr( MPI_COMM_WORLD, comm_ptr );
    mpi_errno = MPIR_Barrier_impl(comm_ptr, &errflag);
    if (mpi_errno) { 
             MPIR_ERR_POP(mpi_errno); 
    }
#if defined(CHANNEL_MRAIL_GEN2)
    char *value = NULL;
    if ((value = getenv("MV2_SHOW_RUNLOG_INFO")) != NULL) {
        mv2_show_runlog_level = atoi(value);
        if (mv2_show_runlog_level) {
            mv2_show_runlog_info(mv2_show_runlog_level);
        }
    }
#endif /* defined(CHANNEL_MRAIL_GEN2) */
#ifndef CHANNEL_PSM
    if( MPIR_Process.comm_world->dev.ch.shmem_coll_ok == 1) {
        mpi_errno = free_2level_comm(MPIR_Process.comm_world);
        if (mpi_errno) { 
             MPIR_ERR_POP(mpi_errno); 
        }
    }
#endif /* !CHANNEL_PSM */
#endif /* _OSU_MVAPICH_ */

    /*********        Added by Mehran       **********/
    if(allocated_shmem==1){
        if (shmctl(shmid, IPC_RMID, 0) != 0) {
            fprintf(stderr, "Failed to mark shm for removal\n");
        }
    }else if(allocated_shmem==2){
        
        if (shmctl(shmid, IPC_RMID, 0) != 0) {
            fprintf(stderr, "Failed to mark shm for removal\n");
        }
        
        if (shmctl(ciphertext_shmid, IPC_RMID, 0) != 0) {
            fprintf(stderr, "Failed to mark ciphertext_shm for removal\n");
        }
    }
    /**************************************************/
    
    mpi_errno = MPID_Finalize();
    if (mpi_errno) {
	MPIR_ERR_POP(mpi_errno);
    }
#ifdef CHANNEL_MRAIL
    mv2_free_dummy_request();
#endif

    /* Call the low-priority (post Finalize) callbacks */
    MPIR_Call_finalize_callbacks( 0, MPIR_FINALIZE_CALLBACK_PRIO-1 );
    MPIR_Call_cleanup_finalize_callbacks();

    /* At this point, if there has been a failure, exit before 
       completing the finalize */
    if (mpi_errno != MPI_SUCCESS) goto fn_fail;

    /* Users did not call MPI_T_init_thread(), so we free memories allocated to
     * MPIR_T during MPI_Init here. Otherwise, free them in MPI_T_finalize() */
    if (!MPIR_T_is_initialized())
        MPIR_T_env_finalize();

    /* FIXME: Many of these debugging items could/should be callbacks, 
       added to the finalize callback list */
    /* FIXME: the memory tracing code block should be a finalize callback */
    /* If memory debugging is enabled, check the memory here, after all
       finalize callbacks */

    MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    OPA_store_int(&MPIR_Process.mpich_state, MPICH_POST_FINALIZED);

#if defined(MPICH_IS_THREADED)
    MPIR_Thread_CS_Finalize();
#endif

    /* We place the memory tracing at the very end because any of the other
       steps may have allocated memory that they still need to release*/
#ifdef USE_MEMORY_TRACING
    /* FIXME: We'd like to arrange for the mem dump output to
       go to separate files or to be sorted by rank (note that
       the rank is at the head of the line) */
    {
	if (MPIR_CVAR_MEMDUMP) {
	    /* The second argument is the min id to print; memory allocated 
	       after MPI_Init is given an id of one.  This allows us to
	       ignore, if desired, memory leaks in the MPID_Init call */
	    MPIU_trdump( (void *)0, -1 );
	}
    }
#endif

#if defined(HAVE_USLEEP) && defined(USE_COVERAGE)
    /* If performing coverage analysis, make each process sleep for
       rank * 100 ms, to give time for the coverage tool to write out
       any files.  It would be better if the coverage tool and runtime 
       was more careful about file updates, though the lack of OS support
       for atomic file updates makes this harder. */
    /* 
       On some systems, a 0.1 second delay appears to be too short for 
       the file system.  This code allows the use of the environment
       variable MPICH_FINALDELAY, which is the delay in milliseconds.
       It must be an integer value.
     */
    {
	int microseconds = 100000;
	char *delayStr = getenv( "MPICH_FINALDELAY" );
	if (delayStr) {
	    /* Because this is a maintainer item, we won't check for 
	       errors in the delayStr */
	    microseconds = 1000 * atoi( delayStr );
	}
	usleep( rank * microseconds );
    }
#endif

    /* ... end of body of routine ... */
  fn_exit:
    MPID_MPI_FINALIZE_FUNC_EXIT(MPID_STATE_MPI_FINALIZE);
    return mpi_errno;

  fn_fail:
    /* --BEGIN ERROR HANDLING-- */
#   ifdef HAVE_ERROR_CHECKING
    {
	mpi_errno = MPIR_Err_create_code(mpi_errno, MPIR_ERR_RECOVERABLE, 
			FCNAME, __LINE__, MPI_ERR_OTHER, "**mpi_finalize", 0);
    }
#   endif
    mpi_errno = MPIR_Err_return_comm( 0, FCNAME, mpi_errno );
    if (OPA_load_int(&MPIR_Process.mpich_state) < MPICH_POST_FINALIZED) {
        MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    }
    goto fn_exit;
    /* --END ERROR HANDLING-- */
}
