#include "ud_array.h"

ud_arr      *ud_arr_tnew(ud_arr_type *type, size_t len, void *val)
{
    ud_arr *new_arr;

    UD_UT_PROT_MALLOC(new_arr = ud_ut_malloc(sizeof(ud_arr)));
    ud_arr_tval(new_arr, type, len, val);
    return new_arr;
}