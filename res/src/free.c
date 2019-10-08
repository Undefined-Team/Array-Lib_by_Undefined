#include "ud_array.h"

void        ud_arr_free_r(ud_arr *arr, int depth)
{
    if (arr->type_s == 0 && (depth > 0 || depth == -1))
    {
        ud_arr **val = (ud_arr**)arr->val;
        ud_ut_count len = arr->len;
        while (len-- > 0) ud_arr_free_r(*val++, depth == -1 ? -1 : depth - 1);
    }
    ud_ut_free(arr->val);
    ud_ut_free(arr);
}