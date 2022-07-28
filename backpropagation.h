/**
 * @file backpropagation.h
 * @author Giovanni Lunardi (giovanni.lunardi@studenti.unitn.com)
 * @brief Backpropagation: last layer weights update
 * @version 0.1
 * @date 2022-07-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BACKPROPAGATION_H__
#define __BACKPROPAGATION_H__

#include <cnn.h>

/**
 * @brief substraction of 2 arrays, ml_softmax - true_output.
 *        We find the difference between the softmax output and the output
 *        we are seeking to obtain in online learning
 * 
 * @param res result array
 * @param arr1 true_output array
 * @param arr2 ml_softmax array
 * @param size size of arrays
 */
void array_substraction(q15_t *res, q15_t *arr1,q15_t *arr2, int size );

/**
 * @brief multiplication of 1 value with an array.
 *        We find the deltaW which is the multiplication between each output value
 *        and the array obtained by substraction
 * @param res result array
 * @param cost first array 
 * @param out_value cnn output value before softmax activation 
 * @param size size of arrays
 */
void delta_multiplication(q15_t *res, q15_t *cost, int32_t out_value,int size);

/**
 * @brief multiply each element of the delta array for a learning rate
 * 
 * @param res result array, dW
 * @param delta delta array
 * @param l_rate learning rate
 * @param size size of the delta array
 */
void dW_multiplication(q15_t *res, q15_t *delta,uint32_t l_rate, int size);

#endif // __BACKPROPAGATION_H__