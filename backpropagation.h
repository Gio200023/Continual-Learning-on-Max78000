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

#define ITERATIONS 1400

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
void array_substraction(int *res, q15_t *arr1, int *arr2, int size);

/**
 * @brief take output of layer_num layer and transform it in mod2
 *
 * @param out crude hex output of frozen layer
 * @param final array which will contain the mod2-frozen layer output
 *
 */
void output_layer_3(const int32_t out, uint8_t *final);

/**
 * @brief transform in mod2 an hex number according to maxim formula
 *        w = (-val_7 2^7+val_6 2^6+val_5 2^5+val_4 2^4+val_3 2^3+val_2 2^2+val_1 2^1+val_0)/128
 *
 * @param val hex to transform
 * @return int mod2 number
 */
int mod2(int val);

/**
 * @brief if CHOOSE==FIND obtain the first channel array of weigths 
 *        if CHOOSE==UPDATE update weigths
 *
 * @param weights array that will contains the weights
 * @param choose choose between Find weights or Update weights
 * @param dW if (Choose==Update), value to update every single weights
 */
void find_weights(int8_t (*weights)[], int choose, int (*dW)[]);

/**
 * @brief update bias
 * 
 * @param cost cost array 
 * @param learning_rate learning rate 
 */
void bias_update(q15_t *cost, float learning_rate);

#endif // __BACKPROPAGATION_H__