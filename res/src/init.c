#include "ud_array.h"

ud_arr      *ud_arr_tinit(ud_arr_type *type, size_t len)
{
    ud_arr *new_arr;

    UD_UT_PROT_MALLOC(new_arr = ud_ut_malloc(sizeof(ud_arr)));
    void *val = ud_ut_malloc(type->size * len);
    ud_arr_tval(new_arr, type, len, val);
    return new_arr;
}

ud_arr      *ud_arr_tinit_z(ud_arr_type *type, size_t len)
{
    ud_arr *new_arr;

    UD_UT_PROT_MALLOC(new_arr = ud_arr_tinit(type, len));
    char *val = (char*)new_arr->val;
    ud_mem_set(val, 0, len * type->size);
    return new_arr;
}

ud_arr      *ud_arr_tinit_val(ud_arr_type *type, size_t len, void *set_val)
{
    ud_arr *new_arr;
    char   *set_val_tmp;
    size_t type_size = type->size;

    UD_UT_PROT_MALLOC(new_arr = ud_arr_tinit(type, len));
    char *val = (char*)new_arr->val;
    while (len-- > 0)
    {
        set_val_tmp = (char*)set_val;
        for (ud_ut_count i = 0; i < type_size; ++i)
            *val++ = *set_val_tmp++;
    }
    return new_arr;
}