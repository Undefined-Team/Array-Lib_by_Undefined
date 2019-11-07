#include "ud_array.h"

static void ud_arr_shape_error(ud_arr *arr, size_t *shape, size_t len, ud_arr_type *atype)
{
    if (!arr) ud_ut_error("Array can't be null");
    else if (len == 0 && arr->type != atype) ud_ut_error("All not deepest layer must have array type");
    else if (arr->len != *shape) ud_ut_error("All elem of same layer must have same len");
    else if (len > 0)
    {
        if (arr->type != ud_arr_type_arr()) ud_ut_error("All deepest layer must have the same type");
        ++shape;
        --len;
        ud_arr **val = (ud_arr**)arr->val;
        size_t arr_len = arr->len;
        while (arr_len-- > 0)
            ud_arr_shape_error(*val++, shape, len, atype);
    }
}

ud_arr_size_t_a *ud_arr_shape(ud_arr *arr)
{
    size_t fdeep = 0;
    ud_arr *tmp = arr;
    while (tmp->type == ud_arr_type_arr())
    {
        tmp = *((ud_arr**)tmp->val);
        if (!tmp) ud_ut_error("Array element can't be null");
        ++fdeep;
    }
    ud_arr_size_t_a *shape = ud_arr_tinit(ud_arr_type_size_t(), fdeep);
    size_t *shape_val = (size_t*)shape->val;
    tmp = arr;
    while (tmp->type == ud_arr_type_arr())
    {
        *shape_val++ = tmp->len;
        tmp = *((ud_arr**)tmp->val);
    }
    ud_arr_shape_error(arr, (size_t*)shape->val, shape->len, tmp->type);
    return shape;
}