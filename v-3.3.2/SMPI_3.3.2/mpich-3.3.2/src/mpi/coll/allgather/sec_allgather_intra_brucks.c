/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#include "mpiimpl.h"

/* Algorithm: Bruck's
 *
 * This algorithm is from the IEEE TPDS Nov 97 paper by Jehoshua Bruck
 * et al.  It is a variant of the disemmination algorithm for barrier.
 * It takes ceiling(lg p) steps.
 *
 * Cost = lgp.alpha + n.((p-1)/p).beta
 * where n is total size of data gathered on each process.
 */


unsigned char ciphertext_sendbuf[4194304*2+20];
unsigned char ciphertext_recvbuf[268435456+4000];


#undef FUNCNAME
#define FUNCNAME MPIR_SEC_Allgather_intra_brucks
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_SEC_Allgather_intra_brucks(const void *sendbuf,
	int sendcount,
	MPI_Datatype sendtype,
	void *recvbuf,
	int recvcount,
	MPI_Datatype recvtype,
	MPIR_Comm * comm_ptr, MPIR_Errflag_t * errflag){

	int comm_size, rank;
	int mpi_errno = MPI_SUCCESS, mpi_rcv_errno=MPI_SUCCESS;
	int mpi_errno_ret = MPI_SUCCESS;
	MPI_Aint recvtype_extent;
	MPI_Aint recvtype_true_extent, recvbuf_extent, recvtype_true_lb;
	int pof2, src, rem;
	void *tmp_buf = NULL;
	int curr_cnt, dst;
	MPI_Status status;
	MPIR_CHKLMEM_DECL(1);

	if (((sendcount == 0) && (sendbuf != MPI_IN_PLACE)) || (recvcount == 0))
		return MPI_SUCCESS;

	comm_size = comm_ptr->local_size;
	rank = comm_ptr->rank;
	if(rank==0){
		printf("Secure Bruck is called!\n");
		fflush(stdout);
	}
	MPIR_Datatype_get_extent_macro(recvtype, recvtype_extent);

	/* This is the largest offset we add to recvbuf */
	MPIR_Ensure_Aint_fits_in_pointer(MPIR_VOID_PTR_CAST_TO_MPI_AINT recvbuf +
		(comm_size * recvcount * recvtype_extent));

	int r=1, nr=0;

	while(r<comm_size){
		++nr;
		r*=2;
	}
	
	MPIR_Request *recv_req_ptr[nr], *send_req_ptr[nr];
	int p;
	for(p=0; p<nr; ++p){
		(recv_req_ptr[p])=NULL;
		(send_req_ptr[p])=NULL;
	}


	/* allocate a temporary buffer of the same size as recvbuf. */

	/* get true extent of recvtype */
	MPIR_Type_get_true_extent_impl(recvtype, &recvtype_true_lb, &recvtype_true_extent);

	recvbuf_extent = comm_size * recvcount * (MPL_MAX(recvtype_true_extent, recvtype_extent));

	MPIR_CHKLMEM_MALLOC(tmp_buf, void *, recvbuf_extent, mpi_errno, "tmp_buf", MPL_MEM_BUFFER);

		/* adjust for potential negative lower bound in datatype */
	tmp_buf = (void *) ((char *) tmp_buf - recvtype_true_lb);



	/**********Added by Mehran **********/
	int sendtype_sz, recvtype_sz, enc_recv_size, context_id;
	unsigned long  ciphertext_sendbuf_len = 0;
	sendtype_sz= recvtype_sz= 0;



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

	// enc_recv_size = (recvcount*recvtype_sz);

	RAND_bytes(ciphertext_sendbuf, 12); // 12 bytes of nonce
	if(!EVP_AEAD_CTX_seal(ctx, ciphertext_sendbuf+12,
		&ciphertext_sendbuf_len, max_out_len,
		ciphertext_sendbuf, 12,
		sendbuf,  t,
		NULL, 0)){
			printf("Error in encryption: allgather\n");
		fflush(stdout);
	}

	
	// printf("Rank %d reached checkpoint 0\n", rank);




	/*
	* Posting the first send and receive
	*/
	
	context_id = (comm_ptr->comm_kind == MPIR_COMM_KIND__INTRACOMM) ?
	MPIR_CONTEXT_INTRA_COLL : MPIR_CONTEXT_INTER_COLL;

	curr_cnt = enc_recv_size;

	pof2 = 1;


	src = (rank + pof2) % comm_size;
	dst = (rank - pof2 + comm_size) % comm_size;

	// printf("Rank %d wants to receive %d from %d at %d in receive 1\n",rank, enc_recv_size, src, enc_recv_size);
	// mpi_errno = MPID_Irecv((char*)tmp_buf+enc_recv_size, enc_recv_size, MPI_CHAR, src, MPIR_ALLGATHER_TAG,
	// 	comm_ptr, context_id, &(recv_req_ptr[0]));
	// if (mpi_errno){
	// 	MPIR_ERR_POP(mpi_errno);
	// 	mpi_rcv_errno = mpi_errno;
	// }


	mpi_errno = MPID_Irecv((char*)ciphertext_recvbuf+enc_recv_size, enc_recv_size, MPI_CHAR, src, MPIR_ALLGATHER_TAG,
		comm_ptr, context_id, &(recv_req_ptr[0]));
	if (mpi_errno){
		MPIR_ERR_POP(mpi_errno);
		mpi_rcv_errno = mpi_errno;
	}

	// mpi_errno = MPID_Isend(tmp_buf, enc_recv_size, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
	// 	comm_ptr, context_id, &(send_req_ptr[0]));
	// if (mpi_errno)
	// 	MPIR_ERR_POP(mpi_errno);


	mpi_errno = MPID_Isend(ciphertext_sendbuf, enc_recv_size, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
		comm_ptr, context_id, &(send_req_ptr[0]));
	if (mpi_errno)
		MPIR_ERR_POP(mpi_errno);

	// printf("Rank %d reached checkpoint 2\n", rank);

		/* copy local data to the top of tmp_buf */
	if (sendbuf != MPI_IN_PLACE) {
		mpi_errno = MPIR_Localcopy(sendbuf, sendcount, sendtype, tmp_buf, recvcount, recvtype);
		if (mpi_errno) {
			MPIR_ERR_POP(mpi_errno);
		}
	} else {
		mpi_errno = MPIR_Localcopy(((char *) recvbuf +
			rank * recvcount * recvtype_extent),
		recvcount, recvtype, tmp_buf, recvcount, recvtype);
		if (mpi_errno) {
			MPIR_ERR_POP(mpi_errno);
		}
	}

	// printf("Rank %d reached checkpoint 1\n", rank);

	/* Copy the local encrypted piece of data to the ciphertext_recvbuf*/  
	mpi_errno = MPIR_Localcopy(ciphertext_sendbuf, enc_recv_size, MPI_CHAR,
		(char *) ciphertext_recvbuf, enc_recv_size, MPI_CHAR);
	if (mpi_errno) {
		MPIR_ERR_POP(mpi_errno);
	}

	// printf("Rank %d reached checkpoint 3\n", rank);


	
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
		MPIR_ERR_ADD(mpi_errno_ret, mpi_rcv_errno);
	}
	curr_cnt *= 2;
	pof2 *= 2;

	//printf("Rank %d reached checkpoint 4\n", rank);



		/* do the \floor(\lg p)-1 steps */
	int iteration=1, total_number_of_recv_msgs=1, err_num=0, number_of_received_msgs;
	unsigned long decrypted_msg_len = 0;
	while (pof2 <= comm_size / 2) {
		src = (rank + pof2) % comm_size;
		dst = (rank - pof2 + comm_size) % comm_size;


		// mpi_errno = MPID_Irecv((char*)tmp_buf+curr_cnt, curr_cnt, MPI_CHAR, src, MPIR_ALLGATHER_TAG,
		// 	comm_ptr, context_id, &(recv_req_ptr[iteration]));
		// if (mpi_errno){
		// 	MPIR_ERR_POP(mpi_errno);
		// 	mpi_rcv_errno = mpi_errno;
		// }

		mpi_errno = MPID_Irecv((char*)ciphertext_recvbuf+curr_cnt, curr_cnt, MPI_CHAR, src, MPIR_ALLGATHER_TAG,
			comm_ptr, context_id, &(recv_req_ptr[iteration]));
		if (mpi_errno){
			MPIR_ERR_POP(mpi_errno);
			mpi_rcv_errno = mpi_errno;
		}



		// mpi_errno = MPID_Isend(tmp_buf, curr_cnt, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
		// 	comm_ptr, context_id, &(send_req_ptr[iteration]));
		// if (mpi_errno)
		// 	MPIR_ERR_POP(mpi_errno);


		mpi_errno = MPID_Isend(ciphertext_recvbuf, curr_cnt, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
			comm_ptr, context_id, &(send_req_ptr[iteration]));
		if (mpi_errno)
			MPIR_ERR_POP(mpi_errno);


			  /*Decrypt previously received data*/
		number_of_received_msgs = (curr_cnt/2)/enc_recv_size;
		

		for (int idx=0; idx<number_of_received_msgs; ++idx){
			err_num = EVP_AEAD_CTX_open(ctx, (tmp_buf+(total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent)),
				&decrypted_msg_len, (unsigned long )((recvcount * recvtype_extent)+16),
				(ciphertext_recvbuf+(total_number_of_recv_msgs+idx)*enc_recv_size), 12,
				(ciphertext_recvbuf+(total_number_of_recv_msgs + idx) * (enc_recv_size) + 12), (unsigned long )(enc_recv_size -12),
				NULL, 0);
			if(!err_num){
				printf("Failed Decryption #%d in iteration %d by %d\nTried to decrypt at %d and put at (%d+%d)*%d=%d\n", idx, iteration, rank, (total_number_of_recv_msgs+idx)*enc_recv_size, total_number_of_recv_msgs, idx, (recvcount * recvtype_extent), (total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent));
				fflush(stdout);        
			}
		}//end for

		total_number_of_recv_msgs += number_of_received_msgs;


		/*
		* Waiting for the receives
		*/

		mpi_errno = MPIC_Wait((recv_req_ptr[iteration]), errflag);
		if (mpi_errno){
			MPIR_ERR_POPFATAL(mpi_errno);
		}
		
		*(&status) = (recv_req_ptr[iteration])->status;

		if (mpi_errno == MPI_SUCCESS) {
			mpi_errno = recv_req_ptr[iteration]->status.MPI_ERROR;
		}

		MPIR_Request_free(recv_req_ptr[iteration]);
		

		if (mpi_rcv_errno) {
			/* for communication errors, just record the error but continue */
			*errflag =
			MPIX_ERR_PROC_FAILED ==
			MPIR_ERR_GET_CLASS(mpi_rcv_errno) ? MPIR_ERR_PROC_FAILED : MPIR_ERR_OTHER;
			MPIR_ERR_SET(mpi_rcv_errno, *errflag, "**fail");
			MPIR_ERR_ADD(mpi_errno_ret, mpi_rcv_errno);
		}
		curr_cnt *= 2;
		pof2 *= 2;
		++iteration;
	}//end While

	//printf("Rank %d reached checkpoint 5\n", rank);



	/* if comm_size is not a power of two, one more step is needed */

	rem = comm_size - pof2;

	if(rank==0){
		printf("%d are remaining\n", rem);
	}

	if (rem) {
		src = (rank + pof2) % comm_size;
		dst = (rank - pof2 + comm_size) % comm_size;


		// mpi_errno = MPID_Irecv((char*)tmp_buf+curr_cnt, rem*enc_recv_size, MPI_CHAR, src, MPIR_ALLGATHER_TAG,
		// 	comm_ptr, context_id, &(recv_req_ptr[iteration]));
		// if (mpi_errno){
		// 	MPIR_ERR_POP(mpi_errno);
		// 	mpi_rcv_errno = mpi_errno;
		// }

		printf("%d wants to recv %d from %d at %d\n", rank, rem*enc_recv_size, src, curr_cnt);
		mpi_errno = MPID_Irecv((char*)ciphertext_recvbuf+curr_cnt, rem*enc_recv_size, MPI_CHAR, src, MPIR_ALLGATHER_TAG,
			comm_ptr, context_id, &(recv_req_ptr[iteration]));
		if (mpi_errno){
			MPIR_ERR_POP(mpi_errno);
			mpi_rcv_errno = mpi_errno;
		}

		// mpi_errno = MPID_Isend(tmp_buf, rem*enc_recv_size, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
		// 	comm_ptr, context_id, &(send_req_ptr[iteration]));
		// if (mpi_errno)
		// 	MPIR_ERR_POP(mpi_errno);


		printf("%d wants to send %d to %d\n", rank, rem*enc_recv_size, dst);
		mpi_errno = MPID_Isend(ciphertext_recvbuf, rem*enc_recv_size, MPI_CHAR, dst, MPIR_ALLGATHER_TAG,
			comm_ptr, context_id, &(send_req_ptr[iteration]));
		if (mpi_errno)
			MPIR_ERR_POP(mpi_errno);


		  /*Decrypt previously received data*/
		number_of_received_msgs = (curr_cnt/2)/enc_recv_size;
		
		decrypted_msg_len = 0;
		for (int idx=0; idx<number_of_received_msgs; ++idx){
			err_num = EVP_AEAD_CTX_open(ctx, (tmp_buf+(total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent)),
				&decrypted_msg_len, (unsigned long )((recvcount * recvtype_extent)+16),
				(ciphertext_recvbuf+(total_number_of_recv_msgs+idx)*enc_recv_size), 12,
				(ciphertext_recvbuf+(total_number_of_recv_msgs + idx) * (enc_recv_size) + 12), (unsigned long )(enc_recv_size -12),
				NULL, 0);
			if(!err_num){
				printf("Failed Decryption #%d in iteration %d by %d\nTried to decrypt at %d and put at (%d+%d)*%d=%d\n", idx, iteration, rank, (total_number_of_recv_msgs+idx)*enc_recv_size, total_number_of_recv_msgs, idx, (recvcount * recvtype_extent), (total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent));
				fflush(stdout);        
			}
		}//end for
		total_number_of_recv_msgs += number_of_received_msgs;

		/*
		* Waiting for the receives
		*/

		mpi_errno = MPIC_Wait((recv_req_ptr[iteration]), errflag);
		if (mpi_errno){
			MPIR_ERR_POPFATAL(mpi_errno);
		}
		
		*(&status) = (recv_req_ptr[iteration])->status;

		if (mpi_errno == MPI_SUCCESS) {
			mpi_errno = recv_req_ptr[iteration]->status.MPI_ERROR;
		}

		MPIR_Request_free(recv_req_ptr[iteration]);



		
		if (mpi_rcv_errno) {
			/* for communication errors, just record the error but continue */
			*errflag =
			MPIX_ERR_PROC_FAILED ==
			MPIR_ERR_GET_CLASS(mpi_rcv_errno) ? MPIR_ERR_PROC_FAILED : MPIR_ERR_OTHER;
			MPIR_ERR_SET(mpi_rcv_errno, *errflag, "**fail");
			MPIR_ERR_ADD(mpi_errno_ret, mpi_rcv_errno);
		}

		/*Do the last decryption*/

		number_of_received_msgs = rem;
		
		decrypted_msg_len = 0;
		for (int idx=0; idx<number_of_received_msgs; ++idx){
			err_num = EVP_AEAD_CTX_open(ctx, (tmp_buf+(total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent)),
				&decrypted_msg_len, (unsigned long )((recvcount * recvtype_extent)+16),
				(ciphertext_recvbuf+(total_number_of_recv_msgs+idx)*enc_recv_size), 12,
				(ciphertext_recvbuf+(total_number_of_recv_msgs + idx) * (enc_recv_size) + 12), (unsigned long )(enc_recv_size -12),
				NULL, 0);
			if(!err_num){
				printf("Failed Decryption #%d in iteration %d by %d\nTried to decrypt at %d and put at (%d+%d)*%d=%d\n", idx, iteration, rank, (total_number_of_recv_msgs+idx)*enc_recv_size, total_number_of_recv_msgs, idx, (recvcount * recvtype_extent), (total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent));
				fflush(stdout);        
			}else{
				printf("%d decrypted %d from %d and copied to %d\n", rank, decrypted_msg_len, (total_number_of_recv_msgs + idx) * (enc_recv_size), (total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent));
			}
		}//end for

		total_number_of_recv_msgs += number_of_received_msgs;
		++iteration;

	}//end if(rem)

	else{
		/*Do the last decryption*/

		number_of_received_msgs = (curr_cnt/2)/enc_recv_size;
		
		decrypted_msg_len = 0;
		for (int idx=0; idx<number_of_received_msgs; ++idx){
			err_num = EVP_AEAD_CTX_open(ctx, (tmp_buf+(total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent)),
				&decrypted_msg_len, (unsigned long )((recvcount * recvtype_extent)+16),
				(ciphertext_recvbuf+(total_number_of_recv_msgs+idx)*enc_recv_size), 12,
				(ciphertext_recvbuf+(total_number_of_recv_msgs + idx) * (enc_recv_size) + 12), (unsigned long )(enc_recv_size -12),
				NULL, 0);
			if(!err_num){
				printf("Failed Decryption #%d in iteration %d by %d \nTried to decrypt at %d and put at (%d+%d)*%d=%d\n", idx, iteration, rank, (total_number_of_recv_msgs+idx)*enc_recv_size, total_number_of_recv_msgs, idx, (recvcount * recvtype_extent), (total_number_of_recv_msgs+idx)*(recvcount * recvtype_extent));
				fflush(stdout);        
			}
		}//end for
		total_number_of_recv_msgs += number_of_received_msgs;
	}//end else
	//printf("Rank %d reached checkpoint 6\n", rank);


	/* Rotate blocks in tmp_buf down by (rank) blocks and store
	 * result in recvbuf. */

	mpi_errno = MPIR_Localcopy(tmp_buf, (comm_size - rank) * recvcount,
		recvtype, (char *) recvbuf + rank * recvcount * recvtype_extent,
		(comm_size - rank) * recvcount, recvtype);
	if (mpi_errno) {
		MPIR_ERR_POP(mpi_errno);
	}

	if (rank) {
		mpi_errno = MPIR_Localcopy((char *) tmp_buf +
			(comm_size - rank) * recvcount * recvtype_extent,
			rank * recvcount, recvtype, recvbuf, rank * recvcount, recvtype);
		if (mpi_errno) {
			MPIR_ERR_POP(mpi_errno);
		}
	}
	printf("Rank %d reached checkpoint 7 and iteration is %d\n", rank, iteration);

	//post wait for each of the sends

	for(p=0; p<iteration; ++p){
		mpi_errno = MPIC_Wait((send_req_ptr[p]), errflag);
		if (mpi_errno)
			MPIR_ERR_POP(mpi_errno);


		if (mpi_errno == MPI_SUCCESS) {
			mpi_errno = send_req_ptr[p]->status.MPI_ERROR;
		}

		MPIR_Request_free(send_req_ptr[p]);
	}
	printf("Rank %d reached checkpoint 8\n", rank);

	fn_exit:
	MPIR_CHKLMEM_FREEALL();
	if (mpi_errno_ret)
		mpi_errno = mpi_errno_ret;
	else if (*errflag != MPIR_ERR_NONE)
		MPIR_ERR_SET(mpi_errno, *errflag, "**coll_fail");

	return mpi_errno;

	fn_fail:
		goto fn_exit;

}
