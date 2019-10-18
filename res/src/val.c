#include "ud_array.h"

void        ud_arr_tval(ud_arr *arr, ud_arr_type *type, size_t len, void *val)
{
    arr->type = type;
    arr->len = len;
    arr->val = val;
}