#include <ud_array.h>
/*
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
        for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) printf(" ");
        printf("%s[ %zd%s\n", ud_ut_color_t[space % UD_UT_COLOR_NBR], space, UD_UT_COLOR_N);
        ud_arr **val = (ud_arr**)arr->val;
        while (len-- > 0) ud_arr_print_ctr(*val++, format, space + 1);
        for (ud_ut_count i = 0; i < space; i++) printf(UD_UT_PRINT_SPACE);
        printf("%s]%s\n", ud_ut_color_t[space % UD_UT_COLOR_NBR], UD_UT_COLOR_N);
    }
}
*/
static void     ud_arr_print_get_arr_size(ud_arr *arr, size_t format_len, size_t *index_cut, size_t *total_size, size_t space, size_t *index)
{
    ud_ut_count len = arr->len;
    if (len != 0)
        if (arr->type_s != 0)
        {
            *total_size += space * UD_UT_SPACE_NBR + ud_ut_byte_len(ud_ut_color_t[space % UD_UT_COLOR_NBR]) + 2;
            while (len-- > 0)
            {
                index_cut[*index++] = *total_size;
                *total_size += format_len;
                *total_size += len > 0 ? 2 : 1;
            }
            *total_size += ud_ut_byte_len(UD_UT_COLOR_N) + 2;
        }
        else
        {
            *total_size += space * UD_UT_SPACE_NBR;
            *total_size += ud_ut_byte_len(ud_ut_color_t[space % UD_UT_COLOR_NBR]) + 3 + ud_ut_nbr_len(space) + ud_ut_byte_len(UD_UT_COLOR_N);
            while (len-- > 0) ud_arr_print_get_arr_size(arr, format_len, index_cut, total_size, space + 1, index);
            *total_size += space * UD_UT_SPACE_NBR;
            *total_size += ud_ut_byte_len(ud_ut_color_t[space % UD_UT_COLOR_NBR]) + 2 + ud_ut_byte_len(UD_UT_COLOR_N);
        }
}

static void     *ud_arr_print_str_add(char **dst, char *src)
{
    while (*src)
        *(*dst)++ = *src++
}

static char     *ud_arr_print_get_total_arr(char *total_arr, char *format, size_t format_len, size_t space)
{
    ud_ut_count len = arr->len;
    if (len != 0)
        if (arr->type_s != 0)
        {
            for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) ud_arr_print_str_add(&total_arr, " ");
            ud_arr_print_str_add(&total_arr, ud_ut_color_t[space % UD_UT_COLOR_NBR]);
            ud_arr_print_str_add(&total_arr, "[ ");
            while (len-- > 0)
            {
                ud_arr_print_str_add(&total_arr, format);
                if (len > 0) ud_arr_print_str_add(&total_arr, ",");
                ud_arr_print_str_add(&total_arr, " ");
            }
            ud_arr_print_str_add(&total_arr, "]");
            ud_arr_print_str_add(&total_arr, UD_UT_COLOR_N);
            ud_arr_print_str_add(&total_arr, "\n");
        }
        else
        {
            for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) ud_arr_print_str_add(&total_arr, " ");
            ud_arr_print_str_add(&total_arr, ud_ut_color_t[space % UD_UT_COLOR_NBR]);
            ud_arr_print_str_add(&total_arr, "[ ");
            char *space_itoa;
            UD_UT_PROT_MALLOC(space_itoa = ud_ut_malloc(sizeof(char) * ud_ut_int_len(space)));
            sprintf(space_itoa, "%zd", space);
            ud_arr_print_str_add(&total_arr, space_itoa);
            ud_ut_free(space_itoa);
            ud_arr_print_str_add(&total_arr, UD_UT_COLOR_N);
            ud_arr_print_str_add(&total_arr, "\n");
            while (len-- > 0) total_arr = ud_arr_print_get_total_arr(total_arr, format, format_len, space + 1);
            for (ud_ut_count i = 0; i < space * UD_UT_SPACE_NBR; i++) ud_arr_print_str_add(&total_arr, " ");
            ud_arr_print_str_add(&total_arr, ud_ut_color_t[space % UD_UT_COLOR_NBR]);
            ud_arr_print_str_add(&total_arr, "]");
            ud_arr_print_str_add(&total_arr, UD_UT_COLOR_N);
            ud_arr_print_str_add(&total_arr, "\n");
        }
    return total_arr;
}

size_t          ud_arr_print_get_save_len(ud_arr *arr, size_t *norm_type_size)
{
    ud_ut_count len = arr->len;
    if (len == 0)
        return 0;
    else if (arr->type_s != 0)
    {
        if (*norm_type_size == 0)
            *norm_type_size = arr->type_s;
        else if (*norm_type_size != arr->type_s)
            ud_ut_error("All sub array must have the same type or type_size")
        return arr->len;
    }
    ud_ut_count count = 0;
    while (len-- > 0) count += ud_arr_print_get_save_len(arr, norm_type_size);
    return count;
}

char            **ud_arr_print_get_arr(ud_arr *arr, char *format)
{
    size_t  norm_type_size = 0;
    size_t  save_len = ud_arr_print_get_save_len(arr, &norm_type_size);
    size_t  index_cut[save_len];
    char    **real_arr;
    char    *total_arr;
    size_t  total_size = 0;
    size_t  format_len = ud_ut_byte_len(format);
    size_t  index = 0;
    UD_UT_PROT_MALLOC(real_arr = ud_ut_malloc(sizeof(char**) * save_len));
    ud_arr_print_get_arr_size(arr, format_len, index_cut, &total_size, 0, &index);
    UD_UT_PROT_MALLOC(total_arr = ud_ut_malloc(sizeof(char) * total_size));
    (void)ud_arr_print_get_total_arr(total_arr, format, format_len, 0);
    for (ud_ut_count i = 0; i < save_len; ++i)
        real_arr[i] = &total_arr[index_cut[i]];
    return real_arr;
}