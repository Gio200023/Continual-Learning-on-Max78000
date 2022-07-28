/********************
 * 
 *  Backpropagation 
 * 
*********************/

#include "backpropagation.h"
#include <stdint.h>
#include "cnn.h"

void array_substraction(q15_t *res,q15_t *arr1,q15_t *arr2, int size ){

    q15_t tmp[size];
    int i=0;  
    for(i=0 ; i< size; i++){
        tmp[i]=arr1[i]-arr2[i];
    }
    for(i=0; i < size; i++){
        if (tmp[i]<=0) res[i]=0;
        else res[i]=0x7fff;
    }
}

void delta_multiplication(q15_t *res, q15_t *cost, int32_t out_value,int size){

    for(int i=0; i < size; i++){
        res[i]=cost[i] * out_value;
    }
}

void dW_multiplication(q15_t *res, q15_t *delta,uint32_t l_rate, int size){

    for(int i=0; i< size; i++){
        res[i]=delta[i]*l_rate;
    }
}


