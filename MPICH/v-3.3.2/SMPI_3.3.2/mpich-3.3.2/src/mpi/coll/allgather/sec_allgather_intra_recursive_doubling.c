#include "mpiimpl.h"

/*
 * Secure Recursive Doubling Algorithm:
 *
 * Restrictions: power-of-two no. of processes
 *
 * Cost = TBD
 *
 *
 */


unsigned char ciphertext_sendbuf[4194304*2+20];
unsigned char ciphertext_recvbuf[268435456+4000];



#undef FUNCNAME
#define FUNCNAME MPIR_SEC_Allgather_intra_recursive_doubling
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_SEC_Allgather_intra_recursive_doubling(const void *sendbuf,
											int sendcount,
											MPI_Datatype sendtype,
											void *recvbuf,
											int recvcount,
											MPI_Datatype recvtype,
											MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag)
{
	int comm_size, rank;
	int mpi_errno = MPI_SUCCESS, mpi_rcv_errno=MPI_SUCCESS;
	int mpi_errno_ret = MPI_SUCCESS;
	MPI_Aint recvtype_extent;
	int j, i;
	MPI_Aint curr_cnt, last_recv_cnt = 0;
	int dst;
	MPI_Status status;
	int mask, dst_tree_root, my_tree_root,
		send_offset, recv_offset, nprocs_completed, k, offset, tmp_mask, tree_root;

	if (((sendcount == 0) && (sendbuf != MPI_IN_PLACE)) || (recvcount == 0))
		return MPI_SUCCESS;

	comm_size = comm_ptr->local_size;
	rank = comm_ptr->rank;
	if(rank==0){
	  printf("Secure RD is called!\n");
	  fflush(stdout);
	}
#ifdef HAVE_ERROR_CHECKING
	/* Currently this algorithm can only handle power-of-2 comm_size.
	 * Non power-of-2 comm_size is still experimental */
	MPIR_Assert(!(comm_size & (comm_size - 1)));
#endif /* HAVE_ERROR_CHECKING */

	MPIR_Datatype_get_extent_macro(recvtype, recvtype_extent);

	/* This is the largest offset we add to recvbuf */
	MPIR_Ensure_Aint_fits_in_pointer(MPIR_VOID_PTR_CAST_TO_MPI_AINT recvbuf +
									 (comm_size * recvcount * recvtype_extent));

	/**********Added by Mehran **********/
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

	enc_recv_size = (recvcount*recvtype_sz)+16+12;
	RAND_bytes(ciphertext_sendbuf, 12); // 12 bytes of nonce
	if(!EVP_AEAD_CTX_seal(ctx, ciphertext_sendbuf+12,
	  &ciphertext_sendbuf_len, max_out_len,
	  ciphertext_sendbuf, 12,
	  sendbuf,  t,
	  NULL, 0)){
	  printf("Error in encryption: allgather\n");
	fflush(stdout);
	}


	/*
	* Posting the first send and receive
	*/

	curr_cnt = enc_recv_size;

	mask = 0x1;
	i = 0;
	dst = rank ^ mask;

	/* find offset into send and recv buffers. zero out
	 * the least significant "i" bits of rank and dst to
	 * find root of src and dst subtrees. Use ranks of
	 * roots as index to send from and recv into buffer */

	dst_tree_root = dst >> i;
	dst_tree_root <<= i;

	my_tree_root = rank >> i;
	my_tree_root <<= i;

	/* FIXME: saving an MPI_Aint into an int */
	send_offset = my_tree_root * enc_recv_size;
	recv_offset = dst_tree_root * enc_recv_size;

	

	MPIR_Request *recv_req_ptr[comm_size-1], *send_req_ptr[comm_size-1];
	int p;
	for(p=0; p<comm_size-1; ++p){
	  (recv_req_ptr[p])=NULL;
	  (send_req_ptr[p])=NULL;
	}
	context_id = (comm_ptr->comm_kind == MPIR_COMM_KIND__INTRACOMM) ?
		  MPIR_CONTEXT_INTRA_COLL : MPIR_CONTEXT_INTER_COLL;

	  mpi_errno = MPID_Irecv((char*)ciphertext_recvbuf+recv_offset, enc_recv_size, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
							 comm_ptr, context_id, &(recv_req_ptr[0]));
	  if (mpi_errno){
		  MPIR_ERR_POP(mpi_errno);
		  mpi_rcv_errno = mpi_errno;
	  }

	  mpi_errno = MPID_Isend(ciphertext_sendbuf, curr_cnt, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
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
	  
	/* Copy the local encrypted piece of data to the ciphertext_recvbuf*/  
	  mpi_errno = MPIR_Localcopy(ciphertext_sendbuf, enc_recv_size, MPI_CHAR,
		((char *) ciphertext_recvbuf +
		  rank * enc_recv_size), enc_recv_size, MPI_CHAR);
	  if (mpi_errno) {
		MPIR_ERR_POP(mpi_errno);
	  }
	}

		
	/*
	* Waiting for the receive
	*/
	
	  mpi_errno = MPIC_Wait((recv_req_ptr[0]), errflag);
	  if (mpi_errno){
		  MPIR_ERR_POPFATAL(mpi_errno);
		  printf("Error in Wait 1 at S_RD\n");
	  }

	  *(&status) = (recv_req_ptr[0])->status;


	  if (mpi_errno == MPI_SUCCESS) {
		  mpi_errno = recv_req_ptr[0]->status.MPI_ERROR;
	  }else{
	  	printf("Error in status check 1 at S_RD\n");
	  }

	  MPIR_Request_free(recv_req_ptr[0]);


	  if (mpi_rcv_errno) {
			/* for communication errors, just record the error but continue */
			*errflag =
				MPIX_ERR_PROC_FAILED ==
				MPIR_ERR_GET_CLASS(mpi_rcv_errno) ? MPIR_ERR_PROC_FAILED : MPIR_ERR_OTHER;
			MPIR_ERR_SET(mpi_rcv_errno, *errflag, "**fail");
			MPIR_ERR_ADD(mpi_errno_ret, last_recv_cnt);
			last_recv_cnt = 0;
		} 
		curr_cnt*=2;

	  mask <<= 1;
	  i=1;
	  
	  while (mask < comm_size) {
		dst = rank ^ mask;

		/* find offset into send and recv buffers. zero out
		 * the least significant "i" bits of rank and dst to
		 * find root of src and dst subtrees. Use ranks of
		 * roots as index to send from and recv into buffer */

		dst_tree_root = dst >> i;
		dst_tree_root <<= i;

		my_tree_root = rank >> i;
		my_tree_root <<= i;

		/* FIXME: saving an MPI_Aint into an int */
		send_offset = my_tree_root * enc_recv_size;
		recv_offset = dst_tree_root * enc_recv_size;

		if (dst < comm_size) {
			
			mpi_errno = MPID_Irecv((char*)ciphertext_recvbuf+recv_offset, (comm_size - dst_tree_root) *  enc_recv_size, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
							 comm_ptr, context_id, &(recv_req_ptr[i]));
			if (mpi_errno){
				MPIR_ERR_POP(mpi_errno);
				mpi_rcv_errno = mpi_errno;
			}
			
			mpi_errno = MPID_Isend(ciphertext_recvbuf + send_offset, curr_cnt, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
								 comm_ptr, context_id, &(send_req_ptr[i]));
			if (mpi_errno)
				MPIR_ERR_POP(mpi_errno);

		}


	//Decrypt Previously received data and move to the recv_buffer 

		//first, we need to compute the previous send and recv offsets:

		int prev_dst, prev_mask, prev_dst_tree_root, prev_my_tree_root, prev_send_offset, prev_recv_offset, prev_i;
		prev_i		= 	i-1;
		prev_mask	=	mask >> 1;

		prev_dst = rank ^ prev_mask;

		prev_dst_tree_root = prev_dst >> prev_i;
		prev_dst_tree_root <<= prev_i;

		prev_my_tree_root = rank >> prev_i;
		prev_my_tree_root <<= prev_i;

		prev_send_offset = prev_my_tree_root * enc_recv_size;
		prev_recv_offset = prev_dst_tree_root * enc_recv_size;


		//Now, we compute the offsets of the previously received messages in the buffer

		unsigned long dec_begin_offset, dec_end_offset; //these offsets indicate which part of the receive buffer should be decrypted
		int number_of_received_msgs = 1<< prev_i, err_num;
		dec_begin_offset = prev_recv_offset;
        if(prev_send_offset<prev_recv_offset){
        	dec_end_offset = prev_recv_offset + number_of_received_msgs * (enc_recv_size);
        }else{
        	dec_end_offset = prev_send_offset;
        }

 		unsigned long decrypted_msg_begin_offset = prev_dst_tree_root * recvcount * recvtype_extent;
 		unsigned long decrypted_msg_len = 0;
        for (int idx=0; idx<number_of_received_msgs; ++idx){
        	err_num = EVP_AEAD_CTX_open(ctx, (recvbuf+decrypted_msg_begin_offset+(idx*recvcount * recvtype_extent)),
	              &decrypted_msg_len, (unsigned long )((recvcount * recvtype_extent)+16),
	               (ciphertext_recvbuf+dec_begin_offset+idx*enc_recv_size), 12,
	              (ciphertext_recvbuf+dec_begin_offset+12+idx*enc_recv_size), (unsigned long )(enc_recv_size -12),
	              NULL, 0);
        	if(!err_num){
		        printf("Failed Decryption #%d in iteration %d by %d decrypted_msg_begin_offset: %d, added by: %d, decrypted_msg_len: %d, dec_begin_offset: %d\n", idx, i, rank, decrypted_msg_begin_offset, (idx*recvcount * recvtype_extent), decrypted_msg_len, dec_begin_offset+idx*enc_recv_size);
		        fflush(stdout);        
	      }
        }//end for
		
	
        /*
		* Waiting for the receives
		*/

		mpi_errno = MPIC_Wait((recv_req_ptr[i]), errflag);
		if (mpi_errno){
		  MPIR_ERR_POPFATAL(mpi_errno);
		}
		
		*(&status) = (recv_req_ptr[i])->status;

		if (mpi_errno == MPI_SUCCESS) {
		  mpi_errno = recv_req_ptr[i]->status.MPI_ERROR;
		}

		MPIR_Request_free(recv_req_ptr[i]);


		if (mpi_rcv_errno) {
				/* for communication errors, just record the error but continue */
				*errflag =
					MPIX_ERR_PROC_FAILED ==
					MPIR_ERR_GET_CLASS(mpi_rcv_errno) ? MPIR_ERR_PROC_FAILED : MPIR_ERR_OTHER;
				MPIR_ERR_SET(mpi_rcv_errno, *errflag, "**fail");
				MPIR_ERR_ADD(mpi_errno_ret, mpi_rcv_errno);
				last_recv_cnt = 0;
			} 
			curr_cnt*=2;
			
		mask <<= 1;
        i++;

	}//end while

	
	//Last Decryption

		//first, we need to compute the previous send and recv offsets:

		int prev_dst, prev_mask, prev_dst_tree_root, prev_my_tree_root, prev_send_offset, prev_recv_offset, prev_i;
		prev_i		= 	i-1;
		prev_mask	=	mask >> 1;

		prev_dst = rank ^ prev_mask;

		prev_dst_tree_root = prev_dst >> prev_i;
		prev_dst_tree_root <<= prev_i;

		prev_my_tree_root = rank >> prev_i;
		prev_my_tree_root <<= prev_i;

		prev_send_offset = prev_my_tree_root * enc_recv_size;
		prev_recv_offset = prev_dst_tree_root * enc_recv_size;


		//Now, we compute the offsets of the previously received messages in the buffer

		unsigned long dec_begin_offset, dec_end_offset; //these offsets indicate which part of the receive buffer should be decrypted
		int number_of_received_msgs = 1<< prev_i, err_num;
		dec_begin_offset = prev_recv_offset;
        if(prev_send_offset<prev_recv_offset){
        	dec_end_offset = prev_recv_offset + number_of_received_msgs * (enc_recv_size);
        }else{
        	dec_end_offset = prev_send_offset;
        }

 		unsigned long decrypted_msg_begin_offset = prev_dst_tree_root * recvcount * recvtype_extent;
 		unsigned long decrypted_msg_len = 0;
        for (int idx=0; idx<number_of_received_msgs; ++idx){
        	
        	err_num = EVP_AEAD_CTX_open(ctx, (recvbuf+decrypted_msg_begin_offset+(idx*recvcount * recvtype_extent)),
	              &decrypted_msg_len, (unsigned long )((recvcount * recvtype_extent)+16),
	               (ciphertext_recvbuf+dec_begin_offset+idx*enc_recv_size), 12,
	              (ciphertext_recvbuf+dec_begin_offset+12+idx*enc_recv_size), (unsigned long )(enc_recv_size -12),
	              NULL, 0);
        	if(!err_num){
		        printf("Failed Decryption #%d in iteration %d by %d decrypted_msg_begin_offset: %d, added by: %d, decrypted_msg_len: %d, dec_begin_offset: %d\n", idx, i, rank, decrypted_msg_begin_offset, (idx*recvcount * recvtype_extent), decrypted_msg_len, dec_begin_offset+idx*enc_recv_size);
		        fflush(stdout);        
	      }
        }


		//post wait for each of the sends
        for(p=0; p<i; ++p){
	        mpi_errno = MPIC_Wait((send_req_ptr[p]), errflag);
	        if (mpi_errno)
	            MPIR_ERR_POP(mpi_errno);
	        

	        if (mpi_errno == MPI_SUCCESS) {
	            mpi_errno = send_req_ptr[p]->status.MPI_ERROR;
	        }

	        MPIR_Request_free(send_req_ptr[p]);
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
