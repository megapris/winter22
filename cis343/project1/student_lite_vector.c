#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size){
    lite_vector *vector = malloc(sizeof *vector);
    vector->length =0;
    vector->max_capacity=100;
    vector->data=malloc(sizeof (void *) * 100);
    //still need to figure out how to return null
    return vector;
    
}

void lv_cleanup(lite_vector* vec){
    free(vec->data);
    free(vec);
}

bool lv_clear(lite_vector* vec){
    vec->length=0;
    vec->max_capacity=10;
    free(vec->data);
    vec->data=malloc(sizeof (void *) * 100);

}
size_t lv_get_length(lite_vector* vec){
    return vec->length;
}
void* lv_get(lite_vector* vec, size_t index){

    return vec->data[index];

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
    void **data2 = malloc(sizeof(void *)*2* vec->length); 

    memcpy(data2, vec->data,sizeof(void *)*vec->length);

    
    vec->max_capacity*=2;
    free(vec->data);
    vec->data=data2;

   

}

bool lv_append(lite_vector* vec, void* element){
   
    if(vec->length ==vec->max_capacity){
        lv_resize(vec);
    }
    vec->data[vec->length]=element;

    vec->length++;

  


}
