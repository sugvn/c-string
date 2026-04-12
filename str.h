#ifndef STR_H
#define STR_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct{
        char* val;
        size_t len;
}Str;

Str* str_create(const char* s){
        size_t len = strlen(s);
        Str* str = (Str*)malloc(sizeof(Str));
        if(!str) return NULL;
        str->val = (char*)malloc(len);
        if(!str->val) {
                free(str);
                return NULL;
        }
        str->len = len;
        return str;
}

#endif
