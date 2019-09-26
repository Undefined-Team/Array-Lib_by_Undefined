#include "ud_array.h"

ud_arr      *ud_arr_cpy(ud_arr *src)
{
    ud_arr *dst;

    UD_UT_PROT_MALLOC(dst = ud_arr_init(src->type_s, src->len));
    if (dst->type_s == 0)
    {
        ud_arr **dst_val = (ud_arr**)dst->val;
        ud_arr **src_val = (ud_arr**)src->val;
        ud_ut_count len = dst->len;
        while (len-- > 0) *dst_val++ = ud_arr_cpy(*src_val++);
    }
    else ud_mem_cpy(dst->val, src->val, dst->len * dst->type_s);
    return dst;
}