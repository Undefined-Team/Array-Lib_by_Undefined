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

// # define __ud_va_argsiz(t)	
// 	(((t + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

// # define ud_va_arg(ap, t)					
// 	 (((ap) = (ap) + __ud_va_argsiz(t)),		
// 	  *((char**) (void*) ((ap) - __ud_va_argsiz(t))))

// #define __va_argsiz(t)	
// 	(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

// #define ud_va_arg(ap, t)					
// 	 (((ap) = (ap) + __va_argsiz(t)),		
// 	  *((t*) (void*) ((ap) - __va_argsiz(t))))

// char* ud_va_arg(char **va, size_t type_size)
// {
//     char* old;

//     size_t int_size = sizeof(int);
//     old = *va;
//     *va += (((type_size + int_size - 1) / int_size) * int_size);
//     return old;
// }

// char* ud_va_arg(va_list *va, size_t type_size)
// {
//     char* old;

//     size_t int_size = sizeof(int);
//     old = *((char**)(void*)*va);
//     *va = *va + (((type_size + int_size - 1) / int_size) * int_size);
//     return old;
// }

// typedef char* ud_va_list;
// #define ud_va_start(ap, param) (void)(ap = (char*)&param + sizeof(param))
// #define ud_va_end(ap) (void)(ap = NULL)
// #define ud_va_copy(dest, src) (void)(dest = src)
// #define ud_va_arg(ap, type_size) (*(char**)((ap = ap + type_size) - type_size))
// #define ud_va_arg(ap, type) (*((type*)ap)++)

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

// #define ud_va_arg(ap, t)					
// 	 (((ap) = (ap) + __va_argsiz(t)),		
// 	  *((t*) (void*) ((ap) - __va_argsiz(t))))

// ud_arr      *ud_arr_set(size_t type_size, size_t len, ...)
// {
//     ud_arr      *new_arr;
//     va_list     va;

//     UD_UT_PROT_MALLOC(new_arr = ud_arr_init(sizeof(type), len));
//     if (!len) return new_arr;
//     type *val = (type*)new_arr->val;
//     ud_va_start(va, len);
//     while (len-- > 0)
//         *val++ = (type)va_arg(va, type);
//     ud_va_end(va);
//     return new_arr;
// }