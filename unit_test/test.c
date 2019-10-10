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

    // ud_arr *test = ud_arr_set(float, 5, 1.0, 1.1, 1.2, 1.3, 1.4);
    // float *val = (float*)test->val;
    // for (ud_ut_count i = 0; i < 5; ++i) printf("%f ", val[i]);
    // printf("\n%zd %zd\n", test->len, test->type_s);

    // ud_arr *test = ud_arr_init(0, 2);
    // ud_arr **val = (ud_arr**)test->val;
    // val[0] = ud_arr_set(float, 5, 1.0, 1.1, 1.2, 1.3, 1.4);
    // val[1] = ud_arr_set(float, 6, 1.6, 1.7, 1.8, 1.9, 1.10, 1);
    // // val[0] = ud_arr_init_z(sizeof(int), 5);
    // // val[1] = ud_arr_init_z(sizeof(int), 5);

    // // float *pval = (float*)val[0]->val;
    // // for (ud_ut_count i = 0; i < 5; ++i) printf("%f ", pval[i]);
    // // printf("\n%zd %zd\n", val[0]->len, val[0]->type_s);

    // ud_arr *test2 = ud_arr_init(0, 3);
    // val = (ud_arr**)test2->val;
    // val[0] = ud_arr_cpy(test);
    // val[1] = ud_arr_cpy(test);
    // // val[2] = ud_arr_set(float, 6, 1.6, 1.7, 1.8, 1.9, 1.10, 1);
    // // float thefloat = 5;
    // val[2] = ud_arr_init_val(sizeof(float), 2, ({float thefloat = 5; &thefloat; }));
    // ud_arr_print(test2, float, "%f");

    // ud_arr_rfree(test);
    // ud_arr_rfree(test2);

    // ud_arr *test3 = ud_arr_init(sizeof(float), 0);
    // printf("test %zd\n", test3->len);
    // ud_arr_print(test3, float, "%f");
    // float *pval2 = (float*)val[0]->val;
    // for (ud_ut_count i = 0; i < 5; ++i) printf("%f ", pval2[i]);
    // printf("\n%zd %zd\n", test2->len, test2->type_s);

    // ud_arr_print(test2, float, "%f");
    ud_arr *main_test = ud_arr_set(ud_arr*,
                            ud_arr_set(float, 1, 2),
                            ud_arr_set(ud_arr*, 
                                ud_arr_set(float, 3, 4), ud_arr_set(float, 5, 6)));
    ud_arr_print(main_test, float, "%f ");
    
    printf("\nTry delete\n\n");
    // printf("%zd\n", ((ud_arr**)main_test->val)[0]->type_s);

    // ud_arr_rm_idx(main_test, 0, true);
    ud_arr **test_adr = &(((ud_arr**)main_test->val)[0]);
    ud_arr_rm_adr(main_test, test_adr, true);

    printf("\nTry printf\n\n");
    printf("%zd\n", ((ud_arr**)main_test->val)[0]->type_s);
    ud_arr_print(main_test, float, "%f ");
    ud_arr_free(main_test);
    return (0);
}