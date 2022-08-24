#include "stdio.h"
#include "stdint.h"
#include "sample_inputs.h"


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

int input = 0;
static uint32_t *input_0;
void load_input(void)
{
    if (input == 45)
    {
        input = 0;
    }
    input_0 = sample_inputs_all[input];
    printf("*input = %x\n",*input_0);
    memcpy32((uint32_t *)0x50400000, input_0, 196);
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
    load_input();
}
