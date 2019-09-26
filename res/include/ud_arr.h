#ifndef UD_ARRAY_H
# define UD_ARRAY_H

// Lib
#include <stdlib.h>
#include "ud_utils.h"

// Macro
# define ud_arr_free(w)         ud_arr_free_r(w, 0)
# define ud_arr_shape(w, ...)   ud_arr_set(sizeof(size_t), w, __VA_ARGS__)
# define ud_arr_print(w, x)     ud_arr_print_ctr(w, x, 0)

# define ud_arr_char_a          ud_arr
# define ud_arr_float_a         ud_arr
# define ud_arr_size_t_a        ud_arr
# define ud_arr_str_a           ud_arr
# define ud_arr_stdiz_a         ud_arr

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
ud_arr                          ud_arr_set(size_t type_size, size_t len, ...);
void                            ud_arr_print_ctr(ud_arr *arr, char *format, size_t space);

#endif