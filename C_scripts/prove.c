#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "sample_inputs.h"

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
int flatten[] = {127, 127, 127, 68, 127, 127, 127, 127, 62, 24, 11, 0, 0, 0, 0, 0, 
                11, 8, 25, 58, 94, 105, 52, 98, 99, 127, 38, 43, 60, 127, 36, 0, 
                127, 127, 127, 110, 113, 107, 86, 59, 0, 0, 0, 34, 0, 0, 0, 29,
                0, 15, 3, 36, 0, 0, 0, 61, 0, 0, 0, 0, 0, 0, 0, 0, 
                0, 0, 0, 42, 17, 0, 0, 0, 59, 91, 0, 0, 49, 45, 0, 0, 
                52, 15, 33, 57, 0, 0, 22, 0, 0, 9, 0, 0, 46, 2, 0, 24, 
                127, 127, 109, 0, 127, 127, 127, 0, 89, 64, 46, 52, 56, 73, 127, 115,
                 127, 127, 93, 66, 127, 127, 105, 10, 127, 81, 0, 0, 56, 0, 12, 51,
                  0, 0, 32, 0, 0, 0, 0, 0, 44, 127, 109, 127, 48, 127, 127, 127,
                   0, 34, 47, 35, 0, 0, 0, 53, 52, 0, 0, 0, 0, 0, 0, 0, 82, 100, 126, 101, 104, 127, 127, 20, 127, 127, 127, 59, 86, 127, 127, 29, 61, 127, 127, 127, 111, 127, 127, 127, 127, 127, 74, 0, 113, 86, 2, 0};

int sample_mod2[] = {127, 11, 127, 0, 127, 8, 127, 15, 127, 25, 127, 3, 68, 58, 110, 36, 127, 94, 113, 0, 127, 105, 107, 0, 127, 52, 86, 0, 127, 98, 59, 61, 62, 99, 0, 0, 24, 127, 0, 0, 11, 38, 0, 0, 0, 43, 34, 0, 0, 60, 0, 0, 0, 127, 0, 0, 0, 36, 0, 0, 0, 0, 29, 0, 0, 52, 127, 127, 0, 15, 127, 127, 0, 33, 109, 93, 42, 57, 0, 66, 17, 0, 127, 127, 0, 0, 127, 127, 0, 22, 127, 105, 0, 0, 0, 10, 59, 0, 89, 127, 91, 9, 64, 81, 0, 0, 46, 0, 0, 0, 52, 0, 49, 46, 56, 56, 45, 2, 73, 0, 0, 0, 127, 12, 0, 24, 115, 51, 0, 0, 82, 61, 0, 34, 100, 127, 32, 47, 126, 127, 0, 35, 101, 127, 0, 0, 104, 111, 0, 0, 127, 127, 0, 0, 127, 127, 0, 53, 20, 127, 44, 52, 127, 127, 127, 0, 127, 127, 109, 0, 127, 74, 127, 0, 59, 0, 48, 0, 86, 113, 127, 0, 127, 86, 127, 0, 127, 2, 127, 0, 29, 0};

signed pesi[43] = {0x50180200, 0x00000029, 0x95f90ce4, 0xbb2e5e2c, 0xf0bccbff, 0x0b09fd09, 0xf5bbc8c8, 0x0900f8d5, 0xceeee63b, 0x131f070c, 0x14fd1ef9, 0x19e1fb1c, 0x08d5c6e2, 0x110810f6, 0xd81c1ffc, 0x0c161648, 0x2bc20c51, 0x2aa7cfe1, 0x154d3ddf, 0xf1e613ea, 0xfdf9eef0, 0xe7c9fd41, 0x3e3f4728, 0x4f38378a, 0x8cb88c89, 0x87325f4a, 0x33636154, 0x7c2aca6f, 0x7dfbb7c4, 0x213b4a58, 0x27213328, 0xfb9acfff, 0xfaedfc24, 0xc6e180a2, 0xf6163546, 0x4db987f1, 0x9480a8b2, 0x8080a8b4, 0x3c331d5a, 0x16315439, 0x19000019, 0x264a142b, 0x5351000};
signed first_row[16] = {0xf0, 0x2c, 0x5e, 0x2e, 0xbb, 0xe4, 0x0c, 0xf9, 0x95, 0xbb, 0xf5, 0x09, 0xfd, 0x09, 0x0b, 0xff};
int cost[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int res[164] = {0};

int mod2(int val)
{
    return -((val >> 7) & 0b1) * pow(2, 7) + ((val >> 6) & 0b1) * pow(2, 6) + ((val >> 5) & 0b1) * pow(2, 5) + ((val >> 4) & 0b1) * pow(2, 4) + ((val >> 3) & 0b1) * pow(2, 3) + ((val >> 2) & 0b1) * pow(2, 2) + ((val >> 1) & 0b1) * pow(2, 1) + ((val >> 0) & 0b1) * pow(2, 0);
}

void array_substraction(int *result, int *arr1, int *arr2, int size)
{

    int i = 0;
    printf("size: %d\n", size);
    for (i = 0; i < size; i++)
    {
        result[i] = arr1[i] - arr2[i];
    }
}

void output_layer_3()
{
    int i, k;
    uint32_t mask, len;
    const uint32_t *addr;
    const uint32_t *ptr = sample_output_layer_0;
    int count = 0;
    int first[16];
    int second[16];
    int third[16];
    int fourth[16];
    int final[192] = {0};
    int pos = 0;
    int counter1=0;
    int counter2=0;
    int counter3=0;
    int counter4=0;

    while ( *ptr++ != 0)
    {
        k = pos;
        mask = *ptr++;
        len = *ptr++;
        count = 0;
        counter1=0;
        counter2=0;
        counter3=0;
        counter4=0;

        for (int s = 0; s < len; s++)
        {
                // printf("Mod2: [1]: %7d              flatten[%3d]: [%3d]\n", mod2((*(ptr - 1)) >> 0), count, flatten[count]);
                first[count] = mod2((*(ptr - 1)) >> 0);
                // count++;
                // printf("\n first[%d] = %2d\n",count,first[count]);
                // sleep(1);
                // printf("Mod2: [2]: %7d              flatten[%3d]: [%3d]\n", mod2((*(ptr - 1)) >> 8), count, flatten[count]);
                second[count] = mod2((*(ptr - 1)) >> 8);
                // printf("\n second[%d] = %2d\n",count,second[count]);
                // sleep(1);
                // count++;

                // printf("Mod2: [3]: %7d              flatten[%3d]: [%3d]\n", mod2((*(ptr - 1)) >> 16), count, flatten[count]);
                third[count] = mod2((*(ptr - 1)) >> 16);
                // count++;

                // printf("Mod2: [4]: %7d              flatten[%3d]: [%3d]\n", mod2((*(ptr - 1)) >> 24), count, flatten[count]);
                fourth[count] = mod2((*(ptr - 1)) >> 24);
                count++;
                *ptr++;
                // printf("ptr = %2d\n",ptr);
                // printf("count %d\n",count);
                pos++;
        }
        
        for (; k < pos+16; k++)
        {
            if (k < 16 || (k >= 64 && k < 80) || (k >= 128 && k < 144))
            {
                final[k] = first[counter1];
                counter1++;
            }
            else if ((k >= 16 && k < 32) || (k >= 80 && k < 96) || (k >= 144 && k < 160))
            {
                final[k] = second[counter2];
                counter2++;
            }
            else if ((k >= 32 && k < 48) || (k >= 96 && k < 112) || (k >= 160 && k < 176))
            {
                final[k] = third[counter3];
                counter3++;
            }
            else if ((k >= 48 && k < 64) || (k >= 112 && k < 128) || (k >= 176 && k < 192))
            {
                final[k] = fourth[counter4];
                counter4++;
            }
        }
        
    }


    printf("final= ");
    for(int m=0; m < 192; m++){
        printf("%3d,",final[m]);
    }
}

uint32_t *prova(){
    static uint32_t pro[10];
    for(int i=0; i< 10; i++){
        pro[i]=i;
        printf("%d ",pro[i]);
    }

    return pro;
}

int main()
{

    /*
     * @brief first try to sum 2 array one by one
     *
     */
    // int arr1[5]={1,2,3,4,5};
    // int arr2[5]={1,2,3,4,5};
    // int res[5]={0};
    // array_substraction(res,arr1,arr2,sizeof res/sizeof res[0]);
    // for(int i=0; i< sizeof res/sizeof res[0]; i++){
    //     printf("%d,",res[i]);
    // }

    // printf("%d\n",pesi[1]);
    // for(int i=0; i < pesi[1]; i++){
    //     printf("%x\n",pesi[i+2]);
    // }

    /**
     * @brief mod2 of kernels in c
     *
     */
    // int count=0;
    // printf("res= ");
    // for(int i=2;i < 43; i++ ){
    //     res[count]=mod2((pesi[i]>>0) & 0xff);
    //     printf("%d,",res[count]);
    //     count++;
    //     res[count]=mod2((pesi[i]>>8) & 0xff);
    //     printf("%d,",res[count]);
    //     count++;
    //     res[count]=mod2((pesi[i]>>16) & 0xff);
    //     printf("%d,",res[count]);
    //     count++;
    //     res[count]=mod2((pesi[i]>>24) & 0xff);
    //     printf("%d,",res[count]);
    //     count++;
    // }
    // printf("\n count= %d",count);

    /**
     * @brief sample output check
     *
     */
    // output_layer_3();

    /**
     * @brief Pointer example
     * 
     */
    // uint32_t *pro;
    // pro = prova();

    // for(int i=0; i< 10; i++){
    //     printf("%d ",*(pro+i));
    // }

    printf("%x\n",sample_inputs_all[1][1]);

    return 0;
}