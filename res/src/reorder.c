#include "ud_array.h"

static void ud_arr_reorder_error(size_t *indexs, size_t len)
{
    ud_bool verif_indexs[len];
    ud_mem_set(verif_indexs, false, sizeof(ud_bool) * len);
    while (len-- > 0) if (verif_indexs[*indexs++]++ != false) ud_ut_error("Indexs must be used only one time");
}

void        ud_arr_reoder_ctr(ud_arr *arr, size_t *indexs)
{
    if (!arr) ud_ut_error("Array can't be null");    
    size_t len = arr->len;
    ud_arr_reorder_error(indexs, len);
    size_t type_size = arr->type->size;
    char new_val[len * type_size];
    char *val = (char*)arr->val;
    for (ud_ut_count i = len; i-- > 0;)
        ud_mem_cpy_rs(new_val + *indexs++ * type_size, val, type_size);
    val = arr->val;
    ud_mem_cpy(val, new_val, type_size * len);
}