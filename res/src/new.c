#include <ud_array.h>

ud_arr      *ud_arr_new(size_t type_size, size_t len, void *val)
{
    ud_arr *new_arr;

    UD_UT_PROT_MALLOC(new_arr = ud_ut_malloc(sizeof(ud_arr)));
    ud_arr_val(new_arr, type_size, len, val);
    return new_arr;
}