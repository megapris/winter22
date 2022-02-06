#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size){
    lite_vector *vector = malloc(sizeof vector);
    vector->length =0;
    vector->max_capacity=100;
    vector->data=malloc(sizeof vector->data);
    //still need to figure out how to return null
    return vector;
    
}

void lv_cleanup(lite_vector* vec){
    free(vec->data);
    free(vec);
}

bool lv_clear(lite_vector* vec){
    vec->length=0;
    vec->max_capacity=100;
    vec->data=NULL;

    if(vec->length != 0)
        return false;
    return true;
}
size_t lv_get_length(lite_vector* vec){
    return vec->length;
}
void* lv_get(lite_vector* vec, size_t index){

    printf("Vector.c address of head %p \n",vec->data);

    if(index == 0)
        return vec->data;

    void** tmp;
    tmp=vec->data + 1 * sizeof(vec->data);
    // for(int i=1;i< index;++i){
    //     tmp=vec->data + i * sizeof(vec->data);
    // }
    return tmp;

}

/**
 * lv_resize is essentially private since we marked it static.
 * The job of this function is to attempt to resize the vector.
 * There may be functions you can call to do this for you, or
 * you may write it yourself.  Either way it isn't too hard.
 * With everything though, check to make sure the code worked
 * and return appropriately.  Do NOT destroy the data if the code
 * fails.  If the resize cannot complete, the original vector
 * must remain unaffected.
 */
static bool lv_resize(lite_vector* vec){
    if(vec->length == vec->max_capacity -1){
        lite_vector *bigger = vec;
        memcpy(vec,bigger, sizeof(bigger)*10);
    }
}

bool lv_append(lite_vector* vec, void* element){
    vec->data=element;
    vec->length++;

}
