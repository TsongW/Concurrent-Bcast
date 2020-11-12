#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "shm_headers.h"
#include <math.h>
#include <unistd.h>

//#define ERROR_CHECK
#ifdef ERROR_CHECK
#define Type_MPI MPI_INT
typedef int Datatype;
#else
#define Type_MPI MPI_CHAR
typedef char Datatype;
#endif

//#define Type_MPI MPI_CHAR
//typedef char Datatype;

int print_vec(int *vec, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");
    return 0;
}

int add_a_and_b(int size, const int *a, const int *b, int *c)
{
    int i;
    for(i = 0; i < size; i++)
    {
        c[i] = a[i] + b[i];
    }
    return 0;
}

int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int make_nbrhood(MPI_Comm comm, int d, int r,
                 int *indegree_ptr,
                 int **sources_ptr,
                 int **sourcesweights_ptr,
                 int *outdegree_ptr,
                 int **destinations_ptr,
                 int **destweights_ptr)
{
    int i, indgr, outdgr, inidx, outidx, comm_size, my_rank, nbr_rank, min_dim;
    int *srcs, *srcwghts, *dests, *destwghts;
    int dims[d];
    int periods[d];
    int my_coords[d];
    int nbr_coords[d];
    int disp_vec[d];
    MPI_Comm cart_comm;

    indgr = outdgr = inidx = outidx = 0;
    MPI_Comm_size(comm, &comm_size);
    MPI_Comm_rank(comm, &my_rank);

    //Set the periods, and initialize dims to 0
    for(i = 0; i < d; i++)
    {
        periods[i] = 1;
        dims[i] = 0;
    }
    MPI_Dims_create(comm_size, d, dims);
    MPI_Cart_create(comm, d, dims, periods, 0, &cart_comm);


    //Print the dimension sizes
    if(my_rank == 0)
    {
        printf("dims = ");
        for(i = 0; i < d; i++)
        {
            printf("%d ", dims[i]);
        }
        printf("\n");
    }

    //Find max valid r based on minimum dimension size
    min_dim = comm_size;
    for(i = 0; i < d; i++)
    {
        if(dims[i] < min_dim)
            min_dim = dims[i];
    }
    if(r > ((min_dim - 1) / 2)) //Divided by 2 to avoid duplicate neighbors
    {
        if(my_rank == 0)
        {
            printf("ERROR: the given neighborhood radius (r = %d) is greater than the half of the minimum dimension size %d. Aborting!\n", r, min_dim);
            fflush(stdout);
        }
        MPI_Comm_free(&cart_comm);
        MPI_Finalize();
        exit(0);
    }

    //Calculate number of neighbors
    outdgr = indgr = pow((2*r + 1), d) - 1;

    srcs = (int*) malloc(indgr * sizeof(int));
    srcwghts = (int*) malloc(indgr * sizeof(int));
    dests = (int*) malloc(outdgr * sizeof(int));
    destwghts = (int*) malloc(outdgr * sizeof(int));

    for(i = 0; i < indgr; i++)
        srcwghts[i] = 1;
    for(i = 0; i < outdgr; i++)
        destwghts[i] = 1;

    //Initialize the displacement vector
    for(i = 0; i < d; i++)
        disp_vec[i] = -r;

    MPI_Cart_coords(cart_comm, my_rank, d, my_coords);
    int overflow = 0;
    while(!overflow)
    {
        /* The displacement vector will act like a counter
         * that is increased in each iteration to find the
         * next neighbor. Each digit of the counter spans
         * from -r to r.
         */
        add_a_and_b(d, my_coords, disp_vec, nbr_coords);

        MPI_Cart_rank(cart_comm, nbr_coords, &nbr_rank);
        if(nbr_rank != my_rank) //Skip the case where nbr_coords is equal to all 0
        {
            dests[outidx] = nbr_rank;
            srcs[inidx] = nbr_rank;
            outidx++;
            inidx++;
        }

        //Increase displacement vector by 1
        for(i = d - 1; i >= -1; i--)
        {
            if(i == -1)
            {
                overflow = 1;
                break;
            }

            if(disp_vec[i] == r) //Have carry, do not break
            {
                disp_vec[i] = -r;
            }
            else
            {
                disp_vec[i]++;
                break;
            }
        }
    }

    qsort(srcs, indgr, sizeof(*srcs), comp);
    qsort(dests, outdgr, sizeof(*dests), comp);


    //Returning all values
    *indegree_ptr = indgr;
    *sources_ptr = srcs;
    *sourcesweights_ptr = srcwghts;
    *outdegree_ptr = outdgr;
    *destinations_ptr = dests;
    *destweights_ptr = destwghts;

    MPI_Comm_free(&cart_comm);
    return 0;
}

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	int my_rank, comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Status status[50];

	int i, j, kk, msg_size, ITER, skip, persistency, shm_impl;
	int d, r;

	d = atoi(argv[1]);
	r = atoi(argv[2]);
	ITER = 1000;
    persistency = 0;

	//Defining the neighborhood
	int indgr, outdgr;
	int *srcs, *srcwghts, *dests, *destwghts;
	make_nbrhood(MPI_COMM_WORLD, d, r,
	             &indgr, &srcs, &srcwghts,
	             &outdgr, &dests, &destwghts);

    //Create a communicator with the topology information attached
    MPI_Comm nbr_comm;
    double start_time0, end_time0;
    start_time0 = MPI_Wtime();
    MPI_Dist_graph_create_adjacent(MPI_COMM_WORLD,
                                   indgr, srcs, srcwghts,
                                   outdgr, dests, destwghts,
                                   MPI_INFO_NULL, 0, &nbr_comm);
    MPI_Barrier(MPI_COMM_WORLD);
    end_time0 = MPI_Wtime();

    if(my_rank == 0) {
        printf("Total time to make communication pattern = %lf  (s)\n", end_time0 - start_time0);
    }

#ifdef ERROR_CHECK
    int num_msg_sizes = 1;
    int msg_sizes[1] = {32768};
#else
    int num_msg_sizes = 11;
    int msg_sizes[11] = {4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304};
#endif

    int max_msg_size = msg_sizes[num_msg_sizes - 1];
    Datatype *sendbuf = (Datatype*) malloc(max_msg_size * sizeof(Datatype));
    Datatype *recvbuf = (Datatype*) calloc(indgr * max_msg_size, sizeof(Datatype));


    for(i = 0; i < max_msg_size; i++)
   	    sendbuf[i] = my_rank;

    MPI_Request req;

    for(kk = 0; kk < num_msg_sizes; kk++)
    {
    	msg_size = msg_sizes[kk];
    	if(my_rank == 0)
    		printf("------ Starting the experimet with %d Byte(s)------\n",
    				msg_size);

    	if(msg_size <524288)
    		ITER = 500;
    	else
    		ITER = 300;

    	skip = 0; //ITER / 10;
    	double start_time, end_time;
    	for(i = 0; i < ITER; i++)
    	{
    		if(i == skip)
    			start_time = MPI_Wtime();

    		MPI_Ineighbor_allgather(sendbuf, msg_size, Type_MPI,
    				recvbuf, msg_size, Type_MPI,
					nbr_comm, &req);

   		MPI_Wait(&req, MPI_STATUS_IGNORE);


#ifdef ERROR_CHECK
    			for(j = 0; j < indgr; j++)
    			{
				int m;
				for(m=0;m<msg_size;m++)
				{
    				if(recvbuf[(j*msg_size)+m] != srcs[j])
    				{
    					printf("Rank %d, PID%d, ITER%d: ERROR: recv buffer =%d and src=%d, index %d\n", my_rank, getpid(), i, recvbuf[j], srcs[j], j);
    				}
				}
    			}
#endif
    	}

    	MPI_Barrier(MPI_COMM_WORLD);
    	end_time = MPI_Wtime();

    	if(my_rank == 0)
    	{
    		printf("Total communication time = %lf  (s)\n", end_time - start_time);
    	}
    }

    free(sendbuf);
    free(recvbuf);

    MPI_Comm_free(&nbr_comm);
    MPI_Finalize();
    return 0;
}

