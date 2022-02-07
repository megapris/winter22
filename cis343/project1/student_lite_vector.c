#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**************************************************************************
 * Short code that implements a vector through the manipulation of
 * pointers.
 * 
 * @author Priscila Ontiveros
 * Feb 7, 2022 
 **************************************************************************/


/**
 * @brief Creates a new vector while dynamically stored, while intializaing 
 * its properties. It initializes the lenght to 0, as there are no elements
 * when first created. It starts with a max capacity of 100 elements, which
 * can be resized if needed at thelv_resize() fuction.
 * 
 * @return a lite_vector* and null if operation fails. 
 */
lite_vector* lv_new_vec(size_t type_size){
    // dynamically request for memory and assign pointer to a vector pointer
        lite_vector *vector = malloc(sizeof *vector);
    // set lenght to 0, there are no elements when its created
        vector->length =0;
    // initialize max capacity to 100
    // note max capacity can be analized to any number, 100 seemed like a good number
        vector->max_capacity=100;
    // ask memory for the data, which will hold the elements desired to store
        vector->data=malloc(sizeof (void *) * 100);
  

    //malloc() will return a pointer to the allocated memory or null if the operation fails
        return vector;
}



/**
 * @brief will free all memory used by the vector 
 * 
 * @param vec, the address of the vector for which we want to free the memory
 */
void lv_cleanup(lite_vector* vec){
    // deallocates the memory previously allocated for the vector
        free(vec->data);
        free(vec);
}

/**
 * @brief clears the contents of the properties of the vector, but does not
 * deallocate the memory of the vector
 * 
 * @param vec, the address of the vector we need to clear
 * @return true when it was able to properly clear the contents
 * @return false if either @param vec is null or if the value returned by malloc()
 *               is null
 */
bool lv_clear(lite_vector* vec){
    // checks to make sure vec is not null, if null returns false 
    if(vec != NULL){
        // resets lenght to 0
            vec->length=0;
        // resets max capacity to 100
            vec->max_capacity=100;
        // deallocates the memory previously allocated for the vector
            free(vec->data);
         // ask for new memory for the data, which will hold the elements desired to store
        vec->data=malloc(sizeof (void *) * 100);

        // if malloc operation failed, then it will return false
            if(vec->data == NULL) return false;
        // if it malloc() didnt fail then return true
            else return true;
    }
    return false;

}

/**
 * @brief returns the number of elements stored in the vector
 * 
 * @param vec the address of the vector
 * @return size_t the numbe of elements or 0 if the operation fails
 */
size_t lv_get_length(lite_vector* vec){
    // if thevector is not null then return the length
        if(vec != NULL)
            return vec->length;
    // if null return 0
        else 
            return 0;
}

/**
 * @brief gets an element from a vector
 * 
 * @param vec the address of the vector
 * @param index from which we want to retrieve the element
 * @return void* the element from the vector or null if failed
 */
void* lv_get(lite_vector* vec, size_t index){
    // it will return null if the vector itself is null or if the
    // index requested is bigger than the actual number of elements
        if( vec == NULL || index > vec->length)
            return NULL;
    // if vec is not null and if the index is within bounds the return the element
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

    // ask for double the size of memory and assign the pointer to a tmp variable
        void **data2 = malloc(sizeof(void *)*2* vec->length); 
    // copy the data to temp variable with double the size of memory
        memcpy(data2, vec->data,sizeof(void *)*vec->length);

    // update the max capacity of vector
        vec->max_capacity*=2;
    // deallocates the memory previously allocated for the vector
        free(vec->data);
    // sets old pointer to new data
        vec->data=data2;

    // this for loop checks that the copy of elements was sucessful, by comparing the "old" data to the
    // new data, if at some point the elements differ then it returns false
        for(int i =0; i < (int)vec->length;i++){
            if(data2[i] != vec->data[i])
                return false;
        }
    // if for loop didn't return false, if will return true
        return true;
   

}

/**
 * @brief it appends one element to the vector
 * 
 * @param vec the address of the vector
 * @param element the address of the element we want to append
 * @return true if it successfully added the element
 * @return false if @param vec is null or if resize failed
 */
bool lv_append(lite_vector* vec, void* element){
    // checks if vector is not null, if null returns false
        if(element != NULL){
            // variable to keep track of the status of resize
                bool sucess = true;
            // if the number is elements is the same as the max capacity
            // the call for resize
                if(vec->length ==vec->max_capacity){
                    sucess = lv_resize(vec);
                }
            // add the element 
                vec->data[vec->length]=element;
            // incraese the lenght;
            vec->length++;
            // return true if resize was successful, otherwise false
            return sucess;

        }
        return false;

}
