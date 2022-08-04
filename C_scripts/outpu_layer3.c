#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "unistd.h"
#include "weights.h"

#define SAMPLE_OUTPUT_LAYER_0                                                                               \
    {                                                                                                       \
        0x50400000, 0xffffffff, 0x00000010, 0x007f0b7f, 0x0f7f087f, 0x037f197f, 0x246e3a44, 0x00715e7f,     \
            0x006b697f, 0x0056347f, 0x3d3b627f, 0x0000633e, 0x00007f18, 0x0000260b, 0x00222b00, 0x00003c00, \
            0x00007f00, 0x00002400, 0x001d0000, 0x50408000, 0xffffffff, 0x00000010, 0x7f7f3400, 0x7f7f0f00, \
            0x5d6d2100, 0x4200392a, 0x7f7f0011, 0x7f7f0000, 0x697f1600, 0x0a000000, 0x7f59003b, 0x5140095b, \
            0x002e0000, 0x00340000, 0x38382e31, 0x0049022d, 0x0c7f0000, 0x33731800, 0x50410000, 0xffffffff, \
            0x00000010, 0x3d520000, 0x7f642200, 0x7f7e2f20, 0x7f652300, 0x6f680000, 0x7f7f0000, 0x7f7f0000, \
            0x7f143500, 0x7f7f342c, 0x7f7f007f, 0x4a7f006d, 0x003b007f, 0x71560030, 0x567f007f, 0x027f007f, \
            0x001d007f, 0x00000000                                                                          \
    }
const uint32_t sample_output_layer_0[] = SAMPLE_OUTPUT_LAYER_0;



int mod2(int val)
{
    return -((val >> 7) & 0b1) * pow(2, 7) + ((val >> 6) & 0b1) * pow(2, 6) + ((val >> 5) & 0b1) * pow(2, 5) + ((val >> 4) & 0b1) * pow(2, 4) + ((val >> 3) & 0b1) * pow(2, 3) + ((val >> 2) & 0b1) * pow(2, 2) + ((val >> 1) & 0b1) * pow(2, 1) + ((val >> 0) & 0b1) * pow(2, 0);
}

int output_layer3()
{
    const uint32_t *ptr = sample_output_layer_0;
    uint32_t mask, len;
    int count = 0;
    int first[16];
    int second[16];
    int third[16];
    int fourth[16];
    int final[192];
    int pos = 0;
    int try = 0;

    while (*ptr++ != 0)
    {
        mask = *ptr++;
        len = *ptr++;
        count = 0;

        for (int i = 0; i < len; i++)
        {
            *ptr++;
            first[count] = mod2((*(ptr - 1)) >> 0);
            pos++;
            second[count] = mod2((*(ptr - 1)) >> 8);
            pos++;
            third[count] = mod2((*(ptr - 1)) >> 16);
            pos++;
            fourth[count] = mod2((*(ptr - 1)) >> 24);
            pos++;
            count++;
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
            for (int i = 128; i < 192; i++)
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
                else if (i >= 176 && i < 192)
                {
                    final[i] = fourth[i - 176];
                }
            }
        }

        try++;
    }
    printf("final=");
    for (int i = 0; i < 192; i++)
    {
        printf("%d,", final[i]);
    }
    return 0;
}

uint8_t append[16];
uint8_t final[192];
int contatore = 0;
int counter = 0;

void split(int hex1, int hex2, int hex3, int hex4, int hex5)
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

static const uint32_t kernels[] = KERNELS;

int cnn_load_weights(void)
{
    int i, m, count = 0;
    for (i = 0; i < (sizeof(kernels) / sizeof(kernels[0])); i++)
    {
        if ((kernels[i] >> 16) == 0x0 && (kernels[i - 1] >> 24) == 0x50 && (kernels[i] == 41 || kernels[i] == 329))
        {
            // printf("Kernel_%d= \n", count);
            if (kernels[i] == 41)
            {
                split(kernels[i +  1], kernels[i +  2], kernels[i +  3], kernels[i +  4], kernels[i +  5]);
            }
            if (kernels[i] == 329)
            {
                for (m = 0; m < 329; m++)
                {
                    if (m >= 288 && m < 293)
                    {
                        split(kernels[i + m + 1], kernels[i + m + 2], kernels[i + m + 3], kernels[i + m + 4], kernels[i + m + 5]);
                        break;
                    }
                }
            }
            // printf("\n");
            count++;
        }
    }

    printf("final=");
    for (i = 0; i < 192; i++)
    {
        printf("%d,", final[i]);
    }
    printf("\n");
    return 1;
}

#define WEIGHTS {0x50180200, 0x00000029,0x50184200, 0x00000029,0x50188200, 0x00000029,\
                 0x5018c200, 0x00000029,0x50190000, 0x00000149,0x50194000, 0x00000149,\
                 0x50198000, 0x00000149,0x5019c000, 0x00000149,0x501a0000, 0x00000149,\
                 0x501a4000, 0x00000149,0x501a8000, 0x00000149,0x501ac000, 0x00000149}
static const uint32_t pesi[] = WEIGHTS;

int main()
{
    volatile uint32_t *pointer;
    volatile uint32_t *addr;
    volatile uint32_t *count;
    pointer = (volatile uint32_t *) 0x50180200;

    for(int i=0; i < 41; i++){
        printf("location= %x,",pointer++);
    }

    return 0;
}