#include "stdio.h"
#include "stdint.h"
#include "math.h"

int8_t output_channel_5[192] = {-3, -72, -116, -118, 55, 56, 79, 40, 71, 63, 97, 99, 51, 74, 95, 50, -13, 28, -57, -93, -2, 36, 20, -6, 21, 34, 29, 84, 20, 5, 44, 37, -46, -32, 9, 29, -10, 36, 84, 76, 33, 59, 86, 82, 47, 58, 47, 33, -6, -82, -126, -102, -9, 17, -9, 13, -6, 43, 28, 33, -36, 3, 55, 19, -18, 78, 126, 122, -81, -84, 49, 72, -89, -84, -22, -62, -77, -55, -11, -30, -25, -38, 0, 32, -54, -51, 62, 65, -46, -81, -61, -49, -35, -48, -32, -52, -75, -96, -78, 72, -39, -105, -39, 76, 4, -55, -47, 30, -11, -25, -27, -18, 24, 6, -7, 33, 47, 22, -43, 46, 115, 49, -31, 9, 55, 34, 11, -26, -16, 10, -17, -45, -2, 9, -12, -17, -38, -39, -30, -58, -49, -79, -72, -59, -7, 8, -85, -87, -19, -35, -68, -71, 5, 1, -26, -8, 0, 33, 74, 52, -32, -84, 30, 104, -69, -59, 19, 118, -52, -38, 0, 62, -22, -33, -12, -34, -48, -127, -128, -78, -65, -59, -36, 24, 41, 84, 107, 49, 62, 108, 101, 48};
int8_t flatten_layer[192] = {127, 127, 127, 68, 127, 127, 127, 127, 62, 24, 11, 0, 0, 0, 0, 0, 11, 8, 25, 58, 94, 105, 52, 98, 99, 127, 38, 43, 60, 127, 36, 0, 127, 127, 127, 110, 113, 107, 86, 59, 0, 0, 0, 34, 0, 0, 0, 29, 0, 15, 3, 36, 0, 0, 0, 61, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 17, 0, 0, 0, 59, 91, 0, 0, 49, 45, 0, 0, 52, 15, 33, 57, 0, 0, 22, 0, 0, 9, 0, 0, 46, 2, 0, 24, 127, 127, 109, 0, 127, 127, 127, 0, 89, 64, 46, 52, 56, 73, 127, 115, 127, 127, 93, 66, 127, 127, 105, 10, 127, 81, 0, 0, 56, 0, 12, 51, 0, 0, 32, 0, 0, 0, 0, 0, 44, 127, 109, 127, 48, 127, 127, 127, 0, 34, 47, 35, 0, 0, 0, 53, 52, 0, 0, 0, 0, 0, 0, 0, 82, 100, 126, 101, 104, 127, 127, 20, 127, 127, 127, 59, 86, 127, 127, 29, 61, 127, 127, 127, 111, 127, 127, 127, 127, 127, 74, 0, 113, 86, 2, 0};

void modify_flatten(int *ptr)
{
    static int count = 1;
    *ptr = *ptr + count++;
}

void modi(int *ptr)
{
    *ptr += 2;
}

// void load_weights()
// {
//     static const int *pntr = ciao;
//     printf("prima %d\n", *pntr);
//     modify_flatten(ciao);
//     printf("dopo %d\n", *pntr);

//     modify_flatten(ciao);
//     printf("dopodopo %d\n", *pntr);
// }

int n = 0;
void due(int (*try)[3])
{
    for (int i = 0; i < 3; i++)
    {
        (*try)[i] = n++;
    }
}
int place = 0;
// void fill(int try[3][3])
// {
//     due(try +)
// }

void update_bias(int *bias)
{
    for (int i = 0; i < 6; i++)
    {
        *(bias + i) += 2;
    }
}

void memcpy32(uint32_t *dst, const uint32_t *src, int n)
{
    printf("\n");
    while (n-- > 0)
    {
        // printf("*src = %x\n",*src);
        *src++;
        printf("*dst = %x", *src);
    }
}

// int input = 0;
// static uint32_t *input_0;
// void load_input(void)
// {
//     if (input == 45)
//     {
//         input = 0;
//     }
//     input_0 = sample_inputs_all[input];
//     printf("*input = %x\n",*input_0);
//     memcpy32((uint32_t *)0x50400000, input_0, 196);
// }

int sign(float num)
{
    if (num > 0)
    {
        return 1;
    }
    else if (num < 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int abs_mio(float num)
{
    if (num > 0)
    {
        return num;
    }
    else if (num < 0)
    {
        return -1 * num;
    }
    else
    {
        return num;
    }
}

int main()
{
    // printf("%d\n",sizeof(sample)/sizeof(uint8_t));
    // int *input_0 = &prova[0][0];

    // for (int i = 0; i < 2; i++)
    // {
    //     printf("%x ", *(input_0 + i * 3));
    // }

    // fill a multidimensional array
    // int prova[3][3] = {0};
    // for (int f = 0; f < 3; f++)
    // {
    //     printf("\n");
    //     for (int m = 0; m < 3; m++)
    //     {
    //         printf(" %d ", prova[f][m]);
    //     }
    // }
    // fill(prova);

    // for (int f = 0; f < 3; f++)
    // {
    //     printf("\n");
    //     for (int m = 0; m < 3; m++)
    //     {
    //         printf(" %d ", prova[f][m]);
    //     }
    // }

    // int m=0;
    // int append[10] = {0};
    // append[m++]=7;
    // append[m++]=5;
    // append[m]=3453;

    // for(int i=0; i< 10; i++){
    //     printf(" %d ",append[i]);
    // }

    // BIAS UPDATE
    // int bias[6] = {1, 2, 3, 4, 5, 6};
    // update_bias(bias);

    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%d\n", bias[i]);
    // }

    // LOAD_input
    // load_input();
    // printf("flatten ");
    // for (int i = 0; i < 192; i++)
    // {
    //     printf(" %d ", flatten_layer[i]);
    // }
    // printf("\n");

    // printf("output ");
    // for (int i = 0; i < 192; i++)
    // {
    //     printf(" %d ", output_channel_5[i]);
    // }
    // printf("\n");

    int32_t res;
    int tmp;
    for (int i = 0; i < 192; i++)
    {
        tmp= flatten_layer[i] * output_channel_5[i];
        res += tmp;
    }

    printf("%d\n", res);

    // int sign_num = 0;
    // int mult = 0;
    // int mult1;
    // int res = 0;
    // int fin = 0;
    // int output[192] = {0};
    // int a = 0, b = 0, c = 0, d = 0;

    // printf("res = [ ");
    // for (int i = 0; i < 192; i++)
    // {
    //     sign_num = sign(-1 / 64) * sign(1 / 2);
    //     a = abs_mio(1 / 64);
    //     b = abs_mio(1 / 2);
    //     c = a << 7;
    //     d = b << 7;
    //     printf("a = %d, b = %d\n", a, b);
    //     printf("c = %d, d = %d\n", c, d);

    //     mult = c * d;
    //     res = (mult >> 7) * -1;
    //     output[i] = res;
    //     printf(" %d ", output[i]);
    //     return 0;
    // }
    // printf("]");

    // for (int i = 0; i < 192; i++)
    // {
    //     fin += output[i];
    // }
    // printf("fin = %d\n", fin);

    // int a = 4612;
    // printf("%d\n",(int8_t)a);
}
