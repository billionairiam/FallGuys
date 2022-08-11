#include <stdarg.h>
#include <stdio.h>

#ifdef __clang__
#define __attribute_no_sanitize_address __attrubute__((no_santize("address")))
#else
#define __attribute_no_sanitize_address
#endif
