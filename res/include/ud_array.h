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
# define UD_ARR_TYPE_INIT_FP_PRINT(format_str, ctype) \
    ({ \
        va_list ap; \
        va_start(ap, val); \
        void *fp_print = va_arg(ap,void*); \
        static char *format = format_str; \
        if (fp_print) format = fp_print; \
        else printf(format, *(ctype*)val); \
        va_end(ap); \
    })

# define ud_arr_type_get(ctype)                             ud_arr_type_get_ctr(#ctype, sizeof(ctype))
# define ud_arr_type_add(type, type_size)                   ud_arr_type_ctr(type, type_size, ud_arr_req_add)
# define ud_arr_type_search(type)                           ud_arr_type_ctr(type, 0, ud_arr_req_search)
# define ud_arr_type_set_fp_print(ctype, fpprint)           ({ ud_arr_type *tmp = ud_arr_type_get(ctype); tmp->fp_print = &fpprint; })
# define ud_arr_type_set_fp_free(ctype, fpfree)             ({ ud_arr_type *tmp = ud_arr_type_get(ctype); tmp->fp_free = &fpfree; })
# define ud_arr_type_set_fp_all(ctype, fpprint, fpfree)     ({ ud_arr_type *tmp = ud_arr_type_get(ctype); tmp->fp_print = &fpprint; tmp->fp_free = &fpfree; })
# define ud_arr_type_free()                                 (void)ud_arr_type_ctr(NULL, 0, ud_arr_req_free);

# define ud_arr_char_a                                      ud_arr
# define ud_arr_float_a                                     ud_arr
# define ud_arr_size_t_a                                    ud_arr
# define ud_arr_str_a                                       ud_arr

# define ud_arr_print(arr)                                  ud_arr_print_ctr(arr, 0);
# define ud_arr_free(arr)                                   ud_arr_free_r(arr, -1);
# define ud_arr_ofree(arr)                                  ud_arr_free_r(arr, 0);
# define ud_arr_reorder(_arr, ...)                          ({ size_t _indexs[] = {__VA_ARGS__}; printf("test = %zd\n", ud_ut_statica_len(_indexs)); if (_arr->len != ud_ut_statica_len(_indexs)) ud_ut_error("ud_arr_reoder function need as much indexs as array length"); ud_arr_reoder_ctr(_arr, _indexs); })

# define ud_arr_val(arr, ctype, len, val)                   ud_arr_tval(arr, ud_arr_type_get(ctype), len, val)
# define ud_arr_new(ctype, len, val)                        ud_arr_tnew(ud_arr_type_get(ctype), len, val)
# define ud_arr_init(ctype, len)                            ud_arr_tinit(ud_arr_type_get(ctype), len)
# define ud_arr_init_z(ctype, len)                          ud_arr_tinit_z(ud_arr_type_get(ctype), len)
# define ud_arr_init_val(ctype, len, set_val)               ud_arr_tinit_val(ud_arr_type_get(ctype), len, set_val)

# define ud_arr_rm_idx(arr, index)                          ud_arr_rm_idx_ctr(arr, index, false)
# define ud_arr_frm_idx(arr, index)                         ud_arr_rm_idx_ctr(arr, index, true)
# define ud_arr_rm_adr(arr, adr)                            ud_arr_rm_adr_ctr(arr, adr, false)
# define ud_arr_frm_adr(arr, adr)                           ud_arr_rm_adr_ctr(arr, adr, true)

# define ud_arr_set(ctype, ...) \
    ({ \
        ud_arr *new_arr; \
        ctype in_val[] = {__VA_ARGS__}; \
        ctype *in_tmp = in_val; \
        size_t len = sizeof(in_val) / sizeof(ctype); \
        new_arr = ud_arr_init(ctype, len); \
        ctype *val = (ctype*)new_arr->val; \
        for (ud_ut_count i = 0; i < len; ++i, ++val, ++in_tmp) *val = *in_tmp; \
        new_arr; \
    })
# define ud_arr_tset(ctype, type, ...) \
    ({ \
        ud_arr *new_arr; \
        ctype in_val[] = {__VA_ARGS__}; \
        ctype *in_tmp = in_val; \
        size_t len = sizeof(in_val) / sizeof(ctype); \
        new_arr = ud_arr_tinit(type, len); \
        ctype *val = (ctype*)new_arr->val; \
        for (ud_ut_count i = 0; i < len; ++i, ++val, ++in_tmp) *val = *in_tmp; \
        new_arr; \
    })

// Structures
typedef enum                    {ud_arr_req_add,ud_arr_req_search,ud_arr_req_free} ud_arr_type_req; 

typedef struct                  uds_arr_type {
    char                        *name;
    size_t                      size;
    void                        (*fp_print)(void *val, ...);
    void                        (*fp_free)(void *val, ...);
    struct uds_arr_type         *next;
}                               ud_arr_type;

typedef struct                  uds_arr {
    void                        *val;
    size_t                      len;
    ud_arr_type                 *type;
}                               ud_arr;

// Prototypes
void                            ud_arr_tval(ud_arr *arr, ud_arr_type *type, size_t len, void *val);
ud_arr                          *ud_arr_tnew(ud_arr_type *type, size_t len, void *val);
ud_arr                          *ud_arr_tinit(ud_arr_type *type, size_t len);
ud_arr                          *ud_arr_tinit_z(ud_arr_type *type, size_t len);
ud_arr                          *ud_arr_tinit_val(ud_arr_type *type, size_t len, void *set_val);
ud_arr                          *ud_arr_cpy(ud_arr *src);
void                            ud_arr_free_r(ud_arr *arr, int depth);
void                            ud_arr_print_ctr(ud_arr *arr, size_t space);
void                            ud_arr_rm_idx_ctr(ud_arr *arr, size_t index, ud_bool free_elem);
void                            ud_arr_rm_adr_ctr(ud_arr *arr, void *adr, ud_bool free_elem);
void                            ud_arr_reoder_ctr(ud_arr *arr, size_t *indexs);
ud_arr_size_t_a                 *ud_arr_shape(ud_arr *arr);

ud_arr_type                     *ud_arr_type_ctr(char *type_name, size_t type_size, ud_arr_type_req req);
ud_arr_type                     *ud_arr_type_get_ctr(char *type_name, size_t type_size);

ud_arr_type                     *ud_arr_type_char(void);
ud_arr_type                     *ud_arr_type_float(void);
ud_arr_type                     *ud_arr_type_size_t(void);
ud_arr_type                     *ud_arr_type_arr(void);

ud_arr_type                     *ud_arr_type_char_p(void);

#endif