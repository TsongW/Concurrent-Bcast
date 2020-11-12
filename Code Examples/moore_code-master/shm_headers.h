typedef int comm_val_t; //These types should match SCOTCH_Num
typedef int comm_cnt_t;

//Data structure representing a sparse matrix
typedef struct sp_matrix{
    //We save both row-major and column-major values
    //only to speedup further steps of our algorithm
    comm_val_t *row_vals, *col_vals;
    int *cols, *rows;
    int *row_idx, *col_idx;
    int num_nzero;
    int size;
}sp_matrix;

comm_val_t** load_comm_patt_shm(char *comm_patt_file_name, int size);
comm_val_t** patt_to_sym(int size, comm_val_t **in_patt_matrix, int printMsg);
comm_val_t find_mat_min(comm_val_t **mat, int size);
comm_val_t find_mat_max(comm_val_t **mat, int size);
sp_matrix patt_to_sp(int size, float sp_percentage, comm_val_t **in_patt_matrix);
comm_val_t** matrix_sum(comm_val_t **mat1, comm_val_t **mat2, int size);
int free_matrix(comm_val_t **mat, int size);
int free_sp_matrix(sp_matrix *sp_mat);
int normalize_mat(comm_val_t **mat, int size, comm_val_t min, comm_val_t max, int norm_max);
int has_neg_val(comm_val_t **mat, int size);
int print_sp_mat(sp_matrix *in_mat_ptr);
