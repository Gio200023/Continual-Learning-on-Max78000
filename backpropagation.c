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

void array_substraction(q15_t *res, q15_t *arr1, q15_t *arr2, int size)
{
    // ml_softmax-true_output
    int i = 0;
    for (i = 0; i < size; i++)
    {
        *(res + i) = round(((*(arr1 + i) - *(arr2 + i)) / 0x7fff));
        printf("tmp[%2d]: ml_soft[%4d]-true[%5d]= %d\n", i, arr1[i], arr2[i], res[i]);
    }
}

void delta_multiplication(q15_t *res, q15_t *cost, int32_t out_value, int size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = cost[i] * out_value;
    }
}

void dW_multiplication(q15_t *res, q15_t *delta, uint32_t l_rate, int size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = delta[i] * l_rate;
    }
}

int mod2(int val)
{
    return -((val >> 7) & 0b1) * pow(2, 7) + ((val >> 6) & 0b1) * pow(2, 6) + ((val >> 5) & 0b1) * pow(2, 5) + ((val >> 4) & 0b1) * pow(2, 4) + ((val >> 3) & 0b1) * pow(2, 3) + ((val >> 2) & 0b1) * pow(2, 2) + ((val >> 1) & 0b1) * pow(2, 1) + ((val >> 0) & 0b1) * pow(2, 0);
}

void output_layer_3(const int32_t out, uint8_t *final)
{
    const uint32_t *ptr = out;
    int count = 0;
    uint32_t first[16];
    uint32_t second[16];
    uint32_t third[16];
    uint32_t fourth[16];
    int try = 0;

    while (*ptr != 0)
    {
        count = 0;

        for (int i = 0; i < 16; i++)
        {
            first[count] = mod2((*(ptr)) >> 0);

            second[count] = mod2((*(ptr)) >> 8);

            third[count] = mod2((*(ptr)) >> 16);

            fourth[count] = mod2((*(ptr)) >> 24);
            count++;
            *ptr++;
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

        if (try == 1)
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

        if (try == 2)
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
int contatore = 0;
int counter = 0;
static int update_place = 0;

uint32_t sottraction(int32_t *hex, int *dW, int shift)
{
    int8_t tmp;
    if (update_place == 192)
    {
        update_place = 0;
    }
    tmp = mod2((*hex >> shift) & 0xff) - *(dW + update_place++);
    *hex = *hex - ((((*hex >> shift) & 0xff) - tmp) << shift);

    return *hex;
}

void split(int32_t *hex1, int32_t *hex2, int32_t *hex3, int32_t *hex4, int32_t *hex5, int8_t *final, int choose, int *dW)
{
    int i, m;
    for (i = 0; i < 2; i++)
    {
        i ? (contatore = 7) : (contatore = 9);

        for (m = 0; m < contatore; m++)
        {
            if (i == 0)
            {
                if (m == 0)
                {
                    choose ? (*hex3 = sottraction(hex3, dW, 24)) : (append[m] = mod2(*hex3 >> 24));
                }
                else if (m == 1)
                {
                    choose ? (*hex2 = sottraction(hex2, dW, 0)) : (append[m] = mod2(*hex2 >> 0));
                    m++;
                    choose ? (*hex2 = sottraction(hex2, dW, 8)) : (append[m] = mod2(*hex2 >> 8));
                    m++;
                    choose ? (*hex2 = sottraction(hex2, dW, 16)) : (append[m] = mod2(*hex2 >> 16));
                    m++;
                    choose ? (*hex2 = sottraction(hex2, dW, 24)) : (append[m] = mod2(*hex2 >> 24));
                }
                else if (m == 5)
                {
                    choose ? (*hex1 = sottraction(hex1, dW, 0)) : (append[m] = mod2(*hex1 >> 0));
                    m++;
                    choose ? (*hex1 = sottraction(hex1, dW, 8)) : (append[m] = mod2(*hex1 >> 8));
                    m++;
                    choose ? (*hex1 = sottraction(hex1, dW, 16)) : (append[m] = mod2(*hex1 >> 16));
                    m++;
                    choose ? (*hex1 = sottraction(hex1, dW, 24)) : (append[m] = mod2(*hex1 >> 24));
                }
            }
            if (i == 1)
            {
                if (m == 0)
                {
                    choose ? (*hex5 = sottraction(hex5, dW, 16)) : (append[m + 9] = mod2(*hex5 >> 16));
                    m++;
                    choose ? (*hex5 = sottraction(hex5, dW, 24)) : (append[m + 9] = mod2(*hex5 >> 24));
                }
                else if (m == 2)
                {
                    choose ? (*hex4 = sottraction(hex4, dW, 0)) : (append[m + 9] = mod2(*hex4 >> 0));
                    m++;
                    choose ? (*hex4 = sottraction(hex4, dW, 8)) : (append[m + 9] = mod2(*hex4 >> 8));
                    m++;
                    choose ? (*hex4 = sottraction(hex4, dW, 16)) : (append[m + 9] = mod2(*hex4 >> 16));
                    m++;
                    choose ? (*hex4 = sottraction(hex4, dW, 24)) : (append[m + 9] = mod2(*hex4 >> 24));
                }
                else if (m == 6)
                {
                    choose ? (*hex3 = sottraction(hex3, dW, 0)) : (append[m + 9] = mod2(*hex3 >> 0));
                }
            }
        }
    }

    if (choose == 0)
    {
        for (int j = 0; j < 16; j++)
        {
            *(final + j + counter) = append[j];
        }
    }

    counter += 16;
}

void find_weights(int8_t *weights, int choose, int *dW)
{
    int i, m = 0;

    for (i = 0; i < 17930; i++)
    {
        if ((kernels_miei[i] >> 16) == 0x0 && (kernels_miei[i - 1] >> 24) == 0x50 && (kernels_miei[i] == 41 || kernels_miei[i] == 329))
        {
            if (kernels_miei[i] == 41)
            {
                if (choose == 0)
                {
                    split((int32_t)(kernels_miei + i + 1), (int32_t)(kernels_miei + i + 2), (int32_t)(kernels_miei + i + 3), (int32_t)(kernels_miei + i + 4), (int32_t)(kernels_miei + i + 5), weights, choose, dW);
                }
                else if (choose == 1)
                {
                    printf("\n");
                    printf("PRIMA = %x , %x , %x , %x , %x\n",(int32_t)*(kernels_miei + i + 1), (int32_t)*(kernels_miei + i + 2), (int32_t)*(kernels_miei + i + 3), (int32_t)*(kernels_miei + i + 4), (int32_t)*(kernels_miei + i + 5));
                    split((int32_t)(kernels_miei + i + 1), (int32_t)(kernels_miei + i + 2), (int32_t)(kernels_miei + i + 3), (int32_t)(kernels_miei + i + 4), (int32_t)(kernels_miei + i + 5), weights, choose, dW);
                    printf("DOPO = %x , %x , %x , %x , %x\n\n",(int32_t)*(kernels_miei + i + 1), (int32_t)*(kernels_miei + i + 2), (int32_t)*(kernels_miei + i + 3), (int32_t)*(kernels_miei + i + 4), (int32_t)*(kernels_miei + i + 5));
                }
            }
            if (kernels_miei[i] == 329)
            {
                for (m = 0; m < 329; m++)
                {
                    if (m >= 288 && m < 293)
                    {
                        if (choose == 0)
                        {
                            split((int32_t)(kernels_miei + m + i + 1), (int32_t)(kernels_miei + m + i + 2), (int32_t)(kernels_miei + m + i + 3), (int32_t)(kernels_miei + m + i + 4), (int32_t)(kernels_miei + m + i + 5), weights, choose, dW);
                            break;
                        }
                        else if (choose == 1)
                        {
                            split((int32_t)(kernels_miei + m + i + 1), (int32_t)(kernels_miei + m + i + 2), (int32_t)(kernels_miei + m + i + 3), (int32_t)(kernels_miei + m + i + 4), (int32_t)(kernels_miei + m + i + 5), weights, choose, dW);
                            break;
                        }
                    }
                }
            }
        }
    }
}
