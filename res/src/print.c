#include <ud_array.h>

void        ud_arr_print_ctr(ud_arr *arr, char *format, size_t space)
{
    ud_ut_count len = arr->len;
    if (len == 0)
        return ;
    else if (arr->type_s != 0)
    {
        for (ud_ut_count i = 0; i < space; i++) printf(UD_UT_PRINT_SPACE);
        printf("%s[ ", ud_ut_color_t[space % UD_UT_COLOR_NBR]);
        ud_ut_count type_size   = arr->type_s;
        char        *val        = (char*)arr->val;
        while (len-- > 0)
        {
            printf(format, *val);
            val += type_size;
            printf("%s ", len > 0 ? "," : "");
        }
        printf("]%s\n", UD_UT_COLOR_N);
    }
    else
    {
        for (ud_ut_count i = 0; i < space; i++) printf(UD_UT_PRINT_SPACE);
        printf("%s[ %zd%s\n", ud_ut_color_t[space % UD_UT_COLOR_NBR], space, UD_UT_COLOR_N);
        ud_arr **val = (ud_arr**)arr->val;
        while (len-- > 0) ud_arr_print_ctr(*val++, format, space + 1);
        for (ud_ut_count i = 0; i < space; i++) printf(UD_UT_PRINT_SPACE);
        printf("%s]%s\n", ud_ut_color_t[space % UD_UT_COLOR_NBR], UD_UT_COLOR_N);
    }
}