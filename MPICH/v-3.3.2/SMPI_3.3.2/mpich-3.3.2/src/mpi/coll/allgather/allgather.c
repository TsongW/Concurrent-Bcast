/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#include "mpiimpl.h"




/*
=== BEGIN_MPI_T_CVAR_INFO_BLOCK ===

cvars:
    - name        : MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE
      category    : COLLECTIVE
      type        : int
      default     : 81920
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        For MPI_Allgather and MPI_Allgatherv, the short message algorithm will
        be used if the send buffer size is < this value (in bytes).
        (See also: MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE)

    - name        : MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE
      category    : COLLECTIVE
      type        : int
      default     : 524288
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        For MPI_Allgather and MPI_Allgatherv, the long message algorithm will be
        used if the send buffer size is >= this value (in bytes)
        (See also: MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE)

    - name        : MPIR_CVAR_ALLGATHER_INTRA_ALGORITHM
      category    : COLLECTIVE
      type        : string
      default     : auto
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : |-
        Variable to select allgather algorithm
        auto               - Internal algorithm selection
        brucks             - Force brucks algorithm
        nb                 - Force nonblocking algorithm
        recursive_doubling - Force recursive doubling algorithm
        ring               - Force ring algorithm

    - name        : MPIR_CVAR_ALLGATHER_INTER_ALGORITHM
      category    : COLLECTIVE
      type        : string
      default     : auto
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : |-
        Variable to select allgather algorithm
        auto                      - Internal algorithm selection
        local_gather_remote_bcast - Force local-gather-remote-bcast algorithm
        nb                        - Force nonblocking algorithm

    - name        : MPIR_CVAR_ALLGATHER_DEVICE_COLLECTIVE
      category    : COLLECTIVE
      type        : boolean
      default     : true
      class       : device
      verbosity   : MPI_T_VERBOSITY_USER_BASIC
      scope       : MPI_T_SCOPE_ALL_EQ
      description : >-
        If set to true, MPI_Allgather will allow the device to override the
        MPIR-level collective algorithms. The device still has the
        option to call the MPIR-level algorithms manually.
        If set to false, the device-level allgather function will not be
        called.

=== END_MPI_T_CVAR_INFO_BLOCK ===
*/

/* -- Begin Profiling Symbol Block for routine MPI_Allgather */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Allgather = PMPI_Allgather
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Allgather  MPI_Allgather
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Allgather as PMPI_Allgather
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf,
                  int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
    __attribute__ ((weak, alias("PMPI_Allgather")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Allgather
#define MPI_Allgather PMPI_Allgather

#undef FUNCNAME
#define FUNCNAME MPIR_Allgather_intra_auto
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Allgather_intra_auto(const void *sendbuf,
                              int sendcount,
                              MPI_Datatype sendtype,
                              void *recvbuf,
                              int recvcount,
                              MPI_Datatype recvtype, MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag)
{
    int comm_size;
    int mpi_errno = MPI_SUCCESS;
    MPI_Aint tot_bytes;
    int type_size;

    if (((sendcount == 0) && (sendbuf != MPI_IN_PLACE)) || (recvcount == 0))
        return MPI_SUCCESS;

    comm_size = comm_ptr->local_size;
    MPIR_Datatype_get_size_macro(recvtype, type_size);

    tot_bytes = (MPI_Aint) recvcount *comm_size * type_size;
    if ((tot_bytes < MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE) && !(comm_size & (comm_size - 1))) {
        if(SECURE_MPI){
          mpi_errno =
            MPIR_SEC_Allgather_intra_recursive_doubling(sendbuf, sendcount, sendtype, recvbuf,
                                                    recvcount, recvtype, comm_ptr, errflag);
        }else{
          mpi_errno =
            MPIR_Allgather_intra_recursive_doubling(sendbuf, sendcount, sendtype, recvbuf,
                                                    recvcount, recvtype, comm_ptr, errflag);
        }
        
    } else if (tot_bytes < MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE) {
        if(SECURE_MPI){
          mpi_errno =
            MPIR_SEC_Allgather_intra_brucks(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype,
                                        comm_ptr, errflag);
        }else{
          mpi_errno =
            MPIR_Allgather_intra_brucks(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype,
                                        comm_ptr, errflag);
        }
        
    } else {
      if(SECURE_MPI){
        mpi_errno =
            MPIR_SEC_Allgather_intra_ring(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype,
                                      comm_ptr, errflag);
      }else{
        mpi_errno =
            MPIR_Allgather_intra_ring(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype,
                                      comm_ptr, errflag);
      }
    }
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

  fn_exit:
    if (*errflag != MPIR_ERR_NONE)
        MPIR_ERR_SET(mpi_errno, *errflag, "**coll_fail");

    return mpi_errno;

  fn_fail:
    goto fn_exit;
}


#undef FUNCNAME
#define FUNCNAME MPIR_Allgather_inter_auto
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Allgather_inter_auto(const void *sendbuf,
                              int sendcount,
                              MPI_Datatype sendtype,
                              void *recvbuf,
                              int recvcount,
                              MPI_Datatype recvtype, MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag)
{
    int mpi_errno = MPI_SUCCESS;

    mpi_errno = MPIR_Allgather_inter_local_gather_remote_bcast(sendbuf, sendcount, sendtype,
                                                               recvbuf, recvcount, recvtype,
                                                               comm_ptr, errflag);

    return mpi_errno;
}

#undef FUNCNAME
#define FUNCNAME MPIR_Allgather_impl
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Allgather_impl(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                        void *recvbuf, int recvcount, MPI_Datatype recvtype,
                        MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag)
{
    int mpi_errno = MPI_SUCCESS;
    
    if (comm_ptr->comm_kind == MPIR_COMM_KIND__INTRACOMM) {
        /* intracommunicator */
        
        /*Added by Mehran*/
        if(SECURE_MPI){
          switch (MPIR_Allgather_intra_algo_choice) {

            case MPIR_ALLGATHER_INTRA_ALGO_BRUCKS:
                mpi_errno =
                    MPIR_SEC_Allgather_intra_brucks(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                                recvtype, comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTRA_ALGO_RECURSIVE_DOUBLING:
                mpi_errno =
                    MPIR_SEC_Allgather_intra_recursive_doubling(sendbuf, sendcount, sendtype, recvbuf,
                                                            recvcount, recvtype, comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTRA_ALGO_RING:
                mpi_errno =
                    MPIR_SEC_Allgather_intra_ring(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                              recvtype, comm_ptr, errflag);
                break;
            // case MPIR_ALLGATHER_INTRA_ALGO_NB:
            //     mpi_errno =
            //         MPIR_Allgather_allcomm_nb(sendbuf, sendcount, sendtype, recvbuf, recvcount,
            //                                   recvtype, comm_ptr, errflag);
            //     break;
            // case MPIR_ALLGATHER_INTRA_ALGO_AUTO:
            //     MPL_FALLTHROUGH;
            default:
                mpi_errno =
                    MPIR_Allgather_intra_auto(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                              recvtype, comm_ptr, errflag);
                break;
          }//end switch
        }//end if
        else{


        /************************/
        switch (MPIR_Allgather_intra_algo_choice) {
            case MPIR_ALLGATHER_INTRA_ALGO_BRUCKS:
                mpi_errno =
                    MPIR_Allgather_intra_brucks(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                                recvtype, comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTRA_ALGO_RECURSIVE_DOUBLING:
                mpi_errno =
                    MPIR_Allgather_intra_recursive_doubling(sendbuf, sendcount, sendtype, recvbuf,
                                                            recvcount, recvtype, comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTRA_ALGO_RING:
                mpi_errno =
                    MPIR_Allgather_intra_ring(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                              recvtype, comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTRA_ALGO_NB:
                mpi_errno =
                    MPIR_Allgather_allcomm_nb(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                              recvtype, comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTRA_ALGO_AUTO:
                MPL_FALLTHROUGH;
            default:
                mpi_errno =
                    MPIR_Allgather_intra_auto(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                              recvtype, comm_ptr, errflag);
                break;
        }//end switch
        /*Added by Mehran*/
      }//end else SEC_MPI
      /*****************/
    } else {
        /* intercommunicator */
        switch (MPIR_Allgather_inter_algo_choice) {
            case MPIR_ALLGATHER_INTER_ALGO_LOCAL_GATHER_REMOTE_BCAST:
                mpi_errno =
                    MPIR_Allgather_inter_local_gather_remote_bcast(sendbuf, sendcount, sendtype,
                                                                   recvbuf, recvcount, recvtype,
                                                                   comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTER_ALGO_NB:
                mpi_errno =
                    MPIR_Allgather_allcomm_nb(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                              recvtype, comm_ptr, errflag);
                break;
            case MPIR_ALLGATHER_INTER_ALGO_AUTO:
                MPL_FALLTHROUGH;
            default:
                mpi_errno =
                    MPIR_Allgather_inter_auto(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                                              recvtype, comm_ptr, errflag);
                break;
        }
    }
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

  fn_exit:
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

#undef FUNCNAME
#define FUNCNAME MPIR_Allgather
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                   void *recvbuf, int recvcount, MPI_Datatype recvtype,
                   MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag)
{
    int mpi_errno = MPI_SUCCESS;

    if (MPIR_CVAR_ALLGATHER_DEVICE_COLLECTIVE && MPIR_CVAR_DEVICE_COLLECTIVES) {
        mpi_errno = MPID_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype,
                                   comm_ptr, errflag);
    } else {
        mpi_errno = MPIR_Allgather_impl(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype,
                                        comm_ptr, errflag);
    }

    return mpi_errno;
}


/***Added by Mehran***
#undef FUNCNAME
#define FUNCNAME MPIR_SEC_Allgather
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_SEC_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                   void *recvbuf, int recvcount, MPI_Datatype recvtype,
                   MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag)
{
    printf("Naive Secure Allgather!\n");
    fflush(stdout);

    int var, sendtype_sz, recvtype_sz, mpi_errno = MPI_SUCCESS;
    unsigned long  ciphertext_sendbuf_len = 0;
    sendtype_sz= recvtype_sz= 0;
     
    var=MPI_Type_size(sendtype, &sendtype_sz);
    var=MPI_Type_size(recvtype, &recvtype_sz);
    // Set the nonce in send_ciphertext 
    RAND_bytes(ciphertext_sendbuf, 12); // 12 bytes of nonce    

    unsigned long t=0;
    t = (unsigned long)(sendtype_sz*sendcount);
    unsigned long   max_out_len = (unsigned long) (16 + (sendtype_sz*sendcount));
    
    if(!EVP_AEAD_CTX_seal(ctx, ciphertext_sendbuf+12,
                         &ciphertext_sendbuf_len, max_out_len,
                         ciphertext_sendbuf, 12,
                         sendbuf,  t,
                        NULL, 0)){
        printf("Error in encryption: allgather\n");
        fflush(stdout);
    }         

    mpi_errno=MPIR_Allgather(ciphertext_sendbuf, ciphertext_sendbuf_len+12, MPI_CHAR,
                  ciphertext_recvbuf, ((recvcount*recvtype_sz) + 16+12), MPI_CHAR, comm_ptr, errflag);
    
    unsigned long count=0;
    unsigned long next, dest;
    unsigned int i;
    for( i = 0; i < comm_ptr->local_size; i++){
        next =(unsigned long )(i*((recvcount*recvtype_sz) + 16+12));
        dest =(unsigned long )(i*(recvcount*recvtype_sz));
        

        if(!EVP_AEAD_CTX_open(ctx, ((recvbuf+dest)),
                        &count, (unsigned long )((recvcount*recvtype_sz)+16),
                         (ciphertext_recvbuf+next), 12,
                        (ciphertext_recvbuf+next+12), (unsigned long )((recvcount*recvtype_sz)+16),
                        NULL, 0)){
            printf("Decryption error: allgather\n");
            fflush(stdout);        
        }                               
       
    }

    return mpi_errno;
}

/*********************/


#endif


#undef FUNCNAME
#define FUNCNAME MPI_Allgather
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
/*@
MPI_Allgather - Gathers data from all tasks and distribute the combined
    data to all tasks

Input Parameters:
+ sendbuf - starting address of send buffer (choice)
. sendcount - number of elements in send buffer (integer)
. sendtype - data type of send buffer elements (handle)
. recvcount - number of elements received from any process (integer)
. recvtype - data type of receive buffer elements (handle)
- comm - communicator (handle)

Output Parameters:
. recvbuf - address of receive buffer (choice)

Notes:
 The MPI standard (1.0 and 1.1) says that
.n
.n
 The jth block of data sent from  each process is received by every process
 and placed in the jth block of the buffer 'recvbuf'.
.n
.n
 This is misleading; a better description is
.n
.n
 The block of data sent from the jth process is received by every
 process and placed in the jth block of the buffer 'recvbuf'.
.n
.n
 This text was suggested by Rajeev Thakur and has been adopted as a
 clarification by the MPI Forum.

.N ThreadSafe

.N Fortran

.N Errors
.N MPI_ERR_COMM
.N MPI_ERR_COUNT
.N MPI_ERR_TYPE
.N MPI_ERR_BUFFER
@*/
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                  void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    int mpi_errno = MPI_SUCCESS;
    MPIR_Comm *comm_ptr = NULL;
    MPIR_Errflag_t errflag = MPIR_ERR_NONE;
    MPIR_FUNC_TERSE_STATE_DECL(MPID_STATE_MPI_ALLGATHER);

    MPIR_ERRTEST_INITIALIZED_ORDIE();

    MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    MPIR_FUNC_TERSE_COLL_ENTER(MPID_STATE_MPI_ALLGATHER);

    /* Validate parameters, especially handles needing to be converted */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            MPIR_ERRTEST_COMM(comm, mpi_errno);
        }
        MPID_END_ERROR_CHECKS;
    }
#endif /* HAVE_ERROR_CHECKING */

    /* Convert MPI object handles to object pointers */
    MPIR_Comm_get_ptr(comm, comm_ptr);

    /* Validate parameters and objects (post conversion) */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            MPIR_Datatype *recvtype_ptr = NULL, *sendtype_ptr = NULL;

            MPIR_Comm_valid_ptr(comm_ptr, mpi_errno, FALSE);
            if (mpi_errno != MPI_SUCCESS)
                goto fn_fail;

            if (comm_ptr->comm_kind == MPIR_COMM_KIND__INTERCOMM) {
                MPIR_ERRTEST_SENDBUF_INPLACE(sendbuf, sendcount, mpi_errno);
            } else {
                /* catch common aliasing cases */
                if (sendbuf != MPI_IN_PLACE && sendtype == recvtype &&
                    recvcount != 0 && sendcount != 0) {
                    int recvtype_size;
                    MPIR_Datatype_get_size_macro(recvtype, recvtype_size);
                    MPIR_ERRTEST_ALIAS_COLL(sendbuf,
                                            (char *) recvbuf +
                                            comm_ptr->rank * recvcount * recvtype_size, mpi_errno);
                }
            }

            if (sendbuf != MPI_IN_PLACE) {
                MPIR_ERRTEST_COUNT(sendcount, mpi_errno);
                MPIR_ERRTEST_DATATYPE(sendtype, "sendtype", mpi_errno);
                if (HANDLE_GET_KIND(sendtype) != HANDLE_KIND_BUILTIN) {
                    MPIR_Datatype_get_ptr(sendtype, sendtype_ptr);
                    MPIR_Datatype_valid_ptr(sendtype_ptr, mpi_errno);
                    if (mpi_errno != MPI_SUCCESS)
                        goto fn_fail;
                    MPIR_Datatype_committed_ptr(sendtype_ptr, mpi_errno);
                    if (mpi_errno != MPI_SUCCESS)
                        goto fn_fail;
                }
                MPIR_ERRTEST_USERBUFFER(sendbuf, sendcount, sendtype, mpi_errno);
            }

            MPIR_ERRTEST_RECVBUF_INPLACE(recvbuf, recvcount, mpi_errno);
            MPIR_ERRTEST_COUNT(recvcount, mpi_errno);
            MPIR_ERRTEST_DATATYPE(recvtype, "recvtype", mpi_errno);
            if (HANDLE_GET_KIND(recvtype) != HANDLE_KIND_BUILTIN) {
                MPIR_Datatype_get_ptr(recvtype, recvtype_ptr);
                MPIR_Datatype_valid_ptr(recvtype_ptr, mpi_errno);
                if (mpi_errno != MPI_SUCCESS)
                    goto fn_fail;
                MPIR_Datatype_committed_ptr(recvtype_ptr, mpi_errno);
                if (mpi_errno != MPI_SUCCESS)
                    goto fn_fail;
            }
            MPIR_ERRTEST_USERBUFFER(recvbuf, recvcount, recvtype, mpi_errno);
        }
        MPID_END_ERROR_CHECKS;
    }
#endif /* HAVE_ERROR_CHECKING */

    /* ... body of routine ...  */
    /*Added by Mehran*/
    /*if(NAIVE_SECURE_MPI){
        mpi_errno = MPIR_SEC_Allgather(sendbuf, sendcount, sendtype,
                               recvbuf, recvcount, recvtype, comm_ptr, &errflag);
    }else{*/

        mpi_errno = MPIR_Allgather(sendbuf, sendcount, sendtype,
                               recvbuf, recvcount, recvtype, comm_ptr, &errflag);
    //}
    
    if (mpi_errno)
        goto fn_fail;

    /* ... end of body of routine ... */

  fn_exit:
    MPIR_FUNC_TERSE_COLL_EXIT(MPID_STATE_MPI_ALLGATHER);
    MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    return mpi_errno;

  fn_fail:
    /* --BEGIN ERROR HANDLING-- */
#ifdef HAVE_ERROR_CHECKING
    {
        mpi_errno =
            MPIR_Err_create_code(mpi_errno, MPIR_ERR_RECOVERABLE, FCNAME, __LINE__, MPI_ERR_OTHER,
                                 "**mpi_allgather", "**mpi_allgather %p %d %D %p %d %D %C", sendbuf,
                                 sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
    }
#endif
    mpi_errno = MPIR_Err_return_comm(comm_ptr, FCNAME, mpi_errno);
    goto fn_exit;
    /* --END ERROR HANDLING-- */
}



/*Added by Mehran*/


// #undef FUNCNAME
// #define FUNCNAME MPI_MyAllgather
// #undef FCNAME
// #define FCNAME MPL_QUOTE(FUNCNAME)

// int MPI_MyAllgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
//                   void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
// {
//     int mpi_errno = MPI_SUCCESS;
//     MPIR_Comm *comm_ptr = NULL;
//     MPIR_Errflag_t errflag = MPIR_ERR_NONE;
//     MPIR_FUNC_TERSE_STATE_DECL(MPID_STATE_MPI_ALLGATHER);

//     MPIR_ERRTEST_INITIALIZED_ORDIE();

//     MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
//     MPIR_FUNC_TERSE_COLL_ENTER(MPID_STATE_MPI_ALLGATHER);

//     /* Validate parameters, especially handles needing to be converted */
// #ifdef HAVE_ERROR_CHECKING
//     {
//         MPID_BEGIN_ERROR_CHECKS;
//         {
//             MPIR_ERRTEST_COMM(comm, mpi_errno);
//         }
//         MPID_END_ERROR_CHECKS;
//     }
// #endif /* HAVE_ERROR_CHECKING */

//     /* Convert MPI object handles to object pointers */
//     MPIR_Comm_get_ptr(comm, comm_ptr);

//     printf("Hi from MyAllgather\n");
//     fn_exit:
//     MPIR_FUNC_TERSE_COLL_EXIT(MPID_STATE_MPI_ALLGATHER);
//     MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
//     return mpi_errno;

//   fn_fail:
//     goto fn_exit;
//   }





/* Added by Abu Naser */
/* Variable nonce */


#undef FUNCNAME
#define FUNCNAME init_crypto
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)

void init_crypto(){
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_256_gcm_siv(),
                            key,
                            32, 0);
    return;                        
}


#undef FUNCNAME
#define FUNCNAME init_boringssl_256_siv
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)

void init_boringssl_256_siv(){
    //unsigned char key_boringssl_siv_32 [32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_256_gcm_siv(),
                            key,
                            32, 0);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  if (world_rank == 0) printf("\n\t\t****** Secure MPI with BoringSSL  256  GCM-SIV ********\n");
    return;                        
}

#undef FUNCNAME
#define FUNCNAME init_boringssl_128_siv
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)

void init_boringssl_128_siv(){
   // unsigned char key_boringssl_siv_16 [16] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_128_gcm_siv(),
                            key,
                            16, 0);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  if (world_rank == 0) printf("\n\t\t****** Secure MPI with BoringSSL  128  GCM-SIV ********\n");
    return;                        
}

#undef FUNCNAME
#define FUNCNAME init_boringssl_128
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)

void init_boringssl_128(){
   // unsigned char key_boringssl_16 [16] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_128_gcm(),
                            key,
                            16, 0);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  //if (world_rank == 0) printf("\n\t\t****** Secure MPI with BoringSSL  128  GCM ********\n");
    return;                        
}

#undef FUNCNAME
#define FUNCNAME init_boringssl_256
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)

void init_boringssl_256(){
    //unsigned char key_boringssl_32 [32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_256_gcm(),
                            key,
                            32, 0);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  //if (world_rank == 0) printf("\n\t\t****** Secure MPI with BoringSSL  256  GCM ********\n");
    return;                        
}

