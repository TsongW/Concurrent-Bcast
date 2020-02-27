#include "mpiimpl.h"


/*Added by Mehran*/

// unsigned char ciphertext[4194304+18];
// EVP_AEAD_CTX *ctx = NULL;
// unsigned char key [32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
// unsigned char nonce[12] = {'1','2','3','4','5','6','7','8','9','0','1','2'};  
// int nonceCounter; 


unsigned char ciphertext_sendbuf[4194304*2+20];
unsigned char ciphertext_recvbuf[268435456+4000];
/****************/







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
	MPI_Status status;

	if (((sendcount == 0) && (sendbuf != MPI_IN_PLACE)) || (recvcount == 0))
		return MPI_SUCCESS;

	comm_size = comm_ptr->local_size;
	rank = comm_ptr->rank;
	if(rank==0){
	  printf("Base Ring is called!\n");
	  fflush(stdout);
	}
	MPIR_Datatype_get_extent_macro(recvtype, recvtype_extent);

	/* This is the largest offset we add to recvbuf */
	MPIR_Ensure_Aint_fits_in_pointer(MPIR_VOID_PTR_CAST_TO_MPI_AINT recvbuf +
									 (comm_size * recvcount * recvtype_extent));




	int sendtype_sz, recvtype_sz, enc_recv_size, context_id;
	unsigned long  ciphertext_sendbuf_len = 0;
	sendtype_sz= recvtype_sz= 0;


	 /*First, encrypt the local data, do the first send and post the first receive request
			* Then, do the local copy and wait for the first receive
			*/

			/*
			* encrypting the local data
			*/


			MPI_Type_size(sendtype, &sendtype_sz);
			MPI_Type_size(recvtype, &recvtype_sz);
			
			unsigned long t=0;
			t = (unsigned long)(sendtype_sz*sendcount);
			unsigned long   max_out_len = (unsigned long) (16 + (sendtype_sz*sendcount));
			

			//#TODO: Dynamically allocate memory

			// char* ciphertext_recvbuf , *ciphertext_sendbuf;
			// ciphertext_recvbuf = (char *) malloc(max_out_len*(comm_size-1) * size_of(char));
			// ciphertext_sendbuf = (char *) malloc(max_out_len * size_of(char));

			// enc_recv_size = (recvcount*recvtype_sz)+16+12;

			enc_recv_size = (recvcount*recvtype_sz);




			// RAND_bytes(ciphertext_sendbuf, 12); // 12 bytes of nonce
			// if(!EVP_AEAD_CTX_seal(ctx, ciphertext_sendbuf+12,
			//   &ciphertext_sendbuf_len, max_out_len,
			//   ciphertext_sendbuf, 12,
			//   sendbuf,  t,
			//   NULL, 0)){
			//   printf("Error in encryption: allgather\n");
			// fflush(stdout);
			// }


			/*
			* Posting the first send and recieve
			*/
			left = (comm_size + rank - 1) % comm_size;
			right = (rank + 1) % comm_size;
			MPIR_Request *recv_req_ptr[comm_size-1], *send_req_ptr[comm_size-1];
			int p;
			for(p=0; p<comm_size-1; ++p){
			  (recv_req_ptr[p])=NULL;
			  (send_req_ptr[p])=NULL;
			}
			context_id = (comm_ptr->comm_kind == MPIR_COMM_KIND__INTRACOMM) ?
				  MPIR_CONTEXT_INTRA_COLL : MPIR_CONTEXT_INTER_COLL;


			  j=rank;
			  jnext= left;
			  mpi_errno = MPID_Irecv((char*)recvbuf+(jnext*(enc_recv_size)), enc_recv_size, MPI_CHAR, left, MPIR_ALLGATHER_TAG,
									 comm_ptr, context_id, &(recv_req_ptr[0]));
			  if (mpi_errno)
				  MPIR_ERR_POP(mpi_errno);


			  mpi_errno = MPID_Isend(sendbuf, ciphertext_sendbuf_len+12, MPI_CHAR, right, MPIR_ALLGATHER_TAG,
									 comm_ptr, context_id, &(send_req_ptr[0]));
			  if (mpi_errno)
				  MPIR_ERR_POP(mpi_errno);



			  
			  


			

			/* Now, load the "local" version in the recvbuf. */
			if (sendbuf != MPI_IN_PLACE) {
			  mpi_errno = MPIR_Localcopy(sendbuf, sendcount, sendtype,
				((char *) recvbuf +
				  rank * recvcount * recvtype_extent), recvcount, recvtype);
			  if (mpi_errno) {
				MPIR_ERR_POP(mpi_errno);
			  }
			}
			/*
			* Posting the first receive and waiting for the receive
			*/
			

			  mpi_errno = MPIC_Wait((recv_req_ptr[0]), errflag);
			  if (mpi_errno)
				  MPIR_ERR_POPFATAL(mpi_errno);


			  *(&status) = (recv_req_ptr[0])->status;



			  if (mpi_errno == MPI_SUCCESS) {
				  mpi_errno = recv_req_ptr[0]->status.MPI_ERROR;
			  }

			  MPIR_Request_free(recv_req_ptr[0]);

			/*added by Mehran*/

			/*
			 * Now, send left to right.  This fills in the receive area in
			 * reverse order.
			 */

			unsigned long next, dest, count=0;

			j = left;
			jnext = (comm_size + left - 1) % comm_size;

			for (i = 2; i < comm_size; i++) {


			  mpi_errno = MPID_Irecv((char*)recvbuf+(jnext*(enc_recv_size)), enc_recv_size, MPI_CHAR, left, MPIR_ALLGATHER_TAG,
									 comm_ptr, context_id, &(recv_req_ptr[i-1]));
			  if (mpi_errno)
				  MPIR_ERR_POP(mpi_errno);


			  mpi_errno = MPID_Isend((char*)recvbuf + j*(enc_recv_size), ciphertext_sendbuf_len+12, MPI_CHAR, right, MPIR_ALLGATHER_TAG,
									 comm_ptr, context_id, &(send_req_ptr[i-1]));
			  if (mpi_errno)
				  MPIR_ERR_POP(mpi_errno);


			  if (mpi_errno) {
				/* for communication errors, just record the error but continue */
			  *errflag =
			  MPIX_ERR_PROC_FAILED ==
			  MPIR_ERR_GET_CLASS(mpi_errno) ? MPIR_ERR_PROC_FAILED : MPIR_ERR_OTHER;
			  MPIR_ERR_SET(mpi_errno, *errflag, "**fail");
			  MPIR_ERR_ADD(mpi_errno_ret, mpi_errno);
			}


			  //Decrypt Previously received data and move to the recv_buffer 
				
			 //  next =(unsigned long )(j*enc_recv_size);
			 //  dest =(unsigned long )(j*(recvcount*recvtype_sz));

			 //  if(!EVP_AEAD_CTX_open(ctx, (recvbuf+dest),
				// 	&count, (unsigned long )((recvcount*recvtype_sz)+16),
				// 	 (ciphertext_recvbuf+next), 12,
				// 	(ciphertext_recvbuf+next+12), (unsigned long )((recvcount*recvtype_sz)+16),
				// 	NULL, 0)){
				// printf("Decryption error: allgather\n");
			 //  fflush(stdout);        
			 //  }




			  mpi_errno = MPIC_Wait((recv_req_ptr[i-1]), errflag);
				if (mpi_errno)
					MPIR_ERR_POPFATAL(mpi_errno);
			   
				*(&status) = recv_req_ptr[i-1]->status;

				if (mpi_errno == MPI_SUCCESS) {
					mpi_errno = recv_req_ptr[i-1]->status.MPI_ERROR;
				}

				MPIR_Request_free(recv_req_ptr[i-1]);

				
			  j = jnext;
			  jnext = (comm_size + jnext - 1) % comm_size;
			}


			//Do the last decryption

			// next =(unsigned long )(j*enc_recv_size);
			//   dest =(unsigned long )(j*(recvcount*recvtype_sz));

			// if(!EVP_AEAD_CTX_open(ctx, ((recvbuf+dest)),
			// 				  &count, (unsigned long )((recvcount*recvtype_sz)+16),
			// 				   (ciphertext_recvbuf+next), 12,
			// 				  (ciphertext_recvbuf+next+12), (unsigned long )((recvcount*recvtype_sz)+16),
			// 				  NULL, 0)){
			// 			  printf("Decryption error: allgather\n");
			// 			fflush(stdout);        
			//   }

			  //post wait for each of the sends
			  for(i=0; i<comm_size-1; ++i){
				mpi_errno = MPIC_Wait((send_req_ptr[i]), errflag);
				if (mpi_errno)
					MPIR_ERR_POP(mpi_errno);
				

				if (mpi_errno == MPI_SUCCESS) {
					mpi_errno = send_req_ptr[i]->status.MPI_ERROR;
				}

				MPIR_Request_free(send_req_ptr[i]);
			  }


  fn_exit:
	if (mpi_errno_ret)
		mpi_errno = mpi_errno_ret;
	else if (*errflag != MPIR_ERR_NONE)
		MPIR_ERR_SET(mpi_errno, *errflag, "**coll_fail");

	return mpi_errno;

  fn_fail:
	goto fn_exit;
}


	