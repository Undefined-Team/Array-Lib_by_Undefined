#include "ud_array.h"

void ud_arr_type_pfprint_char(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%c", char);
}

void ud_arr_type_pfprint_unsigned_char(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%c", unsigned char);
}

void ud_arr_type_pfprint_short(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%hd, ", short);
}

void ud_arr_type_pfprint_unsigned_short(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%hu, ", unsigned short);
}

void ud_arr_type_pfprint_int(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%d, ", int);
}

void ud_arr_type_pfprint_unsigned_int(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%u, ", unsigned int);
}

void ud_arr_type_pfprint_long(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%ld, ", long);
}

void ud_arr_type_pfprint_unsigned_long(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%lu, ", unsigned long);
}

void ud_arr_type_pfprint_long_long(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%lld, ", long long);
}

void ud_arr_type_pfprint_unsigned_long_long(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%llu, ", unsigned long long);
}

void ud_arr_type_pfprint_float(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%f, ", float);
}

void ud_arr_type_pfprint_double(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%f, ", double);
}

void ud_arr_type_pfprint_long_double(void *val, ...)
{
    UD_ARR_TYPE_INIT_FP_PRINT("%Lf, ", long double);
}

void ud_arr_type_pffree_ud_arr(void *val, ...)
{
    ud_arr_free((ud_arr*)val);
}

static ud_arr_type *ud_arr_type_new(char *type_name, size_t type_size, void (*fp_print)(void *val, ...), void (*fp_free)(void *val, ...))
{
    ud_arr_type *new;
    UD_UT_PROT_MALLOC(new = ud_ut_malloc(sizeof(ud_arr_type)));
    new->name  = type_name;
    new->size  = type_size;
    new->fp_print = fp_print;
    new->fp_free = fp_free;
    new->next = NULL;
    return new;
}

static ud_arr_type *ud_arr_type_init(ud_arr_type *begin)
{
    size_t total = 13;
    char *base_type_name[] = {"char", "unsigned char", "short", "unsigned short", "int", "unsigned int", "long", "unsigned long", "long long", "unsigned long long", "float", "double", "long double"};
    size_t base_type_size[] = {sizeof(char), sizeof(unsigned char), sizeof(short), sizeof(unsigned short), sizeof(int), sizeof(unsigned int), sizeof(long), sizeof(unsigned long), sizeof(long long), sizeof(unsigned long long), sizeof(float), sizeof(double), sizeof(long double)};
    void (*base_type_fp_print[])(void *val, ...) = {&ud_arr_type_pfprint_char, &ud_arr_type_pfprint_unsigned_char, &ud_arr_type_pfprint_short, &ud_arr_type_pfprint_unsigned_short, &ud_arr_type_pfprint_int, &ud_arr_type_pfprint_unsigned_int, &ud_arr_type_pfprint_long, &ud_arr_type_pfprint_unsigned_long, &ud_arr_type_pfprint_long_long, &ud_arr_type_pfprint_unsigned_long_long, &ud_arr_type_pfprint_float, &ud_arr_type_pfprint_double, &ud_arr_type_pfprint_long_double};
    for (ud_ut_count i = 0; i < total; ++i)
    {
        begin->next = ud_arr_type_new(base_type_name[i], base_type_size[i], base_type_fp_print[i], NULL);
        begin = begin->next;
    }
    return begin;
}

static ud_arr_type  *ud_arr_type_free_ctr(ud_arr_type *begin)
{
    ud_arr_type *tmp;
    while (begin)
    {
        tmp = begin;
        begin = begin->next;
        ud_ut_free(tmp);
    }
    return NULL;
}

ud_arr_type         *ud_arr_type_ctr(char *type_name, size_t type_size, ud_arr_type_req req)
{
    static ud_arr_type *begin = NULL;
    static ud_arr_type *end = NULL;

    if (req == ud_arr_req_free) return ud_arr_type_free_ctr(begin); 
    if (!begin)
    {
        begin = ud_arr_type_new("ud_arr*", sizeof(ud_arr*), NULL, &ud_arr_type_pffree_ud_arr);
        end = ud_arr_type_init(begin);
    }
    if (req == ud_arr_req_search)
    {
        ud_arr_type *tmp = begin;
        for (; tmp; tmp = tmp->next)
            if (!ud_str_cmp(tmp->name, type_name)) return tmp;
        return NULL;
    }
    end->next = ud_arr_type_new(type_name, type_size, NULL, NULL);
    end = end->next;
    return end;
}

ud_arr_type         *ud_arr_type_get_ctr(char *type_name, size_t type_size)
{
    static ud_arr_type *old_type = NULL;

    if (!old_type) old_type = ud_arr_type_search("ud_arr*");
    if (ud_str_cmp(old_type->name, type_name) && !(old_type = ud_arr_type_search(type_name)))
        old_type = ud_arr_type_add(type_name, type_size);
    return old_type;
}