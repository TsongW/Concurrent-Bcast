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

#include "mpiimpl.h"
#include "mpicomm.h"
#include "mpiinfo.h"    /* MPIU_Info_free */

#include "mpl_utlist.h"
#include "mpiu_uthash.h"

#if defined(CHANNEL_MRAIL) || defined(CHANNEL_PSM)
#include "coll_shmem.h"
#endif /* #if defined(CHANNEL_MRAIL) || defined(CHANNEL_PSM) */ 


/* This is the utility file for comm that contains the basic comm items
   and storage management */
#ifndef MPID_COMM_PREALLOC
#define MPID_COMM_PREALLOC 8
#endif

/* Preallocated comm objects */
/* initialized in initthread.c */
MPID_Comm MPID_Comm_builtin[MPID_COMM_N_BUILTIN] = { {0} };
MPID_Comm MPID_Comm_direct[MPID_COMM_PREALLOC] = { {0} };

MPIU_Object_alloc_t MPID_Comm_mem = {
    0,
    0,
    0,
    0,
    MPID_COMM,
    sizeof(MPID_Comm),
    MPID_Comm_direct,
    MPID_COMM_PREALLOC
};

/* Communicator creation functions */
struct MPID_CommOps *MPID_Comm_fns = NULL;
struct MPIR_Comm_hint_fn_elt {
    char name[MPI_MAX_INFO_KEY];
    MPIR_Comm_hint_fn_t fn;
    void *state;
    UT_hash_handle hh;
};
static struct MPIR_Comm_hint_fn_elt *MPID_hint_fns = NULL;

/* FIXME :
   Reusing context ids can lead to a race condition if (as is desirable)
   MPI_Comm_free does not include a barrier.  Consider the following:
   Process A frees the communicator.
   Process A creates a new communicator, reusing the just released id
   Process B sends a message to A on the old communicator.
   Process A receives the message, and believes that it belongs to the
   new communicator.
   Process B then cancels the message, and frees the communicator.

   The likelyhood of this happening can be reduced by introducing a gap
   between when a context id is released and when it is reused.  An alternative
   is to use an explicit message (in the implementation of MPI_Comm_free)
   to indicate that a communicator is being freed; this will often require
   less communication than a barrier in MPI_Comm_free, and will ensure that
   no messages are later sent to the same communicator (we may also want to
   have a similar check when building fault-tolerant versions of MPI).
 */

/* Zeroes most non-handle fields in a communicator, as well as initializing any
 * other special fields, such as a per-object mutex.  Also defaults the
 * reference count to 1, under the assumption that the caller holds a reference
 * to it.
 *
 * !!! The resulting struct is _not_ ready for communication !!! */
int MPIR_Comm_init(MPID_Comm * comm_p)
{
    int mpi_errno = MPI_SUCCESS;

    MPIU_Object_set_ref(comm_p, 1);

    /* initialize local and remote sizes to -1 to allow other parts of
     * the stack to detect errors more easily */
    comm_p->local_size = -1;
    comm_p->remote_size = -1;

    /* Clear many items (empty means to use the default; some of these
     * may be overridden within the upper-level communicator initialization) */
    comm_p->errhandler = NULL;
    comm_p->attributes = NULL;
    comm_p->remote_group = NULL;
    comm_p->local_group = NULL;
    comm_p->coll_fns = NULL;
    comm_p->topo_fns = NULL;
    comm_p->name[0] = '\0';
    comm_p->info = NULL;

    comm_p->hierarchy_kind = MPID_HIERARCHY_FLAT;
    comm_p->node_comm = NULL;
    comm_p->node_roots_comm = NULL;
    comm_p->intranode_table = NULL;
    comm_p->internode_table = NULL;
#ifdef _OSU_MVAPICH_
    comm_p->dev.ch.shmem_coll_count = 0; 
    comm_p->dev.ch.allgather_coll_count = 0; 
    comm_p->dev.ch.allreduce_coll_count = 0; 
    comm_p->dev.ch.bcast_coll_count = 0;
    comm_p->dev.ch.scatter_coll_count = 0;
    comm_p->dev.ch.shmem_coll_ok = 0;
    comm_p->dev.ch.allgather_comm_ok = 0;
    comm_p->dev.ch.is_global_block  = 0;
    /* We are yet to call create_2level_comm on this new intra-communicator
     * We should make sure that shared-mem collectives do not get used
     * with this communicator */ 
    comm_p->dev.ch.leader_comm=MPI_COMM_NULL;
    comm_p->dev.ch.shmem_comm=MPI_COMM_NULL;
    comm_p->dev.ch.allgather_comm=MPI_COMM_NULL;
    comm_p->dev.ch.intra_node_done = 0;
#if defined(_MCST_SUPPORT_)
    comm_p->dev.ch.is_mcast_ok = 0;
    comm_p->dev.ch.bcast_info = NULL;
#endif
    comm_p->dev.ch.shmem_info = NULL;
    comm_p->dev.ch.leader_map  = NULL;
    comm_p->dev.ch.leader_rank = NULL;
    comm_p->dev.ch.node_disps  = NULL;
    comm_p->dev.ch.rank_list   = NULL;

    comm_p->dev.ch.socket_size=0;
    comm_p->dev.ch.use_intra_sock_comm=0;
    comm_p->dev.ch.is_socket_uniform=0;
    comm_p->dev.ch.tried_to_create_leader_shmem=0;
    comm_p->dev.ch.intra_sock_comm=MPI_COMM_NULL;
    comm_p->dev.ch.intra_sock_leader_comm=MPI_COMM_NULL;
    comm_p->dev.ch.global_sock_leader_comm=MPI_COMM_NULL;

#if ENABLE_PVAR_MV2
    comm_p->sub_comm_counters = NULL;
    comm_p->sub_comm_timers = NULL;
#endif

#endif /* _OSU_MVAPICH_ */

    /* abstractions bleed a bit here... :(*/
    comm_p->next_sched_tag = MPIR_FIRST_NBC_TAG;

    /* Initialize the revoked flag as false */
    comm_p->revoked = 0;
    comm_p->mapper_head = NULL;
    comm_p->mapper_tail = NULL;

    /* Fields not set include context_id, remote and local size, and
     * kind, since different communicator construction routines need
     * different values */
    return mpi_errno;
}


/*
    Create a communicator structure and perform basic initialization
    (mostly clearing fields and updating the reference count).
 */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_create
#undef FCNAME
#define FCNAME "MPIR_Comm_create"
int MPIR_Comm_create(MPID_Comm ** newcomm_ptr)
{
    int mpi_errno = MPI_SUCCESS;
    MPID_Comm *newptr;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_CREATE);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_CREATE);

    newptr = (MPID_Comm *) MPIU_Handle_obj_alloc(&MPID_Comm_mem);
    MPIR_ERR_CHKANDJUMP(!newptr, mpi_errno, MPI_ERR_OTHER, "**nomem");

    *newcomm_ptr = newptr;

    mpi_errno = MPIR_Comm_init(newptr);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

    /* Insert this new communicator into the list of known communicators.
     * Make this conditional on debugger support to match the test in
     * MPIR_Comm_release . */
    MPIR_COMML_REMEMBER(newptr);

  fn_fail:
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_CREATE);

    return mpi_errno;
}

/* Create a local intra communicator from the local group of the
   specified intercomm. */
/* FIXME this is an alternative constructor that doesn't use MPIR_Comm_create! */
#undef FUNCNAME
#define FUNCNAME MPIR_Setup_intercomm_localcomm
#undef FCNAME
#define FCNAME "MPIR_Setup_intercomm_localcomm"
int MPIR_Setup_intercomm_localcomm(MPID_Comm * intercomm_ptr)
{
    MPID_Comm *localcomm_ptr;
    int mpi_errno = MPI_SUCCESS;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_SETUP_INTERCOMM_LOCALCOMM);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_SETUP_INTERCOMM_LOCALCOMM);

    localcomm_ptr = (MPID_Comm *) MPIU_Handle_obj_alloc(&MPID_Comm_mem);
    MPIR_ERR_CHKANDJUMP(!localcomm_ptr, mpi_errno, MPI_ERR_OTHER, "**nomem");

    /* get sensible default values for most fields (usually zeros) */
    mpi_errno = MPIR_Comm_init(localcomm_ptr);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

    /* use the parent intercomm's recv ctx as the basis for our ctx */
    localcomm_ptr->recvcontext_id =
        MPID_CONTEXT_SET_FIELD(IS_LOCALCOMM, intercomm_ptr->recvcontext_id, 1);
    localcomm_ptr->context_id = localcomm_ptr->recvcontext_id;

    MPIU_DBG_MSG_FMT(COMM, TYPICAL,
                     (MPIU_DBG_FDEST,
                      "setup_intercomm_localcomm ic=%p ic->context_id=%d ic->recvcontext_id=%d lc->recvcontext_id=%d",
                      intercomm_ptr, intercomm_ptr->context_id, intercomm_ptr->recvcontext_id,
                      localcomm_ptr->recvcontext_id));

    /* Save the kind of the communicator */
    localcomm_ptr->comm_kind = MPID_INTRACOMM;

    /* Set the sizes and ranks */
    localcomm_ptr->remote_size = intercomm_ptr->local_size;
    localcomm_ptr->local_size = intercomm_ptr->local_size;
    localcomm_ptr->rank = intercomm_ptr->rank;

    MPIR_Comm_map_dup(localcomm_ptr, intercomm_ptr, MPIR_COMM_MAP_DIR_L2L);

    /* TODO More advanced version: if the group is available, dup it by
     * increasing the reference count instead of recreating it later */
    /* FIXME  : No coll_fns functions for the collectives */
    /* FIXME  : No local functions for the topology routines */

    intercomm_ptr->local_comm = localcomm_ptr;
#ifdef _OSU_MVAPICH_
    localcomm_ptr->dev.ch.shmem_coll_ok = 0;
    localcomm_ptr->dev.ch.is_global_block  = 0;
    localcomm_ptr->dev.ch.allgather_comm_ok = 0;
    localcomm_ptr->dev.ch.shmem_comm = MPI_COMM_NULL;
    localcomm_ptr->dev.ch.leader_comm = MPI_COMM_NULL;
    localcomm_ptr->dev.ch.allgather_comm = MPI_COMM_NULL;
    localcomm_ptr->dev.ch.intra_sock_comm=MPI_COMM_NULL;
    localcomm_ptr->dev.ch.intra_sock_leader_comm=MPI_COMM_NULL;
    localcomm_ptr->dev.ch.global_sock_leader_comm=MPI_COMM_NULL;
#endif /* _OSU_MVAPICH_ */


    /* sets up the SMP-aware sub-communicators and tables */
    mpi_errno = MPIR_Comm_commit(localcomm_ptr);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

  fn_fail:
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_SETUP_INTERCOMM_LOCALCOMM);

    return mpi_errno;
}

/* holds default collop "vtables" for _intracomms_, where
 * default[hierarchy_kind] is the pointer to the collop struct for that
 * hierarchy kind */
static struct MPID_Collops *default_collops[MPID_HIERARCHY_SIZE] = { NULL };

/* default for intercomms */
static struct MPID_Collops *ic_default_collops = NULL;
int mv2_coll_ops_initialized = FALSE;

#undef FUNCNAME
#define FUNCNAME cleanup_default_collops
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
static int cleanup_default_collops(void *unused)
{
    int i;
    for (i = 0; i < MPID_HIERARCHY_SIZE; ++i) {
        if (default_collops[i]) {
            MPIU_Assert(default_collops[i]->ref_count >= 1);
            if (--default_collops[i]->ref_count == 0)
                MPIU_Free(default_collops[i]);
            default_collops[i] = NULL;
        }
    }
    if (ic_default_collops) {
        MPIU_Assert(ic_default_collops->ref_count >= 1);
        if (--ic_default_collops->ref_count == 0)
            MPIU_Free(ic_default_collops);
    }
    mv2_coll_ops_initialized = FALSE;
    return MPI_SUCCESS;
}

#undef FUNCNAME
#define FUNCNAME init_default_collops
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
static int init_default_collops(void)
{
    int mpi_errno = MPI_SUCCESS;
    int i;
    struct MPID_Collops *ops = NULL;
    MPIU_CHKPMEM_DECL(MPID_HIERARCHY_SIZE + 1);

    /* first initialize the intracomms */
    for (i = 0; i < MPID_HIERARCHY_SIZE; ++i) {
        MPIU_CHKPMEM_CALLOC(ops, struct MPID_Collops *, sizeof(struct MPID_Collops), mpi_errno,
                            "default intracomm collops");
        ops->ref_count = 1;     /* force existence until finalize time */

        /* intracomm default defaults... */
        ops->Ibcast_sched = &MPIR_Ibcast_intra;
        ops->Ibarrier_sched = &MPIR_Ibarrier_intra;
        ops->Ireduce_sched = &MPIR_Ireduce_intra;
        ops->Ialltoall_sched = &MPIR_Ialltoall_intra;
        ops->Ialltoallv_sched = &MPIR_Ialltoallv_intra;
        ops->Ialltoallw_sched = &MPIR_Ialltoallw_intra;
        ops->Iallreduce_sched = &MPIR_Iallreduce_intra;
        ops->Igather_sched = &MPIR_Igather_intra;
        ops->Igatherv_sched = &MPIR_Igatherv;
        ops->Iscatter_sched = &MPIR_Iscatter_intra;
        ops->Iscatterv_sched = &MPIR_Iscatterv;
        ops->Ireduce_scatter_sched = &MPIR_Ireduce_scatter_intra;
        ops->Ireduce_scatter_block_sched = &MPIR_Ireduce_scatter_block_intra;
        ops->Iallgather_sched = &MPIR_Iallgather_intra;
        ops->Iallgatherv_sched = &MPIR_Iallgatherv_intra;
        ops->Iscan_sched = &MPIR_Iscan_rec_dbl;
        ops->Iexscan_sched = &MPIR_Iexscan;
        ops->Neighbor_allgather = &MPIR_Neighbor_allgather_default;
        ops->Neighbor_allgatherv = &MPIR_Neighbor_allgatherv_default;
        ops->Neighbor_alltoall = &MPIR_Neighbor_alltoall_default;
        ops->Neighbor_alltoallv = &MPIR_Neighbor_alltoallv_default;
        ops->Neighbor_alltoallw = &MPIR_Neighbor_alltoallw_default;
        ops->Ineighbor_allgather = &MPIR_Ineighbor_allgather_default;
        ops->Ineighbor_allgatherv = &MPIR_Ineighbor_allgatherv_default;
        ops->Ineighbor_alltoall = &MPIR_Ineighbor_alltoall_default;
        ops->Ineighbor_alltoallv = &MPIR_Ineighbor_alltoallv_default;
        ops->Ineighbor_alltoallw = &MPIR_Ineighbor_alltoallw_default;

        /* override defaults, such as for SMP */
        switch (i) {
        case MPID_HIERARCHY_FLAT:
            break;
        case MPID_HIERARCHY_PARENT:
            ops->Ibcast_sched = &MPIR_Ibcast_SMP;
            ops->Iscan_sched = &MPIR_Iscan_SMP;
            ops->Iallreduce_sched = &MPIR_Iallreduce_SMP;
            ops->Ireduce_sched = &MPIR_Ireduce_SMP;
            break;
        case MPID_HIERARCHY_NODE:
            break;
        case MPID_HIERARCHY_NODE_ROOTS:
            break;

            /* --BEGIN ERROR HANDLING-- */
        default:
            MPIU_Assertp(FALSE);
            break;
            /* --END ERROR HANDLING-- */
        }

        /* this is a default table, it's not overriding another table */
        ops->prev_coll_fns = NULL;

        default_collops[i] = ops;
    }

    /* now the intercomm table */
    {
        MPIU_CHKPMEM_CALLOC(ops, struct MPID_Collops *, sizeof(struct MPID_Collops), mpi_errno,
                            "default intercomm collops");
        ops->ref_count = 1;     /* force existence until finalize time */

        /* intercomm defaults */
        ops->Ibcast_sched = &MPIR_Ibcast_inter;
        ops->Ibarrier_sched = &MPIR_Ibarrier_inter;
        ops->Ireduce_sched = &MPIR_Ireduce_inter;
        ops->Ialltoall_sched = &MPIR_Ialltoall_inter;
        ops->Ialltoallv_sched = &MPIR_Ialltoallv_inter;
        ops->Ialltoallw_sched = &MPIR_Ialltoallw_inter;
        ops->Iallreduce_sched = &MPIR_Iallreduce_inter;
        ops->Igather_sched = &MPIR_Igather_inter;
        ops->Igatherv_sched = &MPIR_Igatherv;
        ops->Iscatter_sched = &MPIR_Iscatter_inter;
        ops->Iscatterv_sched = &MPIR_Iscatterv;
        ops->Ireduce_scatter_sched = &MPIR_Ireduce_scatter_inter;
        ops->Ireduce_scatter_block_sched = &MPIR_Ireduce_scatter_block_inter;
        ops->Iallgather_sched = &MPIR_Iallgather_inter;
        ops->Iallgatherv_sched = &MPIR_Iallgatherv_inter;
        /* scan and exscan are not valid for intercommunicators, leave them NULL */
        /* Ineighbor_all* routines are not valid for intercommunicators, leave
         * them NULL */

        /* this is a default table, it's not overriding another table */
        ops->prev_coll_fns = NULL;

        ic_default_collops = ops;
    }


    /* run after MPID_Finalize to permit collective usage during finalize */
    MPIR_Add_finalize(cleanup_default_collops, NULL, MPIR_FINALIZE_CALLBACK_PRIO - 1);

    MPIU_CHKPMEM_COMMIT();
  fn_exit:
    return mpi_errno;
    /* --BEGIN ERROR HANDLING-- */
  fn_fail:
    MPIU_CHKPMEM_REAP();
    goto fn_exit;
    /* --END ERROR HANDLING-- */
}

/* Initializes the coll_fns field of comm to a sensible default.  It may re-use
 * an existing structure, so any override by a lower level should _not_ change
 * any of the fields but replace the coll_fns object instead.
 *
 * NOTE: for now we only initialize nonblocking collective routines, since the
 * blocking collectives all contain fallback logic that correctly handles NULL
 * override functions. */
#undef FUNCNAME
#define FUNCNAME set_collops
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
static int set_collops(MPID_Comm * comm)
{
    int mpi_errno = MPI_SUCCESS;

    if (comm->coll_fns != NULL)
        goto fn_exit;

    if (unlikely(!mv2_coll_ops_initialized)) {
        mpi_errno = init_default_collops();
        if (mpi_errno)
            MPIR_ERR_POP(mpi_errno);

        mv2_coll_ops_initialized = TRUE;
    }

    if (comm->comm_kind == MPID_INTRACOMM) {
        /* FIXME MT what protects access to this structure and ic_default_collops? */
        comm->coll_fns = default_collops[comm->hierarchy_kind];
    }
    else {      /* intercomm */
        comm->coll_fns = ic_default_collops;
    }

    comm->coll_fns->ref_count++;

  fn_exit:
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

#undef FUNCNAME
#define FUNCNAME MPIR_Comm_map_irregular
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_map_irregular(MPID_Comm * newcomm, MPID_Comm * src_comm,
                            int *src_mapping, int src_mapping_size,
                            MPIR_Comm_map_dir_t dir, MPIR_Comm_map_t ** map)
{
    int mpi_errno = MPI_SUCCESS;
    MPIR_Comm_map_t *mapper;
    MPIU_CHKPMEM_DECL(3);
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_MAP_IRREGULAR);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_MAP_IRREGULAR);

    MPIU_CHKPMEM_MALLOC(mapper, MPIR_Comm_map_t *, sizeof(MPIR_Comm_map_t), mpi_errno, "mapper");

    mapper->type = MPIR_COMM_MAP_IRREGULAR;
    mapper->src_comm = src_comm;
    mapper->dir = dir;
    mapper->src_mapping_size = src_mapping_size;

    if (src_mapping) {
        mapper->src_mapping = src_mapping;
        mapper->free_mapping = 0;
    }
    else {
        MPIU_CHKPMEM_MALLOC(mapper->src_mapping, int *,
                            src_mapping_size * sizeof(int), mpi_errno, "mapper mapping");
        mapper->free_mapping = 1;
    }

    mapper->next = NULL;

    MPL_LL_APPEND(newcomm->mapper_head, newcomm->mapper_tail, mapper);

    if (map)
        *map = mapper;

  fn_exit:
    MPIU_CHKPMEM_COMMIT();
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_MAP_IRREGULAR);
    return mpi_errno;
  fn_fail:
    MPIU_CHKPMEM_REAP();
    goto fn_exit;
}

#undef FUNCNAME
#define FUNCNAME MPIR_Comm_map_dup
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_map_dup(MPID_Comm * newcomm, MPID_Comm * src_comm, MPIR_Comm_map_dir_t dir)
{
    int mpi_errno = MPI_SUCCESS;
    MPIR_Comm_map_t *mapper;
    MPIU_CHKPMEM_DECL(1);
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_MAP_DUP);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_MAP_DUP);

    MPIU_CHKPMEM_MALLOC(mapper, MPIR_Comm_map_t *, sizeof(MPIR_Comm_map_t), mpi_errno, "mapper");

    mapper->type = MPIR_COMM_MAP_DUP;
    mapper->src_comm = src_comm;
    mapper->dir = dir;

    mapper->next = NULL;

    MPL_LL_APPEND(newcomm->mapper_head, newcomm->mapper_tail, mapper);

  fn_exit:
    MPIU_CHKPMEM_COMMIT();
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_MAP_DUP);
    return mpi_errno;
  fn_fail:
    MPIU_CHKPMEM_REAP();
    goto fn_exit;
}


#undef FUNCNAME
#define FUNCNAME MPIR_Comm_map_free
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_map_free(MPID_Comm * comm)
{
    int mpi_errno = MPI_SUCCESS;
    MPIR_Comm_map_t *mapper, *tmp;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_MAP_FREE);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_MAP_FREE);

    for (mapper = comm->mapper_head; mapper;) {
        tmp = mapper->next;
        if (mapper->type == MPIR_COMM_MAP_IRREGULAR && mapper->free_mapping)
            MPIU_Free(mapper->src_mapping);
        MPIU_Free(mapper);
        mapper = tmp;
    }
    comm->mapper_head = NULL;

    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_MAP_FREE);
    return mpi_errno;
}

/* Provides a hook for the top level functions to perform some manipulation on a
   communicator just before it is given to the application level.

   For example, we create sub-communicators for SMP-aware collectives at this
   step. */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_commit
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_commit(MPID_Comm * comm)
{
    int mpi_errno = MPI_SUCCESS;
    int num_local = -1, num_external = -1;
    int local_rank = -1, external_rank = -1;
    int *local_procs = NULL, *external_procs = NULL;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_COMMIT);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_COMMIT);

#if ENABLE_PVAR_MV2
    extern int sub_comm_counter_idx;
    extern int sub_comm_timer_idx;
    comm->sub_comm_counters = (unsigned long long *)MPIU_Malloc(sub_comm_counter_idx * sizeof(unsigned long long));
    comm->sub_comm_timers = (pvar_timer_t *)MPIU_Malloc(sub_comm_timer_idx * sizeof(pvar_timer_t));
    int i = 0;

    for(i = 0; i < sub_comm_counter_idx; i++)
    {
        comm->sub_comm_counters[i] = 0;    
    }

    for(i = 0; i < sub_comm_timer_idx; i++)
    {
        memset(&((comm->sub_comm_timers[i]).total), 0, sizeof(MPID_Time_t));
        (comm->sub_comm_timers[i]).count = 0;
    }
#endif

    /* It's OK to relax these assertions, but we should do so very
     * intentionally.  For now this function is the only place that we create
     * our hierarchy of communicators */
    MPIU_Assert(comm->node_comm == NULL);
    MPIU_Assert(comm->node_roots_comm == NULL);

    mpi_errno = set_collops(comm);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

    /* Notify device of communicator creation */
    mpi_errno = MPID_Dev_comm_create_hook(comm);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

    MPIR_Comm_map_free(comm);

    if (comm->comm_kind == MPID_INTRACOMM) {

        mpi_errno = MPIU_Find_local_and_external(comm,
                                                 &num_local, &local_rank, &local_procs,
                                                 &num_external, &external_rank, &external_procs,
                                                 &comm->intranode_table, &comm->internode_table);
        /* --BEGIN ERROR HANDLING-- */
        if (mpi_errno) {
            if (MPIR_Err_is_fatal(mpi_errno))
                MPIR_ERR_POP(mpi_errno);

            /* Non-fatal errors simply mean that this communicator will not have
             * any node awareness.  Node-aware collectives are an optimization. */
            MPIU_DBG_MSG_P(COMM, VERBOSE, "MPIU_Find_local_and_external failed for comm_ptr=%p",
                           comm);
            if (comm->intranode_table)
                MPIU_Free(comm->intranode_table);
            if (comm->internode_table)
                MPIU_Free(comm->internode_table);

            mpi_errno = MPI_SUCCESS;
            goto fn_exit;
        }
        /* --END ERROR HANDLING-- */

        /* defensive checks */
        MPIU_Assert(num_local > 0);
        MPIU_Assert(num_local > 1 || external_rank >= 0);
        MPIU_Assert(external_rank < 0 || external_procs != NULL);

        /* if the node_roots_comm and comm would be the same size, then creating
         * the second communicator is useless and wasteful. */
        if (num_external == comm->remote_size) {
            MPIU_Assert(num_local == 1);
            goto fn_exit;
        }

        /* we don't need a local comm if this process is the only one on this node */
        if (num_local > 1) {
            mpi_errno = MPIR_Comm_create(&comm->node_comm);
            if (mpi_errno)
                MPIR_ERR_POP(mpi_errno);

            comm->node_comm->context_id = comm->context_id + MPID_CONTEXT_INTRANODE_OFFSET;
            comm->node_comm->recvcontext_id = comm->node_comm->context_id;
            comm->node_comm->rank = local_rank;
            comm->node_comm->comm_kind = MPID_INTRACOMM;
            comm->node_comm->hierarchy_kind = MPID_HIERARCHY_NODE;
            comm->node_comm->local_comm = NULL;
            MPIU_DBG_MSG_D(CH3_OTHER, VERBOSE, "Create node_comm=%p\n", comm->node_comm);

            comm->node_comm->local_size = num_local;
            comm->node_comm->remote_size = num_local;

            MPIR_Comm_map_irregular(comm->node_comm, comm, local_procs,
                                    num_local, MPIR_COMM_MAP_DIR_L2L, NULL);

            mpi_errno = set_collops(comm->node_comm);
            if (mpi_errno)
                MPIR_ERR_POP(mpi_errno);

            /* Notify device of communicator creation */
            mpi_errno = MPID_Dev_comm_create_hook(comm->node_comm);
            if (mpi_errno)
                MPIR_ERR_POP(mpi_errno);
            /* don't call MPIR_Comm_commit here */

            MPIR_Comm_map_free(comm->node_comm);
        }


        /* this process may not be a member of the node_roots_comm */
        if (local_rank == 0) {
            mpi_errno = MPIR_Comm_create(&comm->node_roots_comm);
            if (mpi_errno)
                MPIR_ERR_POP(mpi_errno);

            comm->node_roots_comm->context_id = comm->context_id + MPID_CONTEXT_INTERNODE_OFFSET;
            comm->node_roots_comm->recvcontext_id = comm->node_roots_comm->context_id;
            comm->node_roots_comm->rank = external_rank;
            comm->node_roots_comm->comm_kind = MPID_INTRACOMM;
            comm->node_roots_comm->hierarchy_kind = MPID_HIERARCHY_NODE_ROOTS;
            comm->node_roots_comm->local_comm = NULL;

            comm->node_roots_comm->local_size = num_external;
            comm->node_roots_comm->remote_size = num_external;

            MPIR_Comm_map_irregular(comm->node_roots_comm, comm,
                                    external_procs, num_external, MPIR_COMM_MAP_DIR_L2L, NULL);

            mpi_errno = set_collops(comm->node_roots_comm);
            if (mpi_errno)
                MPIR_ERR_POP(mpi_errno);

            /* Notify device of communicator creation */
            mpi_errno = MPID_Dev_comm_create_hook(comm->node_roots_comm);
            if (mpi_errno)
                MPIR_ERR_POP(mpi_errno);
            /* don't call MPIR_Comm_commit here */

            MPIR_Comm_map_free(comm->node_roots_comm);
        }

        comm->hierarchy_kind = MPID_HIERARCHY_PARENT;
    }

  fn_exit:
    if (external_procs != NULL)
        MPIU_Free(external_procs);
    if (local_procs != NULL)
        MPIU_Free(local_procs);

    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_COMMIT);
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

/* Returns true if the given communicator is aware of node topology information,
   false otherwise.  Such information could be used to implement more efficient
   collective communication, for example. */
int MPIR_Comm_is_node_aware(MPID_Comm * comm)
{
    return (comm->hierarchy_kind == MPID_HIERARCHY_PARENT);
}

/* Returns true if the communicator is node-aware and processes in all the nodes
   are consecutive. For example, if node 0 contains "0, 1, 2, 3", node 1
   contains "4, 5, 6", and node 2 contains "7", we shall return true. */
int MPIR_Comm_is_node_consecutive(MPID_Comm * comm)
{
    int i = 0, curr_nodeidx = 0;
    int *internode_table = comm->internode_table;

    if (!MPIR_Comm_is_node_aware(comm))
        return 0;

    for (; i < comm->local_size; i++) {
        if (internode_table[i] == curr_nodeidx + 1)
            curr_nodeidx++;
        else if (internode_table[i] != curr_nodeidx)
            return 0;
    }

    return 1;
}

/*
 * Copy a communicator, including creating a new context and copying the
 * virtual connection tables and clearing the various fields.
 * Does *not* copy attributes.  If size is < the size of the local group
 * in the input communicator, copy only the first size elements.
 * If this process is not a member, return a null pointer in outcomm_ptr.
 * This is only supported in the case where the communicator is in
 * Intracomm (not an Intercomm).  Note that this is all that is required
 * for cart_create and graph_create.
 *
 * Used by cart_create, graph_create, and dup_create
 */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_copy
#undef FCNAME
#define FCNAME "MPIR_Comm_copy"
int MPIR_Comm_copy(MPID_Comm * comm_ptr, int size, MPID_Comm ** outcomm_ptr)
{
    int mpi_errno = MPI_SUCCESS;
    MPIU_Context_id_t new_context_id, new_recvcontext_id;
    MPID_Comm *newcomm_ptr = NULL;
    MPIR_Comm_map_t *map;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_COPY);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_COPY);

    /* Get a new context first.  We need this to be collective over the
     * input communicator */
    /* If there is a context id cache in oldcomm, use it here.  Otherwise,
     * use the appropriate algorithm to get a new context id.  Be careful
     * of intercomms here */
    if (comm_ptr->comm_kind == MPID_INTERCOMM) {
        mpi_errno = MPIR_Get_intercomm_contextid(comm_ptr, &new_context_id, &new_recvcontext_id);
        if (mpi_errno)
            MPIR_ERR_POP(mpi_errno);
    }
    else {
        mpi_errno = MPIR_Get_contextid_sparse(comm_ptr, &new_context_id, FALSE);
        new_recvcontext_id = new_context_id;
        if (mpi_errno)
            MPIR_ERR_POP(mpi_errno);
        MPIU_Assert(new_context_id != 0);
    }

    /* This is the local size, not the remote size, in the case of
     * an intercomm */
    if (comm_ptr->rank >= size) {
        *outcomm_ptr = 0;
        /* always free the recvcontext ID, never the "send" ID */
        MPIR_Free_contextid(new_recvcontext_id);
        goto fn_exit;
    }

    /* We're left with the processes that will have a non-null communicator.
     * Create the object, initialize the data, and return the result */

    mpi_errno = MPIR_Comm_create(&newcomm_ptr);
    if (mpi_errno)
        goto fn_fail;

    newcomm_ptr->context_id = new_context_id;
    newcomm_ptr->recvcontext_id = new_recvcontext_id;

    /* Save the kind of the communicator */
    newcomm_ptr->comm_kind = comm_ptr->comm_kind;
    newcomm_ptr->local_comm = 0;

    /* There are two cases here - size is the same as the old communicator,
     * or it is smaller.  If the size is the same, we can just add a reference.
     * Otherwise, we need to create a new network address mapping.  Note that this is the
     * test that matches the test on rank above. */
    if (size == comm_ptr->local_size) {
        /* Duplicate the network address mapping */
        if (comm_ptr->comm_kind == MPID_INTRACOMM)
            MPIR_Comm_map_dup(newcomm_ptr, comm_ptr, MPIR_COMM_MAP_DIR_L2L);
        else
            MPIR_Comm_map_dup(newcomm_ptr, comm_ptr, MPIR_COMM_MAP_DIR_R2R);
    }
    else {
        int i;

        if (comm_ptr->comm_kind == MPID_INTRACOMM)
            MPIR_Comm_map_irregular(newcomm_ptr, comm_ptr, NULL, size, MPIR_COMM_MAP_DIR_L2L, &map);
        else
            MPIR_Comm_map_irregular(newcomm_ptr, comm_ptr, NULL, size, MPIR_COMM_MAP_DIR_R2R, &map);
        for (i = 0; i < size; i++) {
            /* For rank i in the new communicator, find the corresponding
             * rank in the input communicator */
            map->src_mapping[i] = i;
        }
    }

    /* If it is an intercomm, duplicate the local network address references */
    if (comm_ptr->comm_kind == MPID_INTERCOMM) {
        MPIR_Comm_map_dup(newcomm_ptr, comm_ptr, MPIR_COMM_MAP_DIR_L2L);
    }

    /* Set the sizes and ranks */
    newcomm_ptr->rank = comm_ptr->rank;
    if (comm_ptr->comm_kind == MPID_INTERCOMM) {
        newcomm_ptr->local_size = comm_ptr->local_size;
        newcomm_ptr->remote_size = comm_ptr->remote_size;
        newcomm_ptr->is_low_group = comm_ptr->is_low_group;
    }
    else {
        newcomm_ptr->local_size = size;
        newcomm_ptr->remote_size = size;
    }

    /* Inherit the error handler (if any) */
    MPID_THREAD_CS_ENTER(POBJ, MPIR_THREAD_POBJ_COMM_MUTEX(comm_ptr));
    newcomm_ptr->errhandler = comm_ptr->errhandler;
    if (comm_ptr->errhandler) {
        MPIR_Errhandler_add_ref(comm_ptr->errhandler);
    }
    MPID_THREAD_CS_EXIT(POBJ, MPIR_THREAD_POBJ_COMM_MUTEX(comm_ptr));

    /* FIXME do we want to copy coll_fns here? */

    /********* Added by Mehran *******/

    newcomm_ptr->dev.ch.leader_map = comm_ptr->dev.ch.leader_map;

    /********************************/

    
    mpi_errno = MPIR_Comm_commit(newcomm_ptr);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

    /* Start with no attributes on this communicator */
    newcomm_ptr->attributes = 0;

    /* Copy over the info hints from the original communicator. */
    mpi_errno = MPIR_Info_dup_impl(comm_ptr->info, &(newcomm_ptr->info));
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);
    mpi_errno = MPIR_Comm_apply_hints(newcomm_ptr, newcomm_ptr->info);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

    *outcomm_ptr = newcomm_ptr;

  fn_fail:
  fn_exit:

    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_COPY);

    return mpi_errno;
}

/* Copy a communicator, including copying the virtual connection tables and
 * clearing the various fields.  Does *not* allocate a context ID or commit the
 * communicator.  Does *not* copy attributes.
 *
 * Used by comm_idup.
 */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_copy_data
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_copy_data(MPID_Comm * comm_ptr, MPID_Comm ** outcomm_ptr)
{
    int mpi_errno = MPI_SUCCESS;
    MPID_Comm *newcomm_ptr = NULL;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_COPY_DATA);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_COPY_DATA);

    mpi_errno = MPIR_Comm_create(&newcomm_ptr);
    if (mpi_errno)
        goto fn_fail;

    /* use a large garbage value to ensure errors are caught more easily */
    newcomm_ptr->context_id = 32767;
    newcomm_ptr->recvcontext_id = 32767;

    /* Save the kind of the communicator */
    newcomm_ptr->comm_kind = comm_ptr->comm_kind;
    newcomm_ptr->local_comm = 0;

    if (comm_ptr->comm_kind == MPID_INTRACOMM)
        MPIR_Comm_map_dup(newcomm_ptr, comm_ptr, MPIR_COMM_MAP_DIR_L2L);
    else
        MPIR_Comm_map_dup(newcomm_ptr, comm_ptr, MPIR_COMM_MAP_DIR_R2R);

    /* If it is an intercomm, duplicate the network address mapping */
    if (comm_ptr->comm_kind == MPID_INTERCOMM) {
        MPIR_Comm_map_dup(newcomm_ptr, comm_ptr, MPIR_COMM_MAP_DIR_L2L);
    }

    /* Set the sizes and ranks */
    newcomm_ptr->rank = comm_ptr->rank;
    newcomm_ptr->local_size = comm_ptr->local_size;
    newcomm_ptr->remote_size = comm_ptr->remote_size;
    newcomm_ptr->is_low_group = comm_ptr->is_low_group; /* only relevant for intercomms */

    /* Inherit the error handler (if any) */
    MPID_THREAD_CS_ENTER(POBJ, MPIR_THREAD_POBJ_COMM_MUTEX(comm_ptr));
    newcomm_ptr->errhandler = comm_ptr->errhandler;
    if (comm_ptr->errhandler) {
        MPIR_Errhandler_add_ref(comm_ptr->errhandler);
    }
    MPID_THREAD_CS_EXIT(POBJ, MPIR_THREAD_POBJ_COMM_MUTEX(comm_ptr));

    /* FIXME do we want to copy coll_fns here? */

    /* Start with no attributes on this communicator */
    newcomm_ptr->attributes = 0;
    *outcomm_ptr = newcomm_ptr;

  fn_exit:
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_COPY_DATA);
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

/* Common body between MPIR_Comm_release and MPIR_comm_release_always.  This
 * helper function frees the actual MPID_Comm structure and any associated
 * storage.  It also releases any references to other objects.
 * This function should only be called when the communicator's reference count
 * has dropped to 0.
 *
 * !!! This routine should *never* be called outside of MPIR_Comm_release{,_always} !!!
 */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_delete_internal
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_delete_internal(MPID_Comm * comm_ptr)
{
    int in_use;
    int mpi_errno = MPI_SUCCESS;
    MPID_MPI_STATE_DECL(MPID_STATE_COMM_DELETE_INTERNAL);

    MPID_MPI_FUNC_ENTER(MPID_STATE_COMM_DELETE_INTERNAL);

    MPIU_Assert(MPIU_Object_get_ref(comm_ptr) == 0);    /* sanity check */

    /* Remove the attributes, executing the attribute delete routine.
     * Do this only if the attribute functions are defined.
     * This must be done first, because if freeing the attributes
     * returns an error, the communicator is not freed */
    if (MPIR_Process.attr_free && comm_ptr->attributes) {
        /* Temporarily add a reference to this communicator because
         * the attr_free code requires a valid communicator */
        MPIU_Object_add_ref(comm_ptr);
        mpi_errno = MPIR_Process.attr_free(comm_ptr->handle, &comm_ptr->attributes);
        /* Release the temporary reference added before the call to
         * attr_free */
        MPIU_Object_release_ref(comm_ptr, &in_use);
    }

    /* If the attribute delete functions return failure, the
     * communicator must not be freed.  That is the reason for the
     * test on mpi_errno here. */
    if (mpi_errno == MPI_SUCCESS) {
        /* If this communicator is our parent, and we're disconnecting
         * from the parent, mark that fact */
        if (MPIR_Process.comm_parent == comm_ptr)
            MPIR_Process.comm_parent = NULL;

        /* Notify the device that the communicator is about to be
         * destroyed */
        mpi_errno = MPID_Dev_comm_destroy_hook(comm_ptr);
        if (mpi_errno)
            MPIR_ERR_POP(mpi_errno);

        /* Free info hints */
        if (comm_ptr->info != NULL) {
            MPIU_Info_free(comm_ptr->info);
        }

        /* release our reference to the collops structure, comes after the
         * destroy_hook to allow the device to manage these vtables in a custom
         * fashion */
        if (comm_ptr->coll_fns && --comm_ptr->coll_fns->ref_count == 0) {
            MPIU_Free(comm_ptr->coll_fns);
            comm_ptr->coll_fns = NULL;
        }

        if (comm_ptr->comm_kind == MPID_INTERCOMM && comm_ptr->local_comm)
            MPIR_Comm_release(comm_ptr->local_comm);

        /* Free the local and remote groups, if they exist */
        if (comm_ptr->local_group)
            MPIR_Group_release(comm_ptr->local_group);
        if (comm_ptr->remote_group)
            MPIR_Group_release(comm_ptr->remote_group);
 
        /* Free sub-communicator counters */
        #if ENABLE_PVAR_MV2
        if(comm_ptr->sub_comm_counters)
        {
           MPIU_Free(comm_ptr->sub_comm_counters);
        }
        if(comm_ptr->sub_comm_timers)
        {
            MPIU_Free(comm_ptr->sub_comm_timers);
        } 
        #endif
 
        /* free the intra/inter-node communicators, if they exist */
#if defined(CHANNEL_MRAIL) || defined(CHANNEL_PSM)
        if( comm_ptr->dev.ch.shmem_coll_ok == 1) { 
             free_2level_comm(comm_ptr); 
        } 
#endif
        if (comm_ptr->node_comm)
            MPIR_Comm_release(comm_ptr->node_comm);
        if (comm_ptr->node_roots_comm)
            MPIR_Comm_release(comm_ptr->node_roots_comm);
        if (comm_ptr->intranode_table != NULL)
            MPIU_Free(comm_ptr->intranode_table);
        if (comm_ptr->internode_table != NULL)
            MPIU_Free(comm_ptr->internode_table);

        /* Free the context value.  This should come after freeing the
         * intra/inter-node communicators since those free calls won't
         * release this context ID and releasing this before then could lead
         * to races once we make threading finer grained. */
        /* This must be the recvcontext_id (i.e. not the (send)context_id)
         * because in the case of intercommunicators the send context ID is
         * allocated out of the remote group's bit vector, not ours. */
        MPIR_Free_contextid(comm_ptr->recvcontext_id);

        /* We need to release the error handler */
        if (comm_ptr->errhandler &&
            !(HANDLE_GET_KIND(comm_ptr->errhandler->handle) == HANDLE_KIND_BUILTIN)) {
            int errhInuse;
            MPIR_Errhandler_release_ref(comm_ptr->errhandler, &errhInuse);
            if (!errhInuse) {
                MPIU_Handle_obj_free(&MPID_Errhandler_mem, comm_ptr->errhandler);
            }
        }

        /* Remove from the list of active communicators if
         * we are supporting message-queue debugging.  We make this
         * conditional on having debugger support since the
         * operation is not constant-time */
        MPIR_COMML_FORGET(comm_ptr);

        /* Check for predefined communicators - these should not
         * be freed */
        if (!(HANDLE_GET_KIND(comm_ptr->handle) == HANDLE_KIND_BUILTIN))
            MPIU_Handle_obj_free(&MPID_Comm_mem, comm_ptr);
    }
    else {
        /* If the user attribute free function returns an error,
         * then do not free the communicator */
        MPIR_Comm_add_ref(comm_ptr);
    }

  fn_exit:
    MPID_MPI_FUNC_EXIT(MPID_STATE_COMM_DELETE_INTERNAL);
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

/* Release a reference to a communicator.  If there are no pending
   references, delete the communicator and recover all storage and
   context ids.  This version of the function always manipulates the reference
   counts, even for predefined objects. */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_release_always
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_release_always(MPID_Comm * comm_ptr)
{
    int mpi_errno = MPI_SUCCESS;
    int in_use;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_RELEASE_ALWAYS);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_RELEASE_ALWAYS);

    /* we want to short-circuit any optimization that avoids reference counting
     * predefined communicators, such as MPI_COMM_WORLD or MPI_COMM_SELF. */
    MPIU_Object_release_ref_always(comm_ptr, &in_use);
    if (!in_use) {
        mpi_errno = MPIR_Comm_delete_internal(comm_ptr);
        if (mpi_errno)
            MPIR_ERR_POP(mpi_errno);
    }

  fn_exit:
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_RELEASE_ALWAYS);
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

/* Apply all known info hints in the specified info chain to the given
 * communicator. */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_apply_hints
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_apply_hints(MPID_Comm * comm_ptr, MPID_Info * info_ptr)
{
    int mpi_errno = MPI_SUCCESS;
    MPID_Info *hint = NULL;
    char hint_name[MPI_MAX_INFO_KEY] = { 0 };
    struct MPIR_Comm_hint_fn_elt *hint_fn = NULL;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_APPLY_HINTS);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_APPLY_HINTS);

    MPL_LL_FOREACH(info_ptr, hint) {
        /* Have we hit the default, empty info hint? */
        if (hint->key == NULL)
            continue;

        strncpy(hint_name, hint->key, MPI_MAX_INFO_KEY);

        HASH_FIND_STR(MPID_hint_fns, hint_name, hint_fn);

        /* Skip hints that MPICH doesn't recognize. */
        if (hint_fn) {
            mpi_errno = hint_fn->fn(comm_ptr, hint, hint_fn->state);
            if (mpi_errno)
                MPIR_ERR_POP(mpi_errno);
        }
    }

  fn_exit:
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_APPLY_HINTS);
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

#undef FUNCNAME
#define FUNCNAME free_hint_handles
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
static int free_hint_handles(void *ignore)
{
    int mpi_errno = MPI_SUCCESS;
    struct MPIR_Comm_hint_fn_elt *curr_hint = NULL, *tmp = NULL;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_FREE_HINT_HANDLES);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_FREE_HINT_HANDLES);

    if (MPID_hint_fns) {
        HASH_ITER(hh, MPID_hint_fns, curr_hint, tmp) {
            HASH_DEL(MPID_hint_fns, curr_hint);
            MPIU_Free(curr_hint);
        }
    }

    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_FREE_HINT_HANDLES);
    return mpi_errno;
}

/* The hint logic is stored in a uthash, with hint name as key and
 * the function responsible for applying the hint as the value. */
#undef FUNCNAME
#define FUNCNAME MPIR_Comm_register_hint
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Comm_register_hint(const char *hint_key, MPIR_Comm_hint_fn_t fn, void *state)
{
    int mpi_errno = MPI_SUCCESS;
    struct MPIR_Comm_hint_fn_elt *hint_elt = NULL;
    MPID_MPI_STATE_DECL(MPID_STATE_MPIR_COMM_REGISTER_HINT);

    MPID_MPI_FUNC_ENTER(MPID_STATE_MPIR_COMM_REGISTER_HINT);

    if (MPID_hint_fns == NULL) {
        MPIR_Add_finalize(free_hint_handles, NULL, MPIR_FINALIZE_CALLBACK_PRIO - 1);
    }

    hint_elt = MPIU_Malloc(sizeof(struct MPIR_Comm_hint_fn_elt));
    strncpy(hint_elt->name, hint_key, MPI_MAX_INFO_KEY);
    hint_elt->state = state;
    hint_elt->fn = fn;

    HASH_ADD_STR(MPID_hint_fns, name, hint_elt);

    MPID_MPI_FUNC_EXIT(MPID_STATE_MPIR_COMM_REGISTER_HINT);
    return mpi_errno;
}
