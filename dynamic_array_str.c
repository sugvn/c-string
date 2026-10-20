#include <stdbool.h>
#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include "dynamic_array_str.h"
#include "str.h"

int vec_str_init(vec_str* vector,size_t capacity){
        // only pass stack initialised object
        if(!vector) return -1;
        if(capacity==0) return -1;
        vector->ptr = (Str*)malloc(capacity*sizeof(Str));
        if(!vector->ptr) return -1;
        vector->capacity = capacity;
        vector->size = 0;
        return 0;
}

Str vec_str_get(const vec_str* vector,size_t index){
        if(!vector) {
                perror("Accessing Null ptr");
                exit(EXIT_FAILURE);
        }
        if(index >= vector->size) {
                perror("Out of Bound indexing");
                exit(EXIT_FAILURE);
        }
        return (vector->ptr)[index];
}

void vec_str_put(vec_str* vector,size_t index,Str value){
        if(!vector) {
                perror("Accessing Null ptr");
                exit(EXIT_FAILURE);
        }
        if(index >= vector->size) {
                perror("Out of Bound indexing");
                exit(EXIT_FAILURE);
        }
        if(!value.val) {
                perror("Uninitialised string");
                exit(EXIT_FAILURE);
        }
        if(value.val==vector->ptr[index].val) return;
        free(vector->ptr[index].val);
        (vector->ptr)[index] = value;
}

void vec_str_append(vec_str* vector,Str value){
        if(!vector) {
                perror("Accessing Null ptr");
                exit(EXIT_FAILURE);
        }
        if(!value.val) {
                perror("Uninitialised string");
                exit(EXIT_FAILURE);
        }
        if(vector->size == vector->capacity){
                vector->ptr = realloc(vector->ptr,vector->capacity*2*sizeof(Str));
                if(!vector->ptr) {
                        perror("Reallocation failed");
                        exit(EXIT_FAILURE);
                }
                vector->capacity*=2;
        }
        (vector->ptr)[vector->size] = value;
        vector->size += 1;
}

void vec_str_free(vec_str* vector){
        if(!vector) return;
        size_t n = vector->size;
        for(size_t i=0;i<n;i++){
                free(vector->ptr[i].val);
        }
        free(vector->ptr);
        vector->ptr = NULL;
        vector->size = vector->capacity = 0;
}

bool vec_str_is_empty(vec_str *vector){
        if(!vector) return true;
        if(!vector->ptr) return true;
        if(vector->size==0) return true;
        return false;
}
