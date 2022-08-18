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

/**
 *
 * TODO: sistemare load_weights, Load inputs da UART
 * ALMOST: sistemare cost, ora come ora da risultati ma scarsi
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "mxc.h"
#include "cnn.h"
#include "sampledata_mnist.h"
#include "math.h"
#include "backpropagation.h"

/**
 * @brief layers variables
 *
 */
uint8_t output_L0[CNN_NUM_OUTPUTS_FROZEN_LAYER] = {0};

/**
 * @brief wieghts array
 *
 */
int8_t weights[CNN_NUM_OUTPUTS_FROZEN_LAYER];

/**
 * @brief prediction #0 channel -> wieghts x n-1 layer
 *
 */
int16_t prediction[CNN_NUM_OUTPUTS_FROZEN_LAYER] = {0};
volatile uint32_t cnn_time; // Stopwatch

/* Backpropagation variables */
float learning_rate = 0.01;
int iterations = 5000;
q15_t true_output[CNN_NUM_OUTPUTS] = {0x7fff, 0, 0, 0, 0, 0, 0, 0, 0, 0};
q15_t cost[10] = {0};
int16_t deltaW = 0;
int dW[CNN_NUM_OUTPUTS_FROZEN_LAYER] = {0};
int db = 0;

void fail(void)
{
  printf("\n*** FAIL ***\n\n");
  while (1)
    ;
}

// 1-channel 28x28 data input (784 bytes / 196 32-bit words):
// CHW 28x28, channel 0
int count = 0;
// static uint32_t *input_0 = &sample_inputs_all[0][0];
static uint32_t input_0[] = SAMPLE_INPUT_MNIST;

void load_input(void)
{
  // This function loads the sample data input -- replace with actual data
  // memcpy32((uint32_t *)0x50400000, *(input_0 + count++ * 1000), 196);
  memcpy32((uint32_t *)0x50400000, input_0, 196);
}

// Classification layer:
static int32_t ml_data[CNN_NUM_OUTPUTS];
static int32_t ml_data_frozen[CNN_NUM_OUTPUTS_LAYER_0];
static q15_t ml_softmax[CNN_NUM_OUTPUTS];

void softmax_layer(void)
{
  cnn_unload((uint32_t *)ml_data); // va a prendersi i risultati
  softmax_q17p14_q15((const q31_t *)ml_data, CNN_NUM_OUTPUTS, ml_softmax);
}

int a = 0;
int main(void)
{
  int i, f = 0;
  int digs, tens;

  MXC_ICC_Enable(MXC_ICC0); // Enable cache

  // Switch to 100 MHz clock
  MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);
  SystemCoreClockUpdate();

  printf("Waiting...\n");

  // DO NOT DELETE THIS LINE:
  MXC_Delay(SEC(2)); // Let debugger interrupt if needed

  /**************************************************************************
   *  INFERENCE PER LAYER WITH BACKPROPAGATION: ONLINE LEARNING
   *************************************************************************/

  int layer_count = 0;
  // Enable peripheral, enable CNN interrupt, turn on CNN clock
  // CNN clock: APB (50 MHz) div 1
  // cnn_enable(MXC_S_GCR_PCLKDIV_CNNCLKSEL_PCLK, MXC_S_GCR_PCLKDIV_CNNCLKDIV_DIV1);

  // MXC_TMR_SW_Start(MXC_TMR1);
  volatile uint32_t *addr;
  for (i = 0; i < 10; i++)
  {
    cnn_enable(MXC_S_GCR_PCLKDIV_CNNCLKSEL_PCLK, MXC_S_GCR_PCLKDIV_CNNCLKDIV_DIV1);
    cnn_init();
    for (layer_count = 0; layer_count < LAYER_NUM; layer_count = get_next_OS_layer(layer_count))
    {
      cnn_load_weights(); // Load kernels
      cnn_load_bias();

      cnn_set_layer_count(layer_count);
      cnn_config_layer(layer_count);

      if (layer_count == 0)
        load_input();
      cnn_start();

      printf("Layer = %d\n", layer_count);

      while (cnn_time == 0)
        __WFI(); // Wait for CNN

      addr = (volatile uint32_t *)0x50400000;

      for (int l = 0; l < 10; l++)
      {
        printf("questo: %x\n",*addr++);
      }

      if (layer_count == 0)
      {
        /* take output of layer_n-1 layer */
        cnn_unload_frozen_layer((uint32_t *)ml_data_frozen); // mnist: WORKS
        output_layer_3(ml_data_frozen, output_L0);           // WORKS
        /* find weigths of first channel */
        find_weights(weights, FIND, dW); // WORKS
      }

      cnn_stop_SMs(); // Be sure that before next iterations all the State Machines are stopped
    }

    // for (i = 0; i < 2; i++)
    // {

    //   for (layer_count = 0; layer_count < LAYER_NUM; layer_count = get_next_OS_layer(layer_count))
    //   {
    //     cnn_set_layer_count(layer_count);
    //     /* start and configure layers */
    //     cnn_config_layer(layer_count);
    //     /* load input */
    //     if (layer_count == 0)
    //     {
    //       load_input();
    //     }
    //     cnn_start();

    //     while (cnn_time == 0) // forse devo ripetrmettere il caputring time
    //       __WFI();            /* Wait for CNN */

    //     cnn_stop_SMs();

    //     if (layer_count == 0)
    //     {
    //       /* take output of layer_n-1 layer */
    //       cnn_unload_frozen_layer((uint32_t *)ml_data_frozen); // mnist: WORKS
    //       output_layer_3(ml_data_frozen, output_L0);           // WORKS
    //       /* find weigths of first channel */
    //       find_weights(weights, FIND, dW); // WORKS
    //     }
    //   }

    softmax_layer();
    /* predict channel 0 */
    for (int place = 0; place < CNN_NUM_OUTPUTS_FROZEN_LAYER; place++)
    {
      prediction[place] = (weights[place] * output_L0[place]);
    }

    /********************
     *  BACKPROPAGATION  *
     ********************/

    /* Find neuron that need a weights changes */ // COST NON RIESCO A TROVARLO ANCORA: TODO
    array_substraction(cost, ml_softmax, true_output, sizeof ml_softmax / sizeof ml_softmax[0]);

    for (f = 0; f < 1; f++)
    {
      for (int m = 0; m < CNN_NUM_OUTPUTS_FROZEN_LAYER; m++) // per ogni peso del layer i^th
      {
        /* Algoritmo sul totale */
        // deltaW = cost[m] * (q15_t)prediction[i][m]; //mi trovo deltaW moltiplicando il cost del layer i^th con ogni prediction
        // dW = (uint32_t)((float)learning_rate * deltaW); //mi trovo poi dW

        /* Algorimto solo sul primo channel */
        deltaW = cost[0] * prediction[m]; // need to convert them in smaller number
        dW[m] = (int)(learning_rate * deltaW);
      }
      find_weights(weights, UPDATE, (int)dW);
    }
    printf("%d\n", a++);
    cnn_disable();
  }

  // cnn_disable();

  printf("Classification results:\n");
  for (i = 0; i < CNN_NUM_OUTPUTS; i++)
  {
    digs = (1000 * ml_softmax[i] + 0x4000) >> 15;
    tens = digs % 10;
    digs = digs / 10;
    printf("[%7d] -> Class %d: %d.%d%%\n", ml_data[i], i, digs, tens);
  }

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
