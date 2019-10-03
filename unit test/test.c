#include <ud_array.h>

// void print_byte_as_bits(char val) {
//   for (int i = 7; 0 <= i; i--) {
//     printf("%c", (val & (1 << i)) ? '1' : '0');
//   }
// }

// void print_bits(char * ty, char * val, unsigned char * bytes, size_t num_bytes) {
//   printf("(%*s) %*s = [ ", 15, ty, 16, val);
//   for (size_t i = 0; i < num_bytes; i++) {
//     print_byte_as_bits(bytes[i]);
//     printf(" ");
//   }
//   printf("]\n");
// }

// #define SHOW(T,V) do { T x = V; print_bits(#T, #V, (unsigned char*) &x, sizeof(x)); } while(0)

int main(void)
{
    // ud_arr *test = ud_arr_init_z(sizeof(int), 5);
    // ud_arr *test = ud_arr_set();
    ud_arr *test = ud_arr_set(float, 5, 1.0, 1.1, 1.2, 1.3, 1.4);
    float *val = (float*)test->val;
    for (ud_ut_count i = 0; i < 5; ++i) printf("%f ", val[i]);
    printf("\n%zd %zd\n", test->len, test->type_s);
    // int *tab = pute(int, 3, 1, 2, 3);
    // printf("%d %d %d\n", tab[0], tab[1], tab[2]);
    // printf("%d\n", tamer(void){return 7});
    // SHOW(float , 5);
    // int nbr = ;

    // ud_arr_print(test, "%f");
    ud_arr *test2 = ud_arr_cpy(test);
    // ud_arr_print(test2, "%f");
    printf("%zd\n", sizeof(float));
    return (0);
}