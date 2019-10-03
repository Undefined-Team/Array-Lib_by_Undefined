#ifndef UD_ARRAY_H
# define UD_ARRAY_H

// Lib
#include <stdlib.h>
#include <stdarg.h>
#include <ud_utils.h>
#include <ud_memory.h>

// Macro
# define ud_arr_free(w)         ud_arr_free_r(w, 0)
// # define ud_arr_print(w, x)     ud_arr_print_ctr(w, x, 0)

# define ud_arr_char_a          ud_arr
# define ud_arr_float_a         ud_arr
# define ud_arr_size_t_a        ud_arr
# define ud_arr_str_a           ud_arr
# define ud_arr_stdiz_a         ud_arr

/*
# define ud_arr_set(type, len, ...) \
    ({ \
        ud_arr *new_arr; \
        new_arr = ud_arr_init(sizeof(type), len); \
        type *val = (type*)new_arr->val; \
        type in_val[len] = {__VA_ARGS__}; \
        for (ud_ut_count i = 0; i < len; ++i) val[i] = in_val[i]; \
        new_arr; \
    })

    If need to modify ud_arr_set
*/ 
# define ud_arr_set(type, len, ...) ({ ud_arr *new_arr; new_arr = ud_arr_init(sizeof(type), len); type *val = (type*)new_arr->val; type in_val[len] = {__VA_ARGS__}; for (ud_ut_count i = 0; i < len; ++i) val[i] = in_val[i]; new_arr; })

# define ud_arr_print(arr, type, format) \
    ({ \
        char **ud_arr_print_arr = ud_arr_print_get_arr(arr, format); \
        char *start_total = *ud_arr_print_arr; \
        type *val = (type*)arr->val; \
        for (ud_ut_count i = 0; i < arr->len; ++i) printf(ud_arr_print_arr[i], *val++); \
        ud_ut_free(ud_arr_print_arr); \
        ud_ut_free(start_total); \
    })

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
ud_arr                          *ud_arr_init_val(size_t type_size, size_t len, char *set_val);
ud_arr                          *ud_arr_cpy(ud_arr *src);
void                            ud_arr_free_r(ud_arr *arr, int depth);
// void                            ud_arr_print_ctr(ud_arr *arr, char *format, size_t space);
char                            **ud_arr_print_get_arr(ud_arr *arr, char *format);

#endif
