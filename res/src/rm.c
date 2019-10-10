#include "ud_array.h"

static void ud_arr_rm_found(ud_arr *arr, size_t type_size, char **arr_val, ud_bool free_elem)
{
    if (free_elem) 
    {
        if (arr->type_s == 0) ud_arr_free(*(ud_arr**)*arr_val);
        else ud_ut_free(**arr_val);
    }
    *arr_val += type_size;
    --arr->len;
}

void    ud_arr_rm_idx(ud_arr *arr, size_t index, ud_bool free_elem)
{
    if (index >= arr->len) return ;
    size_t len = arr->len;
    size_t type_size = arr->type_s == 0 ? sizeof(ud_arr*) : arr->type_s;
    char* new_arr_val = ud_ut_malloc(type_size * (len - 1));
    char* new_arr_val_tmp = new_arr_val;
    char* arr_val = (char*)arr->val;
    for (ud_ut_count i = 0; i < len; ++i)
    {
        if (i != index)
            ud_mem_cpy_rds((void**)&new_arr_val_tmp, (void**)&arr_val, type_size);
        else
            ud_arr_rm_found(arr, type_size, &arr_val, free_elem);
    }
    ud_ut_free(arr->val);
    arr->val = new_arr_val;
}

void    ud_arr_rm_adr(ud_arr *arr, void *adr, ud_bool free_elem)
{
    if (arr->len == 0) return ;
    size_t len = arr->len - 1;
    size_t type_size = arr->type_s == 0 ? sizeof(ud_arr*) : arr->type_s;
    char* new_arr_val = ud_ut_malloc(type_size * len);
    char* new_arr_val_tmp = new_arr_val;
    char* arr_val = (char*)arr->val;
    for (ud_ut_count i = 0; i < len; ++i)
    {
        if (adr != arr_val)
            ud_mem_cpy_rds((void**)&new_arr_val_tmp, (void**)&arr_val, type_size);
        else
            ud_arr_rm_found(arr, type_size, &arr_val, free_elem);
    }
    if (len != arr->len)
    {
        if (adr == arr_val) ud_arr_rm_found(arr, type_size, &arr_val, free_elem);
        else
        {
            ud_ut_free(new_arr_val);
            return ;
        }
    }
    else ud_mem_cpy_rds((void**)&new_arr_val_tmp, (void**)&arr_val, type_size);
    ud_ut_free(arr->val);
    arr->val = new_arr_val;
}