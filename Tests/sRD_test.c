#include <stdio.h>

int main(){
    for(int rank=0; rank<4; ++rank){
        int mask, dst_tree_root, my_tree_root, dst,
        send_offset, recv_offset, i, comm_size=4, recvcount=4, sendcount=4, recvtype_extent=4, number_of_received_msgs=0, ciphertext_sendbuf_len=20;
        mask = 0x1;
        int enc_recv_size =(recvcount*recvtype_extent)+16+12;
        i = 0;

		int sendtype_sz = recvtype_extent, recvtype_sz=recvtype_extent;
		unsigned long t=0;
		t = (unsigned long)(sendtype_sz*sendcount);
		unsigned long   max_out_len = (unsigned long) (16 + (sendtype_sz*sendcount));
		
		int curr_cnt=recvcount;


		enc_recv_size = (recvcount*recvtype_sz)+16+12;
		
		curr_cnt = recvcount;

		mask = 0x1;
		i = 0;
		dst = rank ^ mask;

		
		dst_tree_root = dst >> i;
		dst_tree_root <<= i;

		my_tree_root = rank >> i;
		my_tree_root <<= i;

		send_offset = my_tree_root * enc_recv_size * recvtype_extent;
		recv_offset = dst_tree_root * enc_recv_size * recvtype_extent;

		

		printf("Rank %d recieves at %d for %d from %d\n", rank, recv_offset, enc_recv_size, dst);
		
		printf("Rank %d sends %d to %d\n", rank, ciphertext_sendbuf_len+12, dst);


		curr_cnt += ciphertext_sendbuf_len+12;



		mask <<= 1;
		i=1;

		while (mask < comm_size) {
			dst = rank ^ mask;

			dst_tree_root = dst >> i;
			dst_tree_root <<= i;

			my_tree_root = rank >> i;
			my_tree_root <<= i;

			send_offset = my_tree_root * enc_recv_size * recvtype_extent;
			recv_offset = dst_tree_root * enc_recv_size * recvtype_extent;

			if (dst < comm_size) {
				printf("Rank %d recieves at %d for %d*%d=%d from %d\n", rank, recv_offset, (comm_size - dst_tree_root),  enc_recv_size, (comm_size - dst_tree_root) *  enc_recv_size, dst);
				

				printf("Rank %d sends from %d for %d to %d\n", rank, send_offset, curr_cnt, dst);
				
				
				curr_cnt += (comm_size - dst_tree_root)*enc_recv_size;
			}


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

	        	printf("Rank %d decrypts at %d for %d and puts at %d\n", rank, dec_begin_offset+12, enc_recv_size -12, decrypted_msg_begin_offset+(idx*recvcount * recvtype_extent));
				
	        	
		      	printf("Successful Decryption #%d in iteration %d by %d\n", idx, i, rank);
		      	printf("decrypted_msg_begin_offset: %d, added by: %d, decrypted_msg_len: %d, dec_begin_offset: %d\n", decrypted_msg_begin_offset, (idx*recvcount * recvtype_extent), decrypted_msg_len, dec_begin_offset);

	        }//end for
		



		mask <<= 1;
        i++;




        /*
		* Waiting for the receives
		*/

		
		}//end while
	}//end for

	/*

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
 		unsigned long decrypted_msg_len = recvcount * recvtype_extent;
        for (int idx=0; idx<number_of_received_msgs; ++idx){
        	err_num = EVP_AEAD_CTX_open(ctx, (recvbuf+decrypted_msg_begin_offset+(idx*recvcount * recvtype_extent)),
	              &decrypted_msg_len, (unsigned long )((recvcount * recvtype_extent)+16),
	               (ciphertext_recvbuf+dec_begin_offset), 12,
	              (ciphertext_recvbuf+dec_begin_offset+12), (unsigned long )(enc_recv_size -12),
	              NULL, 0);
        	if(!err_num){
	        printf("Decryption error: allgather (sRD-2)\nError: %d\n", err_num);
	        fflush(stdout);        
	      }
        }

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
	goto fn_exit;*/
}
