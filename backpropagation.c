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

void array_substraction(q15_t *res, q15_t *arr1, q15_t *arr2, int size)
{

    q15_t tmp[size];
    int i = 0;
    for (i = 0; i < size; i++)
    {
        tmp[i] = arr1[i] - arr2[i];
    }
    for (i = 0; i < size; i++)
    {
        if (tmp[i] <= 0)
            res[i] = 0;
        else
            res[i] = 1;
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

void output_layer_3(const uint32_t out, uint16_t *final)
{
    const uint32_t *ptr = out;
    int count = 0;
    uint32_t first[16];
    uint32_t second[16];
    uint32_t third[16];
    uint32_t fourth[16];
    int step = 0;
    int try = 0;

    while (*ptr != 0)
    {
        count = 0;

        for (int i = 0; i < 16; i++)
        {
            first[count] = mod2((*(ptr)) >> 0);
            step += 1;
            second[count] = mod2((*(ptr)) >> 8);
            step += 1;
            third[count] = mod2((*(ptr)) >> 16);
            step += 1;
            fourth[count] = mod2((*(ptr)) >> 24);
            step += 1;
            count++;
            *ptr++;
        }

        if (try == 0)
        {
            for (int i = 0; i < 64; i++)
            {
                if (i < 16)
                {
                    final[i] = first[i];
                }
                else if (i >= 16 && i < 32)
                {
                    final[i] = second[i - 16];
                }
                else if (i >= 32 && i < 48)
                {
                    final[i] = third[i - 32];
                }
                else if (i >= 48 && i < 64)
                {
                    final[i] = fourth[i - 48];
                }
            }
        }

        if (try == 1)
        {
            for (int i = 64; i < 128; i++)
            {
                if (i < 80)
                {
                    final[i] = first[i - 64];
                }
                else if (i >= 80 && i < 96)
                {
                    final[i] = second[i - 80];
                }
                else if (i >= 96 && i < 112)
                {
                    final[i] = third[i - 96];
                }
                else if (i >= 112 && i < 128)
                {
                    final[i] = fourth[i - 112];
                }
            }
        }

        if (try == 2)
        {
            for (int i = 128; i < CNN_NUM_OUTPUTS_FROZEN_LAYER; i++)
            {
                if (i < 144)
                {
                    final[i] = first[i - 128];
                }
                else if (i >= 144 && i < 160)
                {
                    final[i] = second[i - 144];
                }
                else if (i >= 160 && i < 176)
                {
                    final[i] = third[i - 160];
                }
                else if (i >= 176 && i < CNN_NUM_OUTPUTS_FROZEN_LAYER)
                {
                    final[i] = fourth[i - 176];
                }
            }
        }

        try++;
    }
}

uint16_t append[16];
int contatore = 0;
int counter = 0;

void split(int hex1, int hex2, int hex3, int hex4, int hex5, uint16_t *final)
{
    int i, m;
    for (i = 0; i < 2; i++)
    {
        switch (i)
        {
        case 0:
            contatore = 9;
        case 1:
            contatore = 7;
        }

        for (m = 0; m < contatore; m++)
        {
            if (i == 0)
            {
                if (m == 0)
                {
                    append[m] = mod2(hex3 >> 24);
                }
                else if (m == 1)
                {
                    append[m] = mod2(hex2 >> 0);
                    m++;
                    append[m] = mod2(hex2 >> 8);
                    m++;
                    append[m] = mod2(hex2 >> 16);
                    m++;
                    append[m] = mod2(hex2 >> 24);
                }
                else if (m == 5)
                {
                    append[m] = mod2(hex1 >> 0);
                    m++;
                    append[m] = mod2(hex1 >> 8);
                    m++;
                    append[m] = mod2(hex1 >> 16);
                    m++;
                    append[m] = mod2(hex1 >> 24);
                }
            }
            if (i == 1)
            {
                if (m == 0)
                {
                    append[m + 9] = mod2(hex5 >> 16);
                    m++;
                    append[m + 9] = mod2(hex5 >> 24);
                }
                else if (m == 2)
                {
                    append[m + 9] = mod2(hex4 >> 0);
                    m++;
                    append[m + 9] = mod2(hex4 >> 8);
                    m++;
                    append[m + 9] = mod2(hex4 >> 16);
                    m++;
                    append[m + 9] = mod2(hex4 >> 24);
                }
                else if (m == 6)
                {
                    append[m + 9] = mod2(hex3 >> 0);
                }
            }
        }
    }

    for (int j = 0; j < 16; j++)
    {
        final[j + counter] = append[j];
    }

    counter += 16;
}

static const uint32_t pesi[] = WEIGHTS;

void find_weights(uint16_t *weights)
{
    int i, m;
    volatile uint32_t *addr;

    for (i = 0; i < (sizeof(pesi) / sizeof(pesi[0])); i++)
    {
        if ((pesi[i] >> 16) == 0x0 && (pesi[i - 1] >> 24) == 0x50 && (pesi[i] == 41 || pesi[i] == 329))
        {
            if (pesi[i] == 41)
            {
                addr = (volatile uint32_t *)pesi[i - 1];
                split(*(addr + 2), *(addr + 3), *(addr + 4), *(addr + 5), *(addr + 6), weights);
                printf("%08x, %08x,%08x,%08x,%08x\n", addr + 2, addr + 3, addr + 4, addr + 5, addr + 6);
            }
            if (pesi[i] == 329)
            {
                for (m = 0; m < 329; m++)
                {
                    addr = (volatile uint32_t *)pesi[i - 1];
                    if (m >= 288 && m < 293)
                    {
                        split(*(addr + m + 2), *(addr + m + 3), *(addr + m + 4), *(addr + m + 5), *(addr + m + 6), weights);
                        printf("%08x, %08x,%08x,%08x,%08x\n", addr + m + 2, addr + m + 3, addr + m + 4, addr + m + 5, addr + m + 6);
                        break;
                    }
                }
            }
        }
    }
}

void trova_pesi(uint32_t *out_buf)
{
    uint32_t len;
    volatile uint32_t *addr;
    const uint32_t *ptr = pesi;
    //(volatile uint32_t *) cast --> espliciti il tipo dicendo di andare a prenderlo in memoria e no cache
    while ((addr = (volatile uint32_t *)*ptr++) != 0)
    {
        printf("inizio = %0x\n", addr);
        len = *ptr++;
        printf("%08x\n", len);
        printf("%08x\n",* (volatile uint32_t *) 0x50180200);
        for (int m = 0; m < 5; m++)
        {
            printf("location= %08x, Value= %08x\n", addr, *addr);
            addr++; // questo incremento devo farlo dopo  
        }

    }
}