#include "ud_array.h"

static void     ud_arr_print_get_arr_size(ud_arr *arr, size_t format_len, size_t *index_cut, size_t *total_size, size_t space, size_t *index, size_t *save_len)
{
    ud_ut_count len = arr->len;
    if (arr->type_s != 0)
    {
        *total_size += space * UD_UT_SPACE_NBR + ud_str_len(ud_ut_color_t[space % UD_UT_COLOR_NBR]) + 2;
        while (len-- > 0)
        {
            *total_size += format_len + ((*save_len)-- > 1);
            index_cut[(*index)++] = *total_size;
        }
        *total_size += ud_str_len(UD_UT_COLOR_N) + 3;
    }
    else
    {
        *total_size += space * UD_UT_SPACE_NBR;
        *total_size += ud_str_len(ud_ut_color_t[space % UD_UT_COLOR_NBR]) + 3 + ud_math_int_len(space) + ud_str_len(UD_UT_COLOR_N);
        ud_arr **val = (ud_arr**)arr->val;
        while (len-- > 0) ud_arr_print_get_arr_size(*val++, format_len, index_cut, total_size, space + 1, index, save_len);
        *total_size += space * UD_UT_SPACE_NBR;
        *total_size += ud_str_len(ud_ut_color_t[space % UD_UT_COLOR_NBR]) + 2 + ud_str_len(UD_UT_COLOR_N);
    }
}

static char     *ud_arr_print_get_total_arr(ud_arr *arr, char *total_arr, char *format, size_t format_len, size_t space, size_t *save_len)
{
    ud_ut_count len = arr->len;
    if (arr->type_s != 0)
    {
        for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) ud_str_cpy_rd(&total_arr, " ");
        ud_str_cpy_rd(&total_arr, ud_ut_color_t[space % UD_UT_COLOR_NBR]);
        ud_str_cpy_rd(&total_arr, "[ ");
        while (len-- > 0)
        {
            ud_str_cpy_rd(&total_arr, format);
            if ((*save_len)-- > 1) *total_arr++ = '\0';
        }
        ud_str_cpy_rd(&total_arr, " ]");
        ud_str_cpy_rd(&total_arr, UD_UT_COLOR_N);
        ud_str_cpy_rd(&total_arr, "\n");
    }
    else
    {
        for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) ud_str_cpy_rd(&total_arr, " ");
        ud_str_cpy_rd(&total_arr, ud_ut_color_t[space % UD_UT_COLOR_NBR]);
        ud_str_cpy_rd(&total_arr, "[ ");
        char *space_itoa;
        UD_UT_PROT_MALLOC(space_itoa = ud_ut_malloc(sizeof(char) * (ud_math_int_len(space) + 1)));
        sprintf(space_itoa, "%zd", space);
        ud_str_cpy_rd(&total_arr, space_itoa);
        ud_ut_free(space_itoa);
        ud_str_cpy_rd(&total_arr, UD_UT_COLOR_N);
        ud_str_cpy_rd(&total_arr, "\n");
        ud_arr **val = (ud_arr**)arr->val;
        while (len-- > 0) total_arr = ud_arr_print_get_total_arr(*val++, total_arr, format, format_len, space + 1, save_len);
        for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) ud_str_cpy_rd(&total_arr, " ");
        ud_str_cpy_rd(&total_arr, ud_ut_color_t[space % UD_UT_COLOR_NBR]);
        ud_str_cpy_rd(&total_arr, "]");
        ud_str_cpy_rd(&total_arr, UD_UT_COLOR_N);
        ud_str_cpy_rd(&total_arr, "\n");
    }
    return total_arr;
}

char            **ud_arr_print_get_arr(ud_arr *arr, char *format)
{
    size_t save_len = ud_arr_item_nbr(arr, true, false);
    size_t count = save_len;
    size_t  index_cut[save_len];
    index_cut[0] = 0;
    char    **real_arr = NULL;
    char    *total_arr;
    size_t  total_size = 0;
    size_t  format_len = ud_str_len(format);
    size_t  index = 1;
    real_arr = ud_ut_malloc(sizeof(char**) * save_len);
    ud_arr_print_get_arr_size(arr, format_len, index_cut, &total_size, 0, &index, &count);
    UD_UT_PROT_MALLOC(total_arr = ud_ut_malloc(sizeof(char) * (total_size + 1)));
    total_arr[total_size] = '\0';
    count = save_len;
    (void)ud_arr_print_get_total_arr(arr, total_arr, format, format_len, 0, &count);
    if (save_len == 0)
    {
        printf("%s", total_arr);
        return NULL;
    }
    for (ud_ut_count i = 0; i < save_len; ++i)
        real_arr[i] = &total_arr[index_cut[i]];
    return real_arr;
}