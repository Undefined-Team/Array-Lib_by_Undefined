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

void test_new_type_pf_char(void *val, ...)
{
    // (void)pformat;
    printf("<%c>", *(char*)val);
}

void ud_arr_test_tmp(void)
{
    char a = 'a';
    ud_arr *init = ud_arr_init(char, 5);
    ud_arr *init_val = ud_arr_init_val(char, 5, &a);
    ud_arr *init_z = ud_arr_init_z(char, 5);
    ud_arr *init_set = ud_arr_set(char, 'a', 'b', 'c');
    ud_arr *init_set2 = ud_arr_set(int, 1, 2, 3, 4, 5);
    ud_arr *cpy = ud_arr_cpy(init_set);
    ud_arr *cpy2 = ud_arr_cpy(init_set2);
    ud_arr *init_null = ud_arr_init(char *, 0);
    ud_arr *init_val_null = ud_arr_init_val(char *, 0, NULL);
    ud_arr *init_z_null = ud_arr_init_z(char *, 0);
    ud_arr *init_set_null = ud_arr_set(char *, NULL);
    ud_arr *cpy_null = ud_arr_cpy(NULL);

    ud_ut_test(init->len == 5);
    ud_ut_test((((char *)init->val)[0] = 'a') == 'a');
    ud_ut_test((((char *)init->val)[1] = 'b') == 'b');
    ud_ut_test((((char *)init->val)[2] = 'c') == 'c');
    ud_ut_test((((char *)init->val)[3] = 'd') == 'd');
    ud_ut_test((((char *)init->val)[4] = 'e') == 'e');
    ud_ut_test(init_z->len == 5);
    ud_ut_test(!ud_mem_cmp(init_z->val, "\0\0\0\0\0", 5));
    ud_ut_test(init_val->len == 5);
    ud_ut_test(!ud_mem_cmp(init_val->val, "aaaaa", 5));
    ud_ut_test(init_set->len == 3);
    ud_ut_test(!ud_mem_cmp(init_set->val, "abc", 3));
    ud_ut_test(init_set2->len == 5);
    ud_ut_test(!ud_mem_cmp(init_set2->val, (int[5]){1,2,3,4,5}, 5 * sizeof(int)));

    ud_arr_rm_idx(init_set2, 3);
    ud_ut_test(!ud_mem_cmp(init_set2->val, (int[4]){1,2,3,5}, 4 * sizeof(int)));
    ud_ut_test(init_set2->len = 4);
    ud_arr_rm_adr(init_set2, &(((int *)init_set2->val)[2]));
    ud_ut_test(!ud_mem_cmp(init_set2->val, (int[3]){1,2,5}, 3 * sizeof(int)));
    ud_ut_test(init_set2->len == 3);
    ud_arr_rm_idx(init_set2, 0);
    ud_ut_test(!ud_mem_cmp(init_set2->val, (int[2]){2,5}, 2 * sizeof(int)));
    ud_ut_test(init_set2->len == 2);
    ud_arr_rm_idx(init_set2, 0);
    ud_ut_test(!ud_mem_cmp(init_set2->val, (int[1]){5}, 1 * sizeof(int)));
    ud_ut_test(init_set2->len == 1);
    ud_arr_rm_idx(init_set2, 0);
    ud_ut_test(init_set2->len == 0);
    ud_arr_rm_idx(init_set2, 0); // verif if seg fault
    ud_ut_test(init_set2->len == 0);

    ud_ut_test(cpy->len == init_set->len);
    ud_ut_test(cpy != init_set);
    ud_ut_test(!ud_mem_cmp(cpy->val, init_set->val, cpy->len));
    ud_ut_test(cpy2->len > init_set2->len);
    ud_ut_test(cpy2 != init_set2);
    ud_ut_test(ud_mem_cmp(cpy2->val, init_set2->val, cpy2->len));
    ud_ut_test(!ud_mem_cmp(cpy2->val, (int[5]){1,2,3,4,5}, 5 * sizeof(int)));

    ud_ut_test(init_null->len == 0);
    ud_ut_test(init_null->val == NULL);
    ud_ut_test(init_val_null->len == 0);
    ud_ut_test(init_val_null->val == NULL);
    ud_ut_test(init_z_null->len == 0);
    ud_ut_test(init_z_null->val == NULL);
    ud_ut_test(init_set_null->len == 1);
    ud_ut_test(((char **)init_set_null->val)[0] == NULL);
    ud_ut_test(cpy_null->len == 0);
    ud_ut_test(cpy_null->val == NULL);

    // verif segfault on print
    printf("\n");
    ud_arr_print(init);
    ud_arr_print(init_val);
    ud_arr_print(init_z);
    ud_arr_print(init_set);
    ud_arr_print(init_set2);
    ud_arr_print(cpy);
    ud_arr_print(cpy2);
    ud_arr_print(init_null);
    ud_arr_print(init_val_null);
    ud_arr_print(init_z_null);
    ud_arr_print(init_set_null);
    ud_arr_print(cpy_null);
    ud_arr_print(NULL);

    // verif segfault on free
    ud_arr_free(init);
    ud_arr_free(init_val);
    ud_arr_free(init_z);
    ud_arr_free(init_set);
    ud_arr_free(init_set2);
    ud_arr_free(cpy);
    ud_arr_free(cpy2);
    ud_arr_free(init_null);
    ud_arr_free(init_val_null);
    ud_arr_free(init_z_null);
    ud_arr_free(init_set_null);
    ud_arr_free(cpy_null);
    ud_arr_free(NULL);

    // compile with "./compile.sh noupdate nodepmake && valgrind ./executable to check leaks"
}

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
    // ud_arr *main_test = ud_arr_set(ud_arr*,
    //                         ud_arr_set(float, 1, 2),
    //                         ud_arr_set(ud_arr*, 
    //                             ud_arr_set(float, 3, 4), ud_arr_set(float, 5, 6)));
    // ud_arr_print(main_test, float, "%f ");
    
    // printf("\nTry delete\n\n");
    // // printf("%zd\n", ((ud_arr**)main_test->val)[0]->type_s);

    // // ud_arr_rm_idx(main_test, 0, true);
    // ud_arr **test_adr = &(((ud_arr**)main_test->val)[0]);
    // ud_arr_rm_adr(main_test, test_adr, true);

    // printf("\nTry printf\n\n");
    // printf("%zd\n", ((ud_arr**)main_test->val)[0]->type_s);
    // ud_arr_print(main_test, float, "%f ");
    // ud_arr_free(main_test);

    // ud_arr_type_set_fp_print(char, test_new_type_pf_char);

    // ud_arr *test = ud_arr_tset(float, ud_arr_type_get(float), 2.5, 2.4);
    // ud_arr *str = ud_arr_set(char, 'c', 'a');
    // ud_arr *mainv = ud_arr_set(ud_arr*, test, str);

    // ud_arr *cpymain = ud_arr_cpy(mainv);
    // ud_arr_print(cpymain);
    // ud_arr_free(cpymain);
    // printf("before rm %zd\n", mainv->len);
    // // ud_arr_rm_idx(mainv, 0, false);
    // ud_arr **testadr = &(((ud_arr**)mainv->val)[1]);
    // ud_arr_rm_adr(mainv, testadr, true);
    // float *nbr = &(*(float*)test->val);
    // ud_arr_rm_adr(test, nbr, true);
    // printf("before print\n");
    // ud_arr_print(mainv);
    // printf("before free %zd\n", mainv->len);
    // ud_arr_free(mainv);
    // ud_arr_test_tmp();

    ud_arr *test = ud_arr_set(float, 1.5, 7.2, 8.2, 8.3);    
    ud_arr_reorder(test, 1, 0, 3, 2);
    ud_arr_print(test);
    ud_arr_free(test);
    return (0);
}