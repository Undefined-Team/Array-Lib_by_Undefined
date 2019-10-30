#include "ud_array.h"

void        ud_arr_free_r(ud_arr *arr, int depth)
{
    if (!arr) return ; 
    ud_ut_count len = arr->len;
    if (arr->type == ud_arr_type_arr() && (depth > 0 || depth == -1))
    {
        ud_arr **val = (ud_arr**)arr->val;
        while (len-- > 0) ud_arr_free_r(*val++, depth == -1 ? -1 : depth - 1);
    }
    else if (arr->type->fp_free && (depth > 0 || depth == -1))
    {
        char *val = (char*)arr->val;
        size_t type_size = arr->type->size;
        void (*fp_free)(void *val, ...) = arr->type->fp_free;
        for (; len-- > 0; val += type_size) fp_free(*(void**)val);
    }
    ud_ut_free(arr->val);
    ud_ut_free(arr);
}