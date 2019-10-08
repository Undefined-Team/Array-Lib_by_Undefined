#include <ud_array.h>

void        ud_arr_val(ud_arr *arr, size_t type_size, size_t len, void *val)
{
    arr->type_s = type_size;
    arr->len = len;
    arr->val = val;
}