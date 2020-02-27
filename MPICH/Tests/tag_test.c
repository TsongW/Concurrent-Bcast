#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>



int main(int argc, char*argv){

	int rank, nproc;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Request send_requests_1, send_requests_2, send_requests_3, recv_request_1, recv_request_2, recv_request_3;
    MPI_Status status1, status2, status3, status4, status5, status6;
	int local_1[3] = {1, 2, 3};
	int local_2[3] = {4, 5, 6};


	if(rank==0){
		MPI_Isend(&(local_1[0]), 1, MPI_INT, 1, 88, MPI_COMM_WORLD, &send_requests_1);
		MPI_Isend(&(local_1[1]), 1, MPI_INT, 1, 88, MPI_COMM_WORLD, &send_requests_2);
		MPI_Isend(&(local_1[2]), 1, MPI_INT, 1, 88, MPI_COMM_WORLD, &send_requests_3);

		MPI_Wait(&send_requests_1, &status4);
		MPI_Wait(&send_requests_2, &status5);
		MPI_Wait(&send_requests_3, &status6);

	}else{
		MPI_Irecv(&(local_2[0]), 1, MPI_INT, 0, 88, MPI_COMM_WORLD, &recv_request_1);
		MPI_Irecv(&(local_2[1]), 1, MPI_INT, 0, 88, MPI_COMM_WORLD, &recv_request_2);
		MPI_Irecv(&(local_2[2]), 1, MPI_INT, 0, 88, MPI_COMM_WORLD, &recv_request_3);

		MPI_Wait(&recv_request_1, &status1);
		MPI_Wait(&recv_request_2, &status2);
		MPI_Wait(&recv_request_3, &status3);


		
	}

	


	if(rank==1){
		printf("Received %d, %d, %d\n", local_2[0], local_2[1], local_2[2]);
	}

	MPI_Finalize();


	printf("Done!\n");



}