#include "ud_array.h"

static size_t   ud_arr_item_nbr_ctr(ud_arr *arr, size_t *norm_type_size, ud_bool error_if_multiple_type, ud_bool count_ud_arr)
{
    ud_ut_count len = arr->len;
    // if (len == 0)
        // return 0;
    if (arr->type_s != 0)
    {
        if (*norm_type_size == 0) *norm_type_size = arr->type_s;
        else if (error_if_multiple_type && *norm_type_size != arr->type_s) ud_ut_error("All sub array must have the same type or type_size");
        return arr->len;
    }
    ud_ut_count count = 0;
    ud_arr **val = (ud_arr**)arr->val;
    while (len-- > 0) count += ud_arr_item_nbr_ctr(*val++, norm_type_size, error_if_multiple_type, count_ud_arr);
    return count + (count_ud_arr ? arr->len : 0);
}

size_t          ud_arr_item_nbr(ud_arr *arr, ud_bool error_if_multiple_type, ud_bool count_ud_arr)
{
    size_t  norm_type_size = 0;
    return ud_arr_item_nbr_ctr(arr, &norm_type_size, error_if_multiple_type, count_ud_arr);
}