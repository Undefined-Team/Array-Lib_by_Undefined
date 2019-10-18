#include "ud_array.h"

ud_arr_type    *ud_arr_type_arr(void)
{
    static ud_arr_type *arr_type = NULL;
    if (!arr_type) arr_type = ud_arr_type_get(ud_arr*);
    return arr_type;
}