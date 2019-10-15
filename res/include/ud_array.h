#ifndef UD_ARRAY_H
# define UD_ARRAY_H

// Lib
#include <stdlib.h>
#include <stdarg.h>
#include <ud_utils.h>
#include <ud_memory.h>
#include <ud_math.h>
#include <ud_string.h>

// Macro
# define ud_arr_char_a          ud_arr
# define ud_arr_float_a         ud_arr
# define ud_arr_size_t_a        ud_arr
# define ud_arr_str_a           ud_arr

# define ud_arr_free(w)         ud_arr_free_r(w, -1)
# define ud_arr_ofree(w)        ud_arr_free_r(w, 0)

# define ud_arr_set(type, ...) ({ ud_arr *new_arr; type in_val[] = {__VA_ARGS__}; size_t len = sizeof(in_val) / sizeof(type); new_arr = ud_arr_init(!ud_str_cmp(#type, "ud_arr*") ? 0 : sizeof(type), len); type *val = (type*)new_arr->val; for (ud_ut_count i = 0; i < len; ++i) val[i] = in_val[i]; new_arr; })
/*
# define ud_arr_set(type, ...) \
    ({ \
        ud_arr *new_arr; \
        type in_val[] = {__VA_ARGS__}; \
        type *in_tmp = in_val; \
        size_t len = sizeof(in_val) / sizeof(type); \
        new_arr = ud_arr_init(!ud_str_cmp(#type, "ud_arr*") ? 0 : sizeof(type), len); \
        type *val = (type*)new_arr->val; \
        for (ud_ut_count i = 0; i < len; ++i, ++val, ++in_tmp) *val = *in_tmp; \
        new_arr; \
    })

    // <<< If need to modify ud_arr_set >>>
*/ 

# define ud_arr_print(arr, type, format) ({ char **ud_arr_print_arr = ud_arr_print_get_arr(arr, format); char *start_total = NULL; if (ud_arr_print_arr) start_total = *ud_arr_print_arr; char **ud_arr_print_tmp = ud_arr_print_arr; ud_arr *flattened = ud_arr_flatten(arr); type *val = (type*)flattened->val; for (ud_ut_count i = 0; i < flattened->len; ++i) printf(*ud_arr_print_tmp++, *val++); ud_arr_free(flattened); ud_ut_free(ud_arr_print_arr); ud_ut_free(start_total); })
/*
# define ud_arr_print(arr, type, format) \
    ({ \
        char **ud_arr_print_arr = ud_arr_print_get_arr(arr, format); \
        char *start_total = NULL; \
        if (ud_arr_print_arr) start_total = *ud_arr_print_arr; \
        char **ud_arr_print_tmp = ud_arr_print_arr;
        ud_arr *flattened = ud_arr_flatten(arr); \
        type *val = (type*)flattened->val; \
        for (ud_ut_count i = 0; i < flattened->len; ++i) printf(*ud_arr_print_tmp++, *val++); \
        ud_arr_free(flattened); \
        ud_ut_free(ud_arr_print_arr); \
        ud_ut_free(start_total); \
    })

    // <<< If need to modify ud_arr_print >>>
*/

// Structures
typedef struct                  uds_arr {
    void                        *val;
    size_t                      len;
    size_t                      type_s;
}                               ud_arr;

// Prototypes
void                            ud_arr_val(ud_arr *arr, size_t type_size, size_t len, void *val);
ud_arr                          *ud_arr_new(size_t type_size, size_t len, void *val);
ud_arr                          *ud_arr_init(size_t type_size, size_t len);
ud_arr                          *ud_arr_init_z(size_t type_size, size_t len);
ud_arr                          *ud_arr_init_val(size_t type_size, size_t len, void *set_val);
ud_arr                          *ud_arr_cpy(ud_arr *src);
size_t                          ud_arr_item_nbr(ud_arr *arr, ud_bool error_if_multiple_type, ud_bool count_ud_arr);
ud_arr                          *ud_arr_flatten(ud_arr *src);
void                            ud_arr_free_r(ud_arr *arr, int depth);
char                            **ud_arr_print_get_arr(ud_arr *arr, char *format);
void                            ud_arr_rm_idx(ud_arr *arr, size_t index, ud_bool free_elem);
void                            ud_arr_rm_adr(ud_arr *arr, void *adr, ud_bool free_elem);

#endif
