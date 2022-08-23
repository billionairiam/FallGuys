#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __clang__
#define __attribute_no_sanitize_address __attrubute__((no_santize("address")))
#else
#define __attribute_no_sanitize_address
#endif

char* alloc_concat3(const char* a, size_t a_len, const char* b, size_t b_len, 
                    const char* c, size_t c_len);
char* alloc_concat(const char* a, size_t a_len, const char* b, size_t b_len);
char* alloc_substr(const char* start, size_t len);
char* strdup(const char* str);