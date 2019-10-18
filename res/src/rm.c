#include "ud_array.h"

void    ud_arr_rm_idx(ud_arr *arr, size_t index, ud_bool free_elem)
{
    if (index >= arr->len) return ;
    size_t type_size = arr->type->size;
    char* new_arr_val = ud_ut_malloc(type_size * (arr->len - 1));
    char* new_arr_val_tmp = new_arr_val;
    char* arr_val = (char*)arr->val;
    ud_mem_cpy_rds(new_arr_val_tmp, arr_val, type_size * index);
    if (free_elem && arr->type->fp_free) 
        arr->type->fp_free(*(void**)arr_val);
    arr_val += type_size;
    --arr->len;
    ud_mem_cpy_rds(new_arr_val_tmp, arr_val, type_size * (arr->len - index));
    ud_ut_free(arr->val);
    arr->val = new_arr_val;
}

void    ud_arr_rm_adr(ud_arr *arr, void *adr, ud_bool free_elem)
{
    if (arr->len == 0) return ;
    ud_arr_rm_idx(arr, (adr - arr->val) / arr->type->size, free_elem);
}