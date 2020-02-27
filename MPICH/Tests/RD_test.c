#include <stdio.h>

int main(){
    for(int rank=0; rank<4; ++rank){
        int mask, dst_tree_root, my_tree_root, dst,
        send_offset, recv_offset, i, comm_size=4, recvcount=4, recvtype_extent=100, number_of_received_msgs=0;
        mask = 0x1;
        int enc_recv_size =(recvcount*recvtype_extent)+16+12;
        i = 0;
        printf("\n**************** Rank %d *****************\n", rank);
        while (mask < comm_size) {
            dst = rank ^ mask;

            /* find offset into send and recv buffers. zero out
             * the least significant "i" bits of rank and dst to
             * find root of src and dst subtrees. Use ranks of
             * roots as index to send from and recv into buffer */

            dst_tree_root = dst >> i;
            //printf("dst_tree_root=%d\n", dst_tree_root);
            dst_tree_root <<= i;
            //printf("dst_tree_root=%d\n", dst_tree_root);

            my_tree_root = rank >> i;
            //printf("my_tree_root=%d\n", my_tree_root);
            my_tree_root <<= i;
            //printf("my_tree_root=%d\n", my_tree_root);

            /* FIXME: saving an MPI_Aint into an int */
            send_offset = my_tree_root * recvcount * recvtype_extent;
            recv_offset = dst_tree_root * recvcount * recvtype_extent;
            if(i>0){
                number_of_received_msgs = 1 << (i-1);
            } 

            //printf("in step %d, mask=%d, dst=%d, dst_tree_root=%d, my_tree_root=%d, send_offset=%d, recv_offset=%d, number_of_received_msgs=%d\n", i, mask, dst, dst_tree_root, my_tree_root, send_offset, recv_offset, number_of_received_msgs);
            



            //first, we need to compute the previous send and recv offsets:
            if(i>0){
                int prev_dst, prev_mask, prev_dst_tree_root, prev_my_tree_root, prev_send_offset, prev_recv_offset, prev_i;
                prev_i      =   i-1;
                prev_mask   =   mask >> 1;

                prev_dst = rank ^ prev_mask;
                printf("prev_dst = %d\n", prev_dst);
                prev_dst_tree_root = prev_dst >> prev_i;
                prev_dst_tree_root <<= prev_i;

                prev_my_tree_root = rank >> prev_i;
                prev_my_tree_root <<= prev_i;

                prev_send_offset = prev_my_tree_root * enc_recv_size ;
                prev_recv_offset = prev_dst_tree_root * enc_recv_size;

                printf("prev_send_offset = %d, prev_recv_offset = %d\n", prev_send_offset, prev_recv_offset);
                //Now, we compute the offsets of the previously received messages in the buffer

                int dec_begin_offset, dec_end_offset; //these offsets indicate which part of the receive buffer should be decrypted
                number_of_received_msgs = 1<< prev_i;
                int err_num;
                dec_begin_offset = prev_recv_offset;
                if(prev_send_offset<prev_recv_offset){
                    dec_end_offset = prev_recv_offset + number_of_received_msgs * (enc_recv_size);
                }else{
                    dec_end_offset = prev_send_offset;
                }
                //printf("Decryption should be from %d to %d\n", dec_begin_offset, dec_end_offset);
                int decrypted_msg_begin_offset = prev_dst_tree_root * recvcount * recvtype_extent;
                int decrypted_msg_len = recvcount * recvtype_extent;
                for (int idx=0; idx<number_of_received_msgs; ++idx){
                    
                    
                    printf("Rank %d Decrypts from %d for %d and copies to %d for %d\n", rank, dec_begin_offset+12, (enc_recv_size-12), decrypted_msg_begin_offset+(idx*recvcount * recvtype_extent), decrypted_msg_len);
                }


            }//end if i>0

            mask <<= 1;
            i++;
        }//end while


        int prev_dst, prev_mask, prev_dst_tree_root, prev_my_tree_root, prev_send_offset, prev_recv_offset, prev_i;
        prev_i      =   i-1;
        prev_mask   =   mask >> 1;

        prev_dst = rank ^ prev_mask;
        printf("prev_dst = %d\n", prev_dst);
        prev_dst_tree_root = prev_dst >> prev_i;
        prev_dst_tree_root <<= prev_i;

        prev_my_tree_root = rank >> prev_i;
        prev_my_tree_root <<= prev_i;

        prev_send_offset = prev_my_tree_root * enc_recv_size;
        prev_recv_offset = prev_dst_tree_root * enc_recv_size;

        //printf("prev_send_offset = %d, prev_recv_offset = %d\n", prev_send_offset, prev_recv_offset);
        //Now, we compute the offsets of the previously received messages in the buffer

        int dec_begin_offset, dec_end_offset; //these offsets indicate which part of the receive buffer should be decrypted
        number_of_received_msgs = 1<< prev_i;
        int  err_num;
        dec_begin_offset = prev_recv_offset;
        if(prev_send_offset<prev_recv_offset){
            dec_end_offset = prev_recv_offset + number_of_received_msgs * (enc_recv_size);
        }else{
            dec_end_offset = prev_send_offset;
        }
        //printf("Decryption should be from %d to %d\n", dec_begin_offset, dec_end_offset);ss
        int decrypted_msg_begin_offset = prev_dst_tree_root * recvcount * recvtype_extent;
        int decrypted_msg_len = recvcount * recvtype_extent;
        for (int idx=0; idx<number_of_received_msgs; ++idx){
            
            
            printf("Rank %d Decrypts from %d for %d and copies to %d for %d\n", rank, dec_begin_offset+12, (enc_recv_size -12), decrypted_msg_begin_offset +(idx*recvcount * recvtype_extent), decrypted_msg_len);
        }


    }//end for
	
}