/*******************************************************************************
 * Copyright (C) 2019-2022 Maxim Integrated Products, Inc., All rights Reserved.
 *
 * This software is protected by copyright laws of the United States and
 * of foreign countries. This material may also be protected by patent laws
 * and technology transfer regulations of the United States and of foreign
 * countries. This software is furnished under a license agreement and/or a
 * nondisclosure agreement and may only be used or reproduced in accordance
 * with the terms of those agreements. Dissemination of this information to
 * any party or parties not specified in the license agreement and/or
 * nondisclosure agreement is expressly prohibited.
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************/

// mnist
// Created using ai8xize.py --log --test-dir sdk/Examples/MAX78000/CNN --prefix mnist --checkpoint-file trained/ai85-mnist-qat8-q.pth.tar --config-file networks/mnist-chw-ai85.yaml --softmax --overwrite --debug --log-pooling --debug-computation --compact-data --mexpress --timer 0 --display-checkpoint --device MAX78000 --timer 0 --display-checkpoint --verbose

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "mxc.h"
#include "cnn.h"
#include "sample_inputs.h"
#include "sampledata_mnist.h"
#include "math.h"
#include "backpropagation.h"
#include "pb.h"

/**
 * @brief weigths array
 *
 */
int8_t weights[CNN_NUM_OUTPUTS][CNN_NUM_OUTPUTS_FROZEN_LAYER] = {0};

/**
 * @brief predictions of every channel -> weights[][] x output[LAYER_NUM-1]
 *
 */
static int prediction[CNN_NUM_OUTPUTS][CNN_NUM_OUTPUTS_FROZEN_LAYER] = {0};

// Learning rate
float learning_rate = 0.05;

// True output array and cost array
int true_output[CNN_NUM_OUTPUTS] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int cost[10] = {0};

// Values to subtract
int deltaW = 0;
static int dW[CNN_NUM_OUTPUTS][CNN_NUM_OUTPUTS_FROZEN_LAYER] = {0};

// Output array
static int32_t ml_data[CNN_NUM_OUTPUTS];
static int32_t ml_data_frozen[CNN_NUM_OUTPUTS_LAYER_0];
static int8_t output_L0[CNN_NUM_OUTPUTS_FROZEN_LAYER] = {0}; // cambiato da uint a int

// Softmax array
static q15_t ml_softmax[CNN_NUM_OUTPUTS];

volatile uint32_t cnn_time;  // Stopwatch
volatile uint32_t timestamp; // timer CL

void fail(void)
{
  printf("\n*** FAIL ***\n\n");
  while (1)
    ;
}

// 1-channel 28x28 data input (784 bytes / 196 32-bit words):
// CHW 28x28, channel 0
int input = 0;
static uint32_t *input_0;
void load_input(void)
{
  if (input == 40)
  {
    input = 0;
  }
  input_0 = (uint32_t *)sample_inputs_all[input++];
  memcpy32((uint32_t *)0x50400000, input_0, 196);
}
static const uint32_t input_1[] = SAMPLE_INPUT_MNIST;

void load_input1(void)
{
  // This function loads the sample data input -- replace with actual data

  memcpy32((uint32_t *)0x50400000, input_1, 196);
}

void softmax_layer(void)
{
  cnn_unload((uint32_t *)ml_data); // va a prendersi i risultati
  softmax_q17p14_q15((const q31_t *)ml_data, CNN_NUM_OUTPUTS, ml_softmax);
}

void print_inference_result(void)
{
  int digs, tens;

  for (int inf = 0; inf < CNN_NUM_OUTPUTS; inf++)
  {
    digs = (1000 * ml_softmax[inf] + 0x4000) >> 15;
    tens = digs % 10;
    digs = digs / 10;
    printf("[%7d] -> Class %d: %d.%d%%\n", ml_data[inf], inf, digs, tens);
  }
}

int step = 0;
int main(void)
{
  int i, f = 0;

  MXC_ICC_Enable(MXC_ICC0); // Enable cache

  // Clock Selection
  MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO); // 100 MHz
  // MXC_SYS_Clock_Select(MXC_SYS_CLOCK_ISO); // 60 MHz
  // MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IBRO); // 7.3728 MHz

  SystemCoreClockUpdate();

  printf("\nWaiting to set up debugger\n");

  // DO NOT DELETE THIS LINE:
  MXC_Delay(SEC(2)); // Let debugger interrupt if needed

  /**************************************************************************
   *  INFERENCE LAYER BY LAYER WITH BACKPROPAGATION --> CONTINUAL LEARNING
   *************************************************************************/

  // Enable peripheral, enable CNN interrupt, turn on CNN clock
  // CNN clock: APB (50 MHz) div 1
  cnn_enable(MXC_S_GCR_PCLKDIV_CNNCLKSEL_PCLK, MXC_S_GCR_PCLKDIV_CNNCLKDIV_DIV1);

  int layer_count = 0;
  for (i = 0; i < 100; i++)
  {
    cnn_init();         // Bring state machines to consistent state
    cnn_load_weights(); // Load kernels
    cnn_load_bias();    // Load biases

    for (layer_count = 0; layer_count < LAYER_NUM; layer_count = get_next_OS_layer(layer_count))
    {
      cnn_set_layer_count(layer_count);
      cnn_config_layer(layer_count);

      if (layer_count == 0)
        load_input();
      cnn_start(); // Start state machines

      while (cnn_time == 0)
        __WFI(); // Wait for CNN

      if (layer_count == 0)
      {
        /* take output of last but one layer */
        cnn_unload_frozen_layer((uint32_t *)ml_data_frozen);
        output_layer_3(ml_data_frozen, output_L0);

        /* find weights of every channel */
        weights_function(weights, FIND, dW, cost);
      }

      cnn_stop_SMs(); // Be sure that before next iterations all the State Machines are stopped
    }
    softmax_layer(); // Softmax array with percentage

    if ((i + 1) % 100 == 0)
    {
      input = 0;
    }

#ifdef CNN_INFERENCE_TIMER
    if (i % 100 == 0)
    {
      printf("Classification results of [%d] lap:\n", i);
      print_inference_result();
      printf("Approximate inference time of %d iteration: %u us\n\n", i, cnn_time);
    }
#endif

    /* predict channels output */
    for (f = 0; f < CNN_NUM_OUTPUTS; f++)
    {
      for (int place = 0; place < CNN_NUM_OUTPUTS_FROZEN_LAYER; place++)
      {
        prediction[f][place] = (weights[f][place] * output_L0[place]);
      }
    }

    /********************
     *  BACKPROPAGATION  *
     ********************/

    /* Mesaure weights update */
    MXC_TMR_SW_Start(MXC_TMR1);

    /* Find neurons that need a weights change */
    array_substraction(cost, ml_softmax, true_output, sizeof ml_softmax / sizeof ml_softmax[0]);
    int tmp;
    for (f = 0; f < CNN_NUM_OUTPUTS; f++) // for every output channel
    {
      for (int place = 0; place < CNN_NUM_OUTPUTS_FROZEN_LAYER; place++) // for the lenght of each channel
      {
        /* Update on every channel */
        deltaW = cost[f] * /*(q15_t)*/ prediction[f][place]; // deltaW is the prediction of the f^th times cost[f]
        tmp = ((float)learning_rate * deltaW);
        if (tmp < -128)
        {
          tmp = -128;
        }
        else if (tmp > 127)
        {
          tmp = 127;
        }
        dW[f][place] = tmp; // dW is the value to deduct from the weights
      }
    }

    /* Update weights */
    weights_function(weights, UPDATE, dW, cost);

    /* Update Biases */
    bias_update(cost, learning_rate);

    /* Print step and time to update weights and biases */
    timestamp = MXC_TMR_SW_Stop(MXC_TMR1);
    printf("step: %4d, timer = %u\n", step++, timestamp);
  }

  /*******************************
   * Inference on every 45 samples
   *******************************/
  cnn_init();         // Bring state machines to consistent state
  cnn_load_weights(); // Load kernels
  cnn_load_bias();    // Load biases
  cnn_config_layer(0);
  for (int l = 0; l < 45; l++)
  {
    load_input(); // Load data input
    cnn_start();  // Start CNN processing

    while (cnn_time == 0)
      __WFI(); // Wait for CNN

    cnn_stop_SMs();
    softmax_layer();

#ifdef CNN_INFERENCE_TIMER
    printf("Classification results of [%d] image:\n", l);
    print_inference_result();
    printf("Approximate inference time of %d iteration: %u us\n\n", i, cnn_time);
#endif
  }
  /**********************************
   *  INFERENCE on mnist digit 8
   ************************************/
  load_input1(); // Load data input
  cnn_start();   // Start CNN processing

  while (cnn_time == 0)
    __WFI(); // Wait for CNN

  cnn_stop_SMs();
  softmax_layer();

#ifdef CNN_INFERENCE_TIMER
  printf("\nInference on digit 8:\n");
  print_inference_result();
  printf("Approximate inference time of %d iteration: %u us\n\n", i, cnn_time);
#endif

  cnn_disable();
  return 0;
}
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
