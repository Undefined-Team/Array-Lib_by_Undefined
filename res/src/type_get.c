#include "ud_array.h"

ud_arr_type    *ud_arr_type_arr(void)
{
    static ud_arr_type *type_arr = NULL;
    if (!type_arr) type_arr = ud_arr_type_get(ud_arr*);
    return type_arr;
}