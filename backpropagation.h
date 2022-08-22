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

#include "cnn.h"

#define UPDATE 1
#define FIND 0

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
void array_substraction(q15_t *res, q15_t *arr1, q15_t *arr2, int size);

/**
 * @brief take output of layer_num layer and it transform it in mod2
 *
 * @param out crude hex output of frozen layer
 * @param final array which will contain the frozen layer output
 *
 */
void output_layer_3(const int32_t out, uint8_t *final);

/**
 * @brief transform in mod2 an hex number according to maxim formula
 *
 * @param val hex to transform
 * @return int mod2 number
 */
int mod2(int val);

/**
 * @brief obtain the first channel array of weigths
 *
 * @param weights array that will contains the weights
 */
void find_weights(int8_t (*weights)[], int choose, int (*dW)[]);

#endif // __BACKPROPAGATION_H__