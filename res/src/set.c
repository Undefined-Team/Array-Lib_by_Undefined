#include "ud_array.h"

ud_arr      ud_arr_set(size_t type_size, size_t len, ...)
{
    ud_arr      *new_arr;
    va_list     va;
    char        *set_val;

    UD_UT_PROT_MALLOC(new_arr = ud_arr_init(type_size, len));
    if (!len) return new_arr;
    char *val = (char*)new_arr->val;
    va_start(va, len);    
    while (len-- > 0)
    {
        set_val = (char*)va_arg(va, int);
        for (ud_ut_count i = 0; i < type_size, ++i)
            *val++ = *set_val++;
    }
    va_end(va);
    return new_arr;
}