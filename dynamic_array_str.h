#ifndef DYNAMIC_ARRAY_STR
#define DYNAMIC_ARRAY_STR
#include <stdbool.h>
#include<stddef.h>
#include "str.h"

typedef struct {
        Str *ptr;
        size_t size;
        size_t capacity;
}vec_str;

// returns 0 on success, -1 on error
int  vec_str_init(vec_str *vector, size_t capacity);
void vec_str_free(vec_str *vector);
Str  vec_str_get(const vec_str *vector, size_t index);
void vec_str_put(vec_str *vector, size_t index, Str value);
void vec_str_append(vec_str *vector, Str value);
bool vec_str_is_empty(vec_str *vector);

#endif
