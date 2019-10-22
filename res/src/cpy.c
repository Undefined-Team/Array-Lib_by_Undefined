#include "ud_array.h"

ud_arr      *ud_arr_cpy(ud_arr *src)
{
    ud_arr *dst;
    ud_bool ischar = src->type == ud_arr_type_char();

    UD_UT_PROT_MALLOC(dst = ud_arr_tinit(src->type, src->len + ischar));
    if (dst->type == ud_arr_type_arr())
    {
        ud_arr **dst_val = (ud_arr**)dst->val;
        ud_arr **src_val = (ud_arr**)src->val;
        ud_ut_count len = dst->len;
        while (len-- > 0) *dst_val++ = ud_arr_cpy(*src_val++);
    }
    else ud_mem_cpy(dst->val, src->val, (dst->len + ischar) * dst->type->size);
    return dst;
}