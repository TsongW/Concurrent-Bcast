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
#include <strings.h>

#include "mpiimpl.h"
#include "mpi_init.h"

#if defined(CHANNEL_MRAIL) || defined(CHANNEL_PSM)
#include "coll_shmem.h"
#endif

/*
=== BEGIN_MPI_T_CVAR_INFO_BLOCK ===

categories:
    - name        : THREADS
      description : multi-threading cvars

cvars:
    - name        : MPIR_CVAR_ASYNC_PROGRESS
      category    : THREADS
      type        : boolean
      default     : false
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        If set to true, MPICH will initiate an additional thread to
        make asynchronous progress on all communication operations
        including point-to-point, collective, one-sided operations and
        I/O.  Setting this variable will automatically increase the
        thread-safety level to MPI_THREAD_MULTIPLE.  While this
        improves the progress semantics, it might cause a small amount
        of performance overhead for regular MPI operations.  The user
        is encouraged to leave one or more hardware threads vacant in
        order to prevent contention between the application threads
        and the progress thread(s).  The impact of oversubscription is
        highly system dependent but may be substantial in some cases,
        hence this recommendation.

    - name        : MPIR_CVAR_DEFAULT_THREAD_LEVEL
      category    : THREADS
      type        : string
      default     : "MPI_THREAD_SINGLE"
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        Sets the default thread level to use when using MPI_INIT. This variable
        is case-insensitive.

=== END_MPI_T_CVAR_INFO_BLOCK ===
*/

/* -- Begin Profiling Symbol Block for routine MPI_Init */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Init = PMPI_Init
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Init  MPI_Init
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Init as PMPI_Init
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Init(int *argc, char ***argv) __attribute__((weak,alias("PMPI_Init")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Init
#define MPI_Init PMPI_Init

/* Fortran logical values. extern'd in mpiimpl.h */
/* MPI_Fint MPIR_F_TRUE, MPIR_F_FALSE; */

/* Any internal routines can go here.  Make them static if possible */

/* must go inside this #ifdef block to prevent duplicate storage on darwin */
int MPIR_async_thread_initialized = 0;
#endif

#undef FUNCNAME
#define FUNCNAME MPI_Init

/*@
   MPI_Init - Initialize the MPI execution environment

Input Parameters:
+  argc - Pointer to the number of arguments 
-  argv - Pointer to the argument vector

Thread and Signal Safety:
This routine must be called by one thread only.  That thread is called
the `main thread` and must be the thread that calls 'MPI_Finalize'.

Notes:
   The MPI standard does not say what a program can do before an 'MPI_INIT' or
   after an 'MPI_FINALIZE'.  In the MPICH implementation, you should do
   as little as possible.  In particular, avoid anything that changes the
   external state of the program, such as opening files, reading standard
   input or writing to standard output.

Notes for C:
    As of MPI-2, 'MPI_Init' will accept NULL as input parameters. Doing so
    will impact the values stored in 'MPI_INFO_ENV'.

Notes for Fortran:
The Fortran binding for 'MPI_Init' has only the error return
.vb
    subroutine MPI_INIT( ierr )
    integer ierr
.ve

.N Errors
.N MPI_SUCCESS
.N MPI_ERR_INIT

.seealso: MPI_Init_thread, MPI_Finalize
@*/
int MPI_Init( int *argc, char ***argv )
{
    static const char FCNAME[] = "MPI_Init";
    int mpi_errno = MPI_SUCCESS;
    int rc ATTRIBUTE((unused));
    int threadLevel, provided;
    MPID_MPI_INIT_STATE_DECL(MPID_STATE_MPI_INIT);

    /* Handle mpich_state in case of Re-init */
    if (OPA_load_int(&MPIR_Process.mpich_state) == MPICH_POST_FINALIZED) {
        OPA_store_int(&MPIR_Process.mpich_state, MPICH_PRE_INIT);
    }
    rc = MPID_Wtime_init();
#ifdef USE_DBG_LOGGING
    MPIU_DBG_PreInit( argc, argv, rc );
#endif

    MPID_MPI_INIT_FUNC_ENTER(MPID_STATE_MPI_INIT);
#if defined(CHANNEL_PSM)
    MV2_Read_env_vars();
#endif /* defined(CHANNEL_PSM) */

#   ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            if (OPA_load_int(&MPIR_Process.mpich_state) != MPICH_PRE_INIT) {
                mpi_errno = MPIR_Err_create_code( MPI_SUCCESS, MPIR_ERR_RECOVERABLE, FCNAME, __LINE__, MPI_ERR_OTHER,
						  "**inittwice", NULL );
	    }
            if (mpi_errno) goto fn_fail;
        }
        MPID_END_ERROR_CHECKS;
    }
#   endif /* HAVE_ERROR_CHECKING */

    /* ... body of routine ... */

    /* Temporarily disable thread-safety.  This is needed because the
     * mutexes are not initialized yet, and we don't want to
     * accidentally use them before they are initialized.  We will
     * reset this value once it is properly initialized. */
#if defined MPICH_IS_THREADED
    MPIR_ThreadInfo.isThreaded = 0;
#endif /* MPICH_IS_THREADED */

    MPIR_T_env_init();

    if (!strcasecmp(MPIR_CVAR_DEFAULT_THREAD_LEVEL, "MPI_THREAD_MULTIPLE"))
        threadLevel = MPI_THREAD_MULTIPLE;
    else if (!strcasecmp(MPIR_CVAR_DEFAULT_THREAD_LEVEL, "MPI_THREAD_SERIALIZED"))
        threadLevel = MPI_THREAD_SERIALIZED;
    else if (!strcasecmp(MPIR_CVAR_DEFAULT_THREAD_LEVEL, "MPI_THREAD_FUNNELED"))
        threadLevel = MPI_THREAD_FUNNELED;
    else if (!strcasecmp(MPIR_CVAR_DEFAULT_THREAD_LEVEL, "MPI_THREAD_SINGLE"))
        threadLevel = MPI_THREAD_SINGLE;
    else {
        MPL_error_printf("Unrecognized thread level %s\n", MPIR_CVAR_DEFAULT_THREAD_LEVEL);
        exit(1);
    }

    /* If the user requested for asynchronous progress, request for
     * THREAD_MULTIPLE. */
    if (MPIR_CVAR_ASYNC_PROGRESS)
        threadLevel = MPI_THREAD_MULTIPLE;

    mpi_errno = MPIR_Init_thread( argc, argv, threadLevel, &provided );
    if (mpi_errno != MPI_SUCCESS) goto fn_fail;

    if (MPIR_CVAR_ASYNC_PROGRESS) {
        if (provided == MPI_THREAD_MULTIPLE) {
            mpi_errno = MPIR_Init_async_thread();
            if (mpi_errno) goto fn_fail;

            MPIR_async_thread_initialized = 1;
        }
        else {
            printf("WARNING: No MPI_THREAD_MULTIPLE support (needed for async progress)\n");
        }
    }

#if defined(CHANNEL_MRAIL_GEN2) || defined(CHANNEL_PSM)
    /* initialize the two level communicator for MPI_COMM_WORLD  */
    if (mv2_use_osu_collectives && 
            mv2_enable_shmem_collectives) {

       MPID_Comm *comm_ptr = NULL;
       MPID_Comm_get_ptr(MPI_COMM_WORLD, comm_ptr);
       int flag=0; 
       PMPI_Comm_test_inter(comm_ptr->handle, &flag);

       if(flag == 0 && comm_ptr->dev.ch.shmem_coll_ok == 0 &&
               comm_ptr->local_size < mv2_two_level_comm_early_init_threshold &&
               check_split_comm(pthread_self())) { 

            disable_split_comm(pthread_self());
            mpi_errno = create_2level_comm(comm_ptr->handle, comm_ptr->local_size, comm_ptr->rank);
            if(mpi_errno) {
               MPIR_ERR_POP(mpi_errno);
            }
            enable_split_comm(pthread_self());
            if(mpi_errno) {
               MPIR_ERR_POP(mpi_errno);
            }
       } 
    }
#endif /*defined(CHANNEL_MRAIL_GEN2) || defined(CHANNEL_PSM)*/

    /************************** Added by Mehran ***********************/
    char *s_value, *o_value, *t_value, *sml_value, *c_value, *cb_value, *ob_value;
    if ((s_value = getenv("SECURITY_APPROACH")) != NULL) {
        security_approach = (atoi(s_value));
    }
    overlap_decryption = 0;
    if ((o_value = getenv("OVERLAP_DECRYPTION")) != NULL) {
        overlap_decryption = (atoi(o_value));
    }
    allocated_shmem = 0;
    if ((t_value = getenv("MV2_INTER_ALLGATHER_TUNING")) != NULL) {
        int alg = (atoi(t_value));
        if(alg==14 || alg ==18 || alg==20){
            allocated_shmem = 1;
            if(security_approach==2){
                allocated_shmem = 2;
            }
            init_shmem();
        }
    }
    shmem_leaders = 1;
    if ((sml_value = getenv("SHMEM_LEADERS")) != NULL) {
        shmem_leaders = (atoi(sml_value));
    }
    o_bruck2 = 0;
    if ((ob_value = getenv("O_BRUCK2")) != NULL) {
        o_bruck2 = (atoi(ob_value));
    }

    concurrent_comm = 0;
    if ((c_value = getenv("CONCURRENT_COMM")) != NULL) {
        concurrent_comm = (atoi(c_value));
    }
    concurrent_bcast = 0;
    if ((cb_value = getenv("CONCURRENT_BCAST")) != NULL) {
        concurrent_bcast = (atoi(cb_value));
    }

    if (concurrent_comm == 1){
        MPID_Comm *comm_ptr = NULL;
        MPID_Comm_get_ptr(MPI_COMM_WORLD, comm_ptr);
        mpi_errno = create_concurrent_comm(comm_ptr->handle, comm_ptr->local_size, comm_ptr->rank);
        if(mpi_errno) {
            MPIR_ERR_POP(mpi_errno);
        }
    }
    /******************************************************************/
    /* ... end of body of routine ... */
    MPID_MPI_INIT_FUNC_EXIT(MPID_STATE_MPI_INIT);
    return mpi_errno;

  fn_fail:
    /* --BEGIN ERROR HANDLING-- */
#   ifdef HAVE_ERROR_REPORTING
    {
	mpi_errno = MPIR_Err_create_code(
	    mpi_errno, MPIR_ERR_RECOVERABLE, FCNAME, __LINE__, MPI_ERR_OTHER, 
	    "**mpi_init", "**mpi_init %p %p", argc, argv);
    }
#   endif
    mpi_errno = MPIR_Err_return_comm( 0, FCNAME, mpi_errno );
    return mpi_errno;
    /* --END ERROR HANDLING-- */
}



int create_concurrent_comm (MPI_Comm comm, int size, int my_rank)
{
    static const char FCNAME[] = "create_concurrent_comm";
    int mpi_errno = MPI_SUCCESS;
    MPID_Comm* comm_ptr = NULL;
    //printf("%d is in create_concurrent_comm\n", my_rank);
    MPID_Comm_get_ptr( comm, comm_ptr );
    if (size <= 1) {
        return mpi_errno;
    }

    
    comm_ptr->dev.ch.concurrent_comm =MPI_COMM_NULL;
    
    MPID_Comm* shmem_commptr;
    MPI_Comm shmem_comm = comm_ptr->dev.ch.shmem_comm;
    MPID_Comm_get_ptr(shmem_comm, shmem_commptr);
    
    /* get our rank and the size of this communicator */
    int local_rank = shmem_commptr->rank;


    mpi_errno = PMPI_Comm_split(comm, local_rank, my_rank, &(comm_ptr->dev.ch.concurrent_comm));
    if(mpi_errno) {
       MPIR_ERR_POP(mpi_errno);
    }

    return (mpi_errno);
    fn_fail:
        mpi_errno = MPIR_Err_return_comm( 0, FCNAME, mpi_errno );

    return (mpi_errno);
}








int init_shmem(){
    static const char FCNAME[] = "init_shmem";
    int mpi_errno = MPI_SUCCESS;
    int security_approach, overlap_decryption;
    //printf("Hello from init_shmem\n");
    MPID_Comm *comm_ptr = NULL;
    MPID_Comm_get_ptr(MPI_COMM_WORLD, comm_ptr);
    MPID_Comm *shmem_comm_ptr = NULL;
    MPID_Comm_get_ptr(comm_ptr->dev.ch.shmem_comm, shmem_comm_ptr);
    
    //TODO: Allocate Shmem
    size_t shmem_size = (comm_ptr->local_size) * 4 * 1024 *1024;
    size_t ciphertext_shmem_size = (comm_ptr->local_size) * (1024 * 1024 * 4 + 16 + 12);
    shmem_key = 77877;
    ciphertext_shmem_key = 54821;
    

    if(shmem_comm_ptr->rank == 0){
        
        shmid = shmget(shmem_key, shmem_size, IPC_CREAT | 0666);

        if(allocated_shmem==2){
            ciphertext_shmid = shmget(ciphertext_shmem_key, ciphertext_shmem_size, IPC_CREAT | 0666);

        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(shmem_comm_ptr->rank > 0){
        shmid = shmget(shmem_key, shmem_size, 0666);

        if(allocated_shmem==2){
            ciphertext_shmid = shmget(ciphertext_shmem_key, ciphertext_shmem_size, 0666);

        }
    }
    
    if (shmid < 0) {
        printf("%s",strerror(errno));
        printf("ERROR 1\n");
        goto fn_fail;
    }
    
    // attach shared memory 

    shmem_buffer = (void *) shmat(shmid, NULL, 0);
    if (shmem_buffer == (void *) -1) {
        printf("ERROR 2\n");
        goto fn_fail;
    }
    if(allocated_shmem==2){
        ciphertext_shmem_buffer = (void *) shmat(ciphertext_shmid, NULL, 0);
        if (ciphertext_shmem_buffer == (void *) -1) {
            printf("ERROR 3\n");
            goto fn_fail;
        }

    }

    return mpi_errno;
    
    fn_fail:
        mpi_errno = MPIR_Err_return_comm( 0, FCNAME, mpi_errno );
    
    return mpi_errno;
    
}
