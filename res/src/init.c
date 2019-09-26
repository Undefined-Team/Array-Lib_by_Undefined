#include "ud_array.h"

ud_arr      *ud_arr_init(size_t type_size, size_t len)
{
    ud_arr *new_arr;

    UD_UT_PROT_MALLOC(new_arr = ud_ut_malloc(sizeof(ud_arr)));
    void *val = ud_ut_malloc((type_size == 0 ? sizeof(ud_arr) : type_size) * len);
    ud_arr_val(new_arr, type_size, len, val);
    return new_arr;
}

ud_arr      *ud_arr_init_z(size_t type_size, size_t len)
{
    ud_arr *new_arr;

    UD_UT_PROT_MALLOC(new_arr = ud_arr_init(type_size, len));
    char *val = (char*)new_arr->val;
    while (len-- > 0) *val++ = 0;
    return new_arr;
}

ud_arr      *ud_arr_init_val(size_t type_size, size_t len, char *set_val)
{
    ud_arr *new_arr;
    char   *set_val_tmp;

    UD_UT_PROT_MALLOC(new_arr = ud_arr_init(type_size, len));
    char *val = (char*)new_arr->val;
    while (len-- > 0)
    {
        set_val_tmp = set_val;
        for (ud_ut_count i = 0; i < type_size, ++i)
            *val++ = *set_val_tmp++;
    }
    return new_arr;
}