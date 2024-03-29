/**************************************************************************************************
 * Copyright (C) 2019-2021 Maxim Integrated Products, Inc. All Rights Reserved.
 *
 * Maxim Integrated Products, Inc. Default Copyright Notice:
 * https://www.maximintegrated.com/en/aboutus/legal/copyrights.html
 **************************************************************************************************/

/*
 * This header file was automatically generated for the mnist network from a template.
 * Please do not edit; instead, edit the template and regenerate.
 */

#ifndef __CNN_H__
#define __CNN_H__

#include <stdint.h>
typedef int32_t q31_t;
typedef int16_t q15_t;

/* Return codes */
#define CNN_FAIL 0
#define CNN_OK 1

/*
  SUMMARY OF OPS
  Hardware: 10,883,968 ops (10,751,808 macc; 128,576 comp; 3,584 add; 0 mul; 0 bitwise)
            True MACs: 0
    Layer 0: 470,400 ops (423,360 macc; 47,040 comp; 0 add; 0 mul; 0 bitwise)
    Layer 1: 8,356,800 ops (8,294,400 macc; 62,400 comp; 0 add; 0 mul; 0 bitwise)
    Layer 2: 1,954,304 ops (1,935,360 macc; 18,944 comp; 0 add; 0 mul; 0 bitwise)
    Layer 3: 100,544 ops (96,768 macc; 192 comp; 3,584 add; 0 mul; 0 bitwise)
    Layer 4: 1,920 ops (1,920 macc; 0 comp; 0 add; 0 mul; 0 bitwise)

  RESOURCE USAGE
  Weight memory: 71,148 bytes out of 442,368 bytes total (16%)
  Bias memory:   10 bytes out of 2,048 bytes total (0%)
*/

/* Number of outputs for this network */
#define CNN_NUM_OUTPUTS 10
#define CNN_NUM_OUTPUTS_LAYER_0 48
#define CNN_NUM_OUTPUTS_LAYER_1 10
#define CNN_NUM_OUTPUTS_FROZEN_LAYER 192

/* Number of layers */
#define LAYER_NUM 5

/* Number of One-Shot layers */
#define OS_LAYER_NUM 1

/* One-Shot layers */
#define OS_LAYERS {0}

/* Use this timer to time the inference */
#define CNN_INFERENCE_TIMER MXC_TMR0

/* Port pin actions used to signal that processing is active */

#define CNN_START LED_On(1)
#define CNN_COMPLETE LED_Off(1)
#define SYS_START LED_On(0)
#define SYS_COMPLETE LED_Off(0)

/* Run software SoftMax on unloaded data */
void softmax_q17p14_q15(const q31_t *vec_in, const uint16_t dim_vec, q15_t *p_out);
/* Shift the input, then calculate SoftMax */
void softmax_shift_q17p14_q15(q31_t *vec_in, const uint16_t dim_vec, uint8_t in_shift, q15_t *p_out);

/* Stopwatch - holds the runtime when accelerator finishes */
extern volatile uint32_t cnn_time;

/* Custom memcopy routines used for weights and data */
void memcpy32(uint32_t *dst, const uint32_t *src, int n);
void memcpy32_const(uint32_t *dst, int n);

/* Enable clocks and power to accelerator, enable interrupt */
int cnn_enable(uint32_t clock_source, uint32_t clock_divider);

/* Disable clocks and power to accelerator */
int cnn_disable(void);

/* Perform minimum accelerator initialization so it can be configured */
int cnn_init(void);

/* Load accelerator weights */
int cnn_load_weights(void);

/* Verify accelerator weights (debug only) */
int cnn_verify_weights(void);

/* Load accelerator bias values (if needed) */
int cnn_load_bias(void);

/* Start accelerator processing */
int cnn_start(void);

/* Force stop accelerator */
int cnn_stop(void);

/* Continue accelerator after stop */
int cnn_continue(void);

/* Unload results from accelerator */
int cnn_unload(uint32_t *out_buf);

/* Unload results of frozen model from accelerator */
int cnn_unload_frozen_layer(uint32_t *out_buf);

/* Specific layer initialization */
int cnn_init_layer(int layer_num);

/* Specific layer configuration */
int cnn_config_layer(int layer_num);

/* Start a specific layer */
int cnn_start_layer(int layer_num);

/* Stop all the cnn State Machines */
void cnn_stop_SMs();

/* Get the next One-Shot layer available */
int get_next_OS_layer(int layer_count);

/* Get last One-Show layer number */
int get_last_OS_layer();

/* Set layer count value to configuration registers*/
int cnn_set_layer_count(int layer_num);

#endif // __CNN_H__
