#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

// end of string should be decided through len and not '\0'
typedef struct{
        char* val;
        size_t len;
}Str;

// code style:
// functions that return the base-type(Str) are capitalised

// allocates new memory for char*
Str STR(const char* s){
        Str str;
        size_t len = strlen(s);
        str.val = (char*)malloc(len);
        if(!str.val) return (Str){0};
        memcpy(str.val,s,len);
        str.len = len;
        return str;
}

// mutable by default
// from l_index to r_index - 1
Str STR_SLICE(Str s,size_t l_index,size_t r_index){
        if (!(l_index <= r_index && r_index <= s.len && s.val && s.len > 0)) return (Str){0};
        Str str;
        str.val = s.val + l_index;
        str.len = r_index - l_index; 
        return str;
}

bool str_eq(Str s1,Str s2){
        if(s1.len != s2.len ) return false;
        if (!s1.val || !s2.val) return false;
        return memcmp(s1.val, s2.val, s1.len) == 0;
}

Str STR_DEEP_COPY(Str s){
        if (!s.val || s.len==0) return (Str){0};
        Str str;
        str.val = (char*)malloc(s.len);
        if(!str.val) return (Str){0};
        str.len = s.len;
        memcpy(str.val, s.val ,str.len);
        return str;
}

char str_at(Str s,size_t idx){
        if (!s.val) return '\0';
        char i = idx < s.len ? s.val[idx] : '\0';
        return i;
}

void str_free(Str s){
        if (!s.val) return;
        free(s.val);
}

void str_print(Str s){
        if (!s.val) return;
        if (s.len==0) {
                printf("");
                return;
        }
        fwrite(s.val,1,s.len,stdout);
}

#endif
