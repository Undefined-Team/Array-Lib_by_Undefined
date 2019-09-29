#include <ud_array.h>

int main(void)
{
    // ud_arr *test = ud_arr_init_z(sizeof(int), 5);
    ud_arr *test = ud_arr_set(sizeof(float), 5, 1.0, 1.1, 1.2, 1.3, 1.4);
    ud_arr_print(test, "%f");
    ud_arr *test2 = ud_arr_cpy(test);
    ud_arr_print(test2, "%f");
    return (0);
}