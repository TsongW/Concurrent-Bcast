#include "mpiimpl.h"




#undef FUNCNAME
#define FUNCNAME MPIR_SEC_Allgather_intra_ring
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_SEC_Allgather_intra_ring(const void *sendbuf,
                              int sendcount,
                              MPI_Datatype sendtype,
                              void *recvbuf,
                              int recvcount,
                              MPI_Datatype recvtype, MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag)
{

	int comm_size, rank;
    int mpi_errno = MPI_SUCCESS;
    int mpi_errno_ret = MPI_SUCCESS;
    MPI_Aint recvtype_extent;
    int j, i;
    int left, right, jnext;

    if (((sendcount == 0) && (sendbuf != MPI_IN_PLACE)) || (recvcount == 0))
        return MPI_SUCCESS;

    comm_size = comm_ptr->local_size;
    rank = comm_ptr->rank;


    printf("YooHoo! This is my Secure Ring!\n");
    fflush(stdout);
    return mpi_errno;



}