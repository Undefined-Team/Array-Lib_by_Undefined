#include "ud_array.h"

static void *ud_arr_flatten_fill(ud_arr *arr, void *val)
{
    ud_ut_count len = arr->len;
    if (len == 0)
        return val;
    else if (arr->type_s != 0)
    {
        ud_mem_cpy(val, arr->val, arr->len * arr->type_s);
        return val + arr->len * arr->type_s;
    }
    ud_arr **arr_val = (ud_arr**)arr->val;
    while (len-- > 0) val = ud_arr_flatten_fill(*arr_val++, val);
    return val;
}

static size_t ud_arr_flatten_get_first_type_size(ud_arr *arr)
{
    if (arr->type_s != 0) return arr->type_s;
    else if (arr->len == 0) return 0;
    return ud_arr_flatten_get_first_type_size(*(ud_arr**)arr->val);
}

ud_arr      *ud_arr_flatten(ud_arr *src)
{
    ud_arr *new_arr = ud_arr_init(  ud_arr_flatten_get_first_type_size(src),
                                    ud_arr_item_nbr(src, true, false));
    ud_arr_flatten_fill(src, new_arr->val);
    return new_arr;
}
