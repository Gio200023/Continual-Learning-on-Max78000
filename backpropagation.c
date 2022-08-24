/********************
 *
 *  Backpropagation
 *
 *********************/

#include "backpropagation.h"
#include "stdint.h"
#include "math.h"
#include "stdio.h"
#include "weights.h"
#include "math.h"

void array_substraction(int *res, q15_t *arr1, int *arr2, int size)
{
    // ml_softmax-true_output
    int i = 0;
    double tmp;
    for (i = 0; i < size; i++)
    {
        tmp = ((double)*(arr1 + i) / (double)0x7fff);
        *(res + i) = (round(tmp)) - *(arr2 + i);
    }
}

int mod2(int val)
{
    return -((val >> 7) & 0b1) * pow(2, 7) + ((val >> 6) & 0b1) * pow(2, 6) + ((val >> 5) & 0b1) * pow(2, 5) + ((val >> 4) & 0b1) * pow(2, 4) + ((val >> 3) & 0b1) * pow(2, 3) + ((val >> 2) & 0b1) * pow(2, 2) + ((val >> 1) & 0b1) * pow(2, 1) + ((val >> 0) & 0b1) * pow(2, 0);
}

void output_layer_3(const int32_t out, uint8_t *final)
{
    const uint32_t *ptr = out;
    uint32_t first[16];
    uint32_t second[16];
    uint32_t third[16];
    uint32_t fourth[16];
    int try = 0, i = 0;

    while (*ptr != 0)
    {
        for (i = 0; i < 16; i++)
        {
            first[i] = mod2((*ptr) >> 0);
            second[i] = mod2((*ptr) >> 8);
            third[i] = mod2((*ptr) >> 16);
            fourth[i] = mod2((*ptr++) >> 24);
        }
        if (try == 0)
        {
            for (int i = 0; i < 64; i++)
            {
                if (i < 16)
                {
                    *(final + i) = first[i];
                }
                else if (i >= 16 && i < 32)
                {
                    *(final + i) = second[i - 16];
                }
                else if (i >= 32 && i < 48)
                {
                    *(final + i) = third[i - 32];
                }
                else if (i >= 48 && i < 64)
                {
                    *(final + i) = fourth[i - 48];
                }
            }
        }
        else if (try == 1)
        {
            for (int i = 64; i < 128; i++)
            {
                if (i < 80)
                {
                    *(final + i) = first[i - 64];
                }
                else if (i >= 80 && i < 96)
                {
                    *(final + i) = second[i - 80];
                }
                else if (i >= 96 && i < 112)
                {
                    *(final + i) = third[i - 96];
                }
                else if (i >= 112 && i < 128)
                {
                    *(final + i) = fourth[i - 112];
                }
            }
        }
        else if (try == 2)
        {
            for (int i = 128; i < CNN_NUM_OUTPUTS_FROZEN_LAYER; i++)
            {
                if (i < 144)
                {
                    *(final + i) = first[i - 128];
                }
                else if (i >= 144 && i < 160)
                {
                    *(final + i) = second[i - 144];
                }
                else if (i >= 160 && i < 176)
                {
                    *(final + i) = third[i - 160];
                }
                else if (i >= 176 && i < CNN_NUM_OUTPUTS_FROZEN_LAYER)
                {
                    *(final + i) = fourth[i - 176];
                }
            }
        }
        try++;
    }
}

uint16_t append[16];
int counter = 0;
static int update_place = 0;
static int spot = 0;

int32_t sottraction(int32_t *hex, int (*dW)[CNN_NUM_OUTPUTS_FROZEN_LAYER], int shift)
{
    int8_t tmp;
    tmp = mod2((*hex >> shift) & 0xff) - (*dW)[update_place++];
    *hex = *hex - ((mod2((*hex >> shift) & 0xff) - tmp) << shift); //forse devi fare in modo che dW diventi tra -128 e 127

    return *hex;
}

// 7 hex weights
void split_7(int32_t *hex1, int32_t *hex2, int32_t *hex3, int32_t *hex4, int32_t *hex5, int32_t *hex6, int32_t *hex7, int8_t (*final)[CNN_NUM_OUTPUTS_FROZEN_LAYER], int choose, int (*dW)[CNN_NUM_OUTPUTS_FROZEN_LAYER])
{
    int i, m = 0;
    if (choose == 0) // FIND
    {
        if (spot == 0)
        {
            append[m++] = mod2(*hex2 >> 8);
            append[m++] = mod2(*hex2 >> 16);
            append[m++] = mod2(*hex2 >> 24);
            append[m++] = mod2(*hex1 >> 0);
            append[m++] = mod2(*hex5 >> 24);
            append[m++] = mod2(*hex4 >> 0);
            append[m++] = mod2(*hex4 >> 8);
            append[m++] = mod2(*hex4 >> 16);
            append[m++] = mod2(*hex4 >> 24);
            append[m++] = mod2(*hex3 >> 0);
            append[m++] = mod2(*hex3 >> 8);
            append[m++] = mod2(*hex3 >> 16);
            append[m++] = mod2(*hex3 >> 24);
            append[m++] = mod2(*hex7 >> 16);
            append[m++] = mod2(*hex7 >> 24);
            append[m++] = mod2(*hex6 >> 0);
        }
        else
        {
            append[m++] = mod2(*hex2 >> 24);
            append[m++] = mod2(*hex1 >> 0);
            append[m++] = mod2(*hex1 >> 8);
            append[m++] = mod2(*hex5 >> 0);
            append[m++] = mod2(*hex5 >> 8);
            append[m++] = mod2(*hex5 >> 16);
            append[m++] = mod2(*hex5 >> 24);
            append[m++] = mod2(*hex4 >> 0);
            append[m++] = mod2(*hex4 >> 8);
            append[m++] = mod2(*hex4 >> 16);
            append[m++] = mod2(*hex4 >> 24);
            append[m++] = mod2(*hex3 >> 0);
            append[m++] = mod2(*hex7 >> 24);
            append[m++] = mod2(*hex6 >> 0);
            append[m++] = mod2(*hex6 >> 8);
            append[m++] = mod2(*hex6 >> 16);
        }

        for (int j = 0; j < 16; j++)
        {
            (*final)[j + counter] = (int8_t)append[j];
        }
    }
    else if (choose == 1) // UPDATE
    {
        if (spot == 0)
        {
            *hex2 = sottraction(hex2, dW, 8);
            *hex2 = sottraction(hex2, dW, 16);
            *hex2 = sottraction(hex2, dW, 24);
            *hex1 = sottraction(hex1, dW, 0);
            *hex5 = sottraction(hex5, dW, 24);
            *hex4 = sottraction(hex4, dW, 0);
            *hex4 = sottraction(hex4, dW, 8);
            *hex4 = sottraction(hex4, dW, 16);
            *hex4 = sottraction(hex4, dW, 24);
            *hex3 = sottraction(hex3, dW, 0);
            *hex3 = sottraction(hex3, dW, 8);
            *hex3 = sottraction(hex3, dW, 16);
            *hex3 = sottraction(hex3, dW, 24);
            *hex7 = sottraction(hex7, dW, 16);
            *hex7 = sottraction(hex7, dW, 24);
            *hex6 = sottraction(hex6, dW, 0);
        }
        else
        {
            *hex2 = sottraction(hex2, dW, 24);
            *hex1 = sottraction(hex1, dW, 0);
            *hex1 = sottraction(hex1, dW, 8);
            *hex5 = sottraction(hex5, dW, 0);
            *hex5 = sottraction(hex5, dW, 8);
            *hex5 = sottraction(hex5, dW, 16);
            *hex5 = sottraction(hex5, dW, 24);
            *hex4 = sottraction(hex4, dW, 0);
            *hex4 = sottraction(hex4, dW, 8);
            *hex4 = sottraction(hex4, dW, 16);
            *hex4 = sottraction(hex4, dW, 24);
            *hex3 = sottraction(hex3, dW, 0);
            *hex7 = sottraction(hex7, dW, 24);
            *hex6 = sottraction(hex6, dW, 0);
            *hex6 = sottraction(hex6, dW, 8);
            *hex6 = sottraction(hex6, dW, 16);
        }
    }
}

// 6 hex weights
void split_6(int32_t *hex1, int32_t *hex2, int32_t *hex3, int32_t *hex4, int32_t *hex5, int32_t *hex6, int8_t (*final)[CNN_NUM_OUTPUTS_FROZEN_LAYER], int choose, int (*dW)[CNN_NUM_OUTPUTS_FROZEN_LAYER])
{
    int i, m = 0;
    if (choose == 0) // find
    {
        if (spot == 0)
        {
            append[m++] = mod2(*hex1 >> 8);
            append[m++] = mod2(*hex1 >> 16);
            append[m++] = mod2(*hex4 >> 8);
            append[m++] = mod2(*hex4 >> 16);
            append[m++] = mod2(*hex4 >> 24);
            append[m++] = mod2(*hex3 >> 0);
            append[m++] = mod2(*hex3 >> 8);
            append[m++] = mod2(*hex3 >> 16);
            append[m++] = mod2(*hex3 >> 24);
            append[m++] = mod2(*hex2 >> 0);
            append[m++] = mod2(*hex2 >> 8);
            append[m++] = mod2(*hex6 >> 0);
            append[m++] = mod2(*hex6 >> 8);
            append[m++] = mod2(*hex6 >> 16);
            append[m++] = mod2(*hex6 >> 24);
            append[m++] = mod2(*hex5 >> 0);
        }
        else if (spot == 1)
        {
            append[m++] = mod2(*hex2 >> 8);
            append[m++] = mod2(*hex2 >> 16);
            append[m++] = mod2(*hex2 >> 24);
            append[m++] = mod2(*hex1 >> 0);
            append[m++] = mod2(*hex1 >> 8);
            append[m++] = mod2(*hex1 >> 16);
            append[m++] = mod2(*hex5 >> 8);
            append[m++] = mod2(*hex5 >> 16);
            append[m++] = mod2(*hex5 >> 24);
            append[m++] = mod2(*hex4 >> 0);
            append[m++] = mod2(*hex4 >> 8);
            append[m++] = mod2(*hex4 >> 16);
            append[m++] = mod2(*hex4 >> 24);
            append[m++] = mod2(*hex3 >> 0);
            append[m++] = mod2(*hex3 >> 8);
            append[m++] = mod2(*hex6 >> 0);
        }
        else if (spot == 2)
        {
            append[m++] = mod2(*hex3 >> 8);
            append[m++] = mod2(*hex3 >> 16);
            append[m++] = mod2(*hex3 >> 24);
            append[m++] = mod2(*hex2 >> 0);
            append[m++] = mod2(*hex2 >> 8);
            append[m++] = mod2(*hex2 >> 16);
            append[m++] = mod2(*hex2 >> 24);
            append[m++] = mod2(*hex1 >> 0);
            append[m++] = mod2(*hex6 >> 24);
            append[m++] = mod2(*hex5 >> 0);
            append[m++] = mod2(*hex5 >> 8);
            append[m++] = mod2(*hex5 >> 16);
            append[m++] = mod2(*hex5 >> 24);
            append[m++] = mod2(*hex4 >> 0);
            append[m++] = mod2(*hex4 >> 8);
            append[m++] = mod2(*hex4 >> 16);
        }
        else if (spot == 3)
        {
            append[m++] = mod2(*hex1 >> 24);
            append[m++] = mod2(*hex4 >> 16);
            append[m++] = mod2(*hex4 >> 24);
            append[m++] = mod2(*hex3 >> 0);
            append[m++] = mod2(*hex3 >> 8);
            append[m++] = mod2(*hex3 >> 16);
            append[m++] = mod2(*hex3 >> 24);
            append[m++] = mod2(*hex2 >> 0);
            append[m++] = mod2(*hex2 >> 8);
            append[m++] = mod2(*hex2 >> 16);
            append[m++] = mod2(*hex6 >> 8);
            append[m++] = mod2(*hex6 >> 16);
            append[m++] = mod2(*hex6 >> 24);
            append[m++] = mod2(*hex5 >> 0);
            append[m++] = mod2(*hex5 >> 8);
            append[m++] = mod2(*hex5 >> 16);
        }
        else if (spot == 4)
        {
            append[m++] = mod2(*hex2 >> 24);
            append[m++] = mod2(*hex1 >> 0);
            append[m++] = mod2(*hex1 >> 8);
            append[m++] = mod2(*hex1 >> 16);
            append[m++] = mod2(*hex1 >> 24);
            append[m++] = mod2(*hex5 >> 16);
            append[m++] = mod2(*hex5 >> 24);
            append[m++] = mod2(*hex4 >> 0);
            append[m++] = mod2(*hex4 >> 8);
            append[m++] = mod2(*hex4 >> 16);
            append[m++] = mod2(*hex4 >> 24);
            append[m++] = mod2(*hex3 >> 0);
            append[m++] = mod2(*hex3 >> 8);
            append[m++] = mod2(*hex3 >> 16);
            append[m++] = mod2(*hex6 >> 8);
            append[m++] = mod2(*hex6 >> 16);
        }
        for (int j = 0; j < 16; j++)
        {
            (*final)[j + counter] = (int8_t)append[j];
        }
    }
    else // update
    {
        if (spot == 0)
        {
            *hex1 = sottraction(hex1, dW, 8);
            *hex1 = sottraction(hex1, dW, 16);
            *hex4 = sottraction(hex4, dW, 8);
            *hex4 = sottraction(hex4, dW, 16);
            *hex4 = sottraction(hex4, dW, 24);
            *hex3 = sottraction(hex3, dW, 0);
            *hex3 = sottraction(hex3, dW, 8);
            *hex3 = sottraction(hex3, dW, 16);
            *hex3 = sottraction(hex3, dW, 24);
            *hex2 = sottraction(hex2, dW, 0);
            *hex2 = sottraction(hex2, dW, 8);
            *hex6 = sottraction(hex6, dW, 0);
            *hex6 = sottraction(hex6, dW, 8);
            *hex6 = sottraction(hex6, dW, 16);
            *hex6 = sottraction(hex6, dW, 24);
            *hex5 = sottraction(hex5, dW, 0);
        }
        else if (spot == 1)
        {
            *hex2 = sottraction(hex2, dW, 8);
            *hex2 = sottraction(hex2, dW, 16);
            *hex2 = sottraction(hex2, dW, 24);
            *hex1 = sottraction(hex1, dW, 0);
            *hex1 = sottraction(hex1, dW, 8);
            *hex1 = sottraction(hex1, dW, 16);
            *hex5 = sottraction(hex5, dW, 8);
            *hex5 = sottraction(hex5, dW, 16);
            *hex5 = sottraction(hex5, dW, 24);
            *hex4 = sottraction(hex4, dW, 0);
            *hex4 = sottraction(hex4, dW, 8);
            *hex4 = sottraction(hex4, dW, 16);
            *hex4 = sottraction(hex4, dW, 24);
            *hex3 = sottraction(hex3, dW, 0);
            *hex3 = sottraction(hex3, dW, 8);
            *hex6 = sottraction(hex6, dW, 0);
        }
        else if (spot == 2)
        {
            *hex3 = sottraction(hex3, dW, 8);
            *hex3 = sottraction(hex3, dW, 16);
            *hex3 = sottraction(hex3, dW, 24);
            *hex2 = sottraction(hex2, dW, 0);
            *hex2 = sottraction(hex2, dW, 8);
            *hex2 = sottraction(hex2, dW, 16);
            *hex2 = sottraction(hex2, dW, 24);
            *hex1 = sottraction(hex1, dW, 0);
            *hex6 = sottraction(hex6, dW, 24);
            *hex5 = sottraction(hex5, dW, 0);
            *hex5 = sottraction(hex5, dW, 8);
            *hex5 = sottraction(hex5, dW, 16);
            *hex5 = sottraction(hex5, dW, 24);
            *hex4 = sottraction(hex4, dW, 0);
            *hex4 = sottraction(hex4, dW, 8);
            *hex4 = sottraction(hex4, dW, 16);
        }
        else if (spot == 3)
        {
            *hex1 = sottraction(hex1, dW, 24);
            *hex4 = sottraction(hex4, dW, 16);
            *hex4 = sottraction(hex4, dW, 24);
            *hex3 = sottraction(hex3, dW, 0);
            *hex3 = sottraction(hex3, dW, 8);
            *hex3 = sottraction(hex3, dW, 16);
            *hex3 = sottraction(hex3, dW, 24);
            *hex2 = sottraction(hex2, dW, 0);
            *hex2 = sottraction(hex2, dW, 8);
            *hex2 = sottraction(hex2, dW, 16);
            *hex6 = sottraction(hex6, dW, 8);
            *hex6 = sottraction(hex6, dW, 16);
            *hex6 = sottraction(hex6, dW, 24);
            *hex5 = sottraction(hex5, dW, 0);
            *hex5 = sottraction(hex5, dW, 8);
            *hex5 = sottraction(hex5, dW, 16);
        }
        else if (spot == 4)
        {
            *hex2 = sottraction(hex2, dW, 24);
            *hex1 = sottraction(hex1, dW, 0);
            *hex1 = sottraction(hex1, dW, 8);
            *hex1 = sottraction(hex1, dW, 16);
            *hex1 = sottraction(hex1, dW, 24);
            *hex5 = sottraction(hex5, dW, 16);
            *hex5 = sottraction(hex5, dW, 24);
            *hex4 = sottraction(hex4, dW, 0);
            *hex4 = sottraction(hex4, dW, 8);
            *hex4 = sottraction(hex4, dW, 16);
            *hex4 = sottraction(hex4, dW, 24);
            *hex3 = sottraction(hex3, dW, 0);
            *hex3 = sottraction(hex3, dW, 8);
            *hex3 = sottraction(hex3, dW, 16);
            *hex6 = sottraction(hex6, dW, 8);
            *hex6 = sottraction(hex6, dW, 16);
        }
    }
}

// 5 hex weights
void split_5(int32_t *hex1, int32_t *hex2, int32_t *hex3, int32_t *hex4, int32_t *hex5, int8_t (*final)[CNN_NUM_OUTPUTS_FROZEN_LAYER], int choose, int (*dW)[CNN_NUM_OUTPUTS_FROZEN_LAYER])
{
    int i, m = 0;

    if (choose == 0) // FIND
    {
        append[m++] = mod2(*hex3 >> 24);
        append[m++] = mod2(*hex2 >> 0);
        append[m++] = mod2(*hex2 >> 8);
        append[m++] = mod2(*hex2 >> 16);
        append[m++] = mod2(*hex2 >> 24);
        append[m++] = mod2(*hex1 >> 0);
        append[m++] = mod2(*hex1 >> 8);
        if (spot == 0)
        {
            append[m++] = mod2(*hex1 >> 16);

            append[m++] = mod2(*hex1 >> 24);
        }
        else
        {
            append[m++] = mod2(*hex5 >> 0);

            append[m++] = mod2(*hex5 >> 8);
        }
        append[m++] = mod2(*hex5 >> 16);
        append[m++] = mod2(*hex5 >> 24);
        append[m++] = mod2(*hex4 >> 0);
        append[m++] = mod2(*hex4 >> 8);
        append[m++] = mod2(*hex4 >> 16);
        append[m++] = mod2(*hex4 >> 24);
        append[m++] = mod2(*hex3 >> 0);

        for (int j = 0; j < 16; j++)
        {
            (*final)[j + counter] = (int8_t)append[j];
        }
    }
    else if (choose == 1) // UPDATE
    {
        *hex3 = sottraction(hex3, dW, 24);
        *hex2 = sottraction(hex2, dW, 0);
        *hex2 = sottraction(hex2, dW, 8);
        *hex2 = sottraction(hex2, dW, 16);
        *hex2 = sottraction(hex2, dW, 24);
        *hex1 = sottraction(hex1, dW, 0);
        *hex1 = sottraction(hex1, dW, 8);
        if (spot == 0)
        {
            *hex1 = sottraction(hex1, dW, 16);

            *hex1 = sottraction(hex1, dW, 24);
        }
        else
        {
            *hex5 = sottraction(hex5, dW, 0);

            *hex5 = sottraction(hex5, dW, 8);
        }
        *hex5 = sottraction(hex5, dW, 16);
        *hex5 = sottraction(hex5, dW, 24);
        *hex4 = sottraction(hex4, dW, 0);
        *hex4 = sottraction(hex4, dW, 8);
        *hex4 = sottraction(hex4, dW, 16);
        *hex4 = sottraction(hex4, dW, 24);
        *hex3 = sottraction(hex3, dW, 0);
    }
}

void find_weights(int8_t (*weights)[CNN_NUM_OUTPUTS_FROZEN_LAYER], int choose, int (*dW)[CNN_NUM_OUTPUTS_FROZEN_LAYER])
{
    // printf("peso intero = %x\n",kernels_miei[139]);
    // printf("sono qui\n");
    int i, offset = 288, place = 0;
    if (update_place == 192)
    {
        update_place = 0;
    }
    if (counter == 192)
    {
        counter = 0;
    }

    for (i = 0; i < 17930; i++)
    {
        if ((kernels_miei[i] >> 16) == 0x0 && (kernels_miei[i - 1] >> 24) == 0x50 && (kernels_miei[i] == 41 || kernels_miei[i] == 329))
        {
            if (kernels_miei[i] == 41)
            {
                split_5((int32_t)(kernels_miei + i + 1), (int32_t)(kernels_miei + i + 2), (int32_t)(kernels_miei + i + 3), (int32_t)(kernels_miei + i + 4), (int32_t)(kernels_miei + i + 5), (weights + place), choose, dW + place++);
                split_6((int32_t)(kernels_miei + i + 3), (int32_t)(kernels_miei + i + 5), (int32_t)(kernels_miei + i + 6), (int32_t)(kernels_miei + i + 7), (int32_t)(kernels_miei + i + 8), (int32_t)(kernels_miei + i + 9), weights + place, choose, dW + place++);
                split_7((int32_t)(kernels_miei + i + 7), (int32_t)(kernels_miei + i + 8), (int32_t)(kernels_miei + i + 10), (int32_t)(kernels_miei + i + 11), (int32_t)(kernels_miei + i + 12), (int32_t)(kernels_miei + i + 13), (int32_t)(kernels_miei + i + 14), weights + place, choose, dW + place++);
                spot++; // 1
                split_6((int32_t)(kernels_miei + i + 12), (int32_t)(kernels_miei + i + 13), (int32_t)(kernels_miei + i + 14), (int32_t)(kernels_miei + i + 15), (int32_t)(kernels_miei + i + 16), (int32_t)(kernels_miei + i + 18), weights + place, choose, dW + place++);
                spot++; // 2
                split_6((int32_t)(kernels_miei + i + 16), (int32_t)(kernels_miei + i + 17), (int32_t)(kernels_miei + i + 18), (int32_t)(kernels_miei + i + 19), (int32_t)(kernels_miei + i + 20), (int32_t)(kernels_miei + i + 21), weights + place, choose, dW + place++);
                spot++; // 3
                split_6((int32_t)(kernels_miei + i + 19), (int32_t)(kernels_miei + i + 21), (int32_t)(kernels_miei + i + 22), (int32_t)(kernels_miei + i + 23), (int32_t)(kernels_miei + i + 24), (int32_t)(kernels_miei + i + 25), weights + place, choose, dW + place++);
                spot = 1;
                split_7((int32_t)(kernels_miei + i + 23), (int32_t)(kernels_miei + i + 24), (int32_t)(kernels_miei + i + 25), (int32_t)(kernels_miei + i + 26), (int32_t)(kernels_miei + i + 27), (int32_t)(kernels_miei + i + 29), (int32_t)(kernels_miei + i + 30), weights + place, choose, dW + place++);
                spot = 4; // 4
                split_6((int32_t)(kernels_miei + i + 28), (int32_t)(kernels_miei + i + 29), (int32_t)(kernels_miei + i + 30), (int32_t)(kernels_miei + i + 31), (int32_t)(kernels_miei + i + 32), (int32_t)(kernels_miei + i + 34), weights + place, choose, dW + place++);
                spot = 1;
                split_5((int32_t)(kernels_miei + i + 32), (int32_t)(kernels_miei + i + 33), (int32_t)(kernels_miei + i + 34), (int32_t)(kernels_miei + i + 35), (int32_t)(kernels_miei + i + 36), weights + place, choose, dW + place++);
                spot = 0;
                split_5((int32_t)(kernels_miei + i + 37), (int32_t)(kernels_miei + i + 38), (int32_t)(kernels_miei + i + 39), (int32_t)(kernels_miei + i + 40), (int32_t)(kernels_miei + i + 41), weights + place, choose, dW + place); // update weights[place++][counter] and dw[place++][counter]
                place = 0;
                counter += 16;
                update_place = 0;
                i += 39;
            }
            else if (kernels_miei[i] == 329)
            {
                split_5((int32_t)(kernels_miei + i + offset + 1), (int32_t)(kernels_miei + i + offset + 2), (int32_t)(kernels_miei + i + offset + 3), (int32_t)(kernels_miei + i + offset + 4), (int32_t)(kernels_miei + i + offset + 5), weights + place, choose, dW + place++);
                split_6((int32_t)(kernels_miei + i + offset + 3), (int32_t)(kernels_miei + i + offset + 5), (int32_t)(kernels_miei + i + offset + 6), (int32_t)(kernels_miei + i + offset + 7), (int32_t)(kernels_miei + i + offset + 8), (int32_t)(kernels_miei + i + offset + 9), weights + place, choose, dW + place++);
                split_7((int32_t)(kernels_miei + i + offset + 7), (int32_t)(kernels_miei + i + offset + 8), (int32_t)(kernels_miei + i + offset + 10), (int32_t)(kernels_miei + i + offset + 11), (int32_t)(kernels_miei + i + offset + 12), (int32_t)(kernels_miei + i + offset + 13), (int32_t)(kernels_miei + i + offset + 14), weights + place, choose, dW + place++);
                spot++; // 1
                split_6((int32_t)(kernels_miei + i + offset + 12), (int32_t)(kernels_miei + i + offset + 13), (int32_t)(kernels_miei + i + offset + 14), (int32_t)(kernels_miei + i + offset + 15), (int32_t)(kernels_miei + i + offset + 16), (int32_t)(kernels_miei + i + offset + 18), weights + place, choose, dW + place++);
                spot++; // 2
                split_6((int32_t)(kernels_miei + i + offset + 16), (int32_t)(kernels_miei + i + offset + 17), (int32_t)(kernels_miei + i + offset + 18), (int32_t)(kernels_miei + i + offset + 19), (int32_t)(kernels_miei + i + offset + 20), (int32_t)(kernels_miei + i + offset + 21), weights + place, choose, dW + place++);
                spot++; // 3
                split_6((int32_t)(kernels_miei + i + offset + 19), (int32_t)(kernels_miei + i + offset + 21), (int32_t)(kernels_miei + i + offset + 22), (int32_t)(kernels_miei + i + offset + 23), (int32_t)(kernels_miei + i + offset + 24), (int32_t)(kernels_miei + i + offset + 25), weights + place, choose, dW + place++);
                spot = 1;
                split_7((int32_t)(kernels_miei + i + offset + 23), (int32_t)(kernels_miei + i + offset + 24), (int32_t)(kernels_miei + i + offset + 25), (int32_t)(kernels_miei + i + offset + 26), (int32_t)(kernels_miei + i + offset + 27), (int32_t)(kernels_miei + i + offset + 29), (int32_t)(kernels_miei + i + offset + 30), weights + place, choose, dW + place++);
                spot = 4; // 4
                split_6((int32_t)(kernels_miei + i + offset + 28), (int32_t)(kernels_miei + i + offset + 29), (int32_t)(kernels_miei + i + offset + 30), (int32_t)(kernels_miei + i + offset + 31), (int32_t)(kernels_miei + i + offset + 32), (int32_t)(kernels_miei + i + offset + 34), weights + place, choose, dW + place++);
                spot = 1;
                split_5((int32_t)(kernels_miei + i + offset + 32), (int32_t)(kernels_miei + i + offset + 33), (int32_t)(kernels_miei + i + offset + 34), (int32_t)(kernels_miei + i + offset + 35), (int32_t)(kernels_miei + i + offset + 36), weights + place, choose, dW + place++);
                spot = 0;
                split_5((int32_t)(kernels_miei + i + offset + 37), (int32_t)(kernels_miei + i + offset + 38), (int32_t)(kernels_miei + i + offset + 39), (int32_t)(kernels_miei + i + offset + 40), (int32_t)(kernels_miei + i + offset + 41), weights + place, choose, dW + place); // update weights[place++][counter] and dw[place++][counter]
                place = 0;
                counter += 16;
                update_place = 0;
                i += 280;
            }
        }
    }
}

void bias_update(q15_t *cost, float learning_rate)
{
    int tmp;
    for (int i = 0; i < 10; i++)
    {
        tmp = learning_rate * (*(cost + i));
        bias[i] -= tmp;
    }
}
