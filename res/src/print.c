#include "ud_array.h"

void        ud_arr_print_ctr(ud_arr *arr, size_t space)
{
    if (!arr) return ;
    ud_ut_count len = arr->len;
    if (arr->type != ud_arr_type_arr())
    {
        for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) printf(" ");
        printf("%s[ ", ud_ut_color_t[space % UD_UT_COLOR_NBR]);
        ud_ut_count type_size            = arr->type->size;
        char        *val                 = (char*)arr->val;
        void (*fp_print)(void *val, ...) = arr->type->fp_print;
        char        *name                = arr->type->name;
        if (fp_print)
            while (len-- > 0)
            {
                fp_print(val, NULL);
                val += type_size;
            }
        else while (len-- > 0) printf("(%s), ", name);
        printf(" ]%s\n", UD_UT_COLOR_N);
    }
    else
    {
        for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) printf(" ");
        printf("%s[ %zd%s\n", ud_ut_color_t[space % UD_UT_COLOR_NBR], space, UD_UT_COLOR_N);
        ud_arr **val = (ud_arr**)arr->val;
        while (len-- > 0) ud_arr_print_ctr(*val++, space + 1);
        for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) printf(" ");
        printf("%s]%s\n", ud_ut_color_t[space % UD_UT_COLOR_NBR], UD_UT_COLOR_N);
    }
}