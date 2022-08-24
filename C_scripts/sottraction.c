#include "stdio.h"
#include "stdint.h"
#include "math.h"

int mod2(int val)
{
    return -((val >> 7) & 0b1) * pow(2, 7) + ((val >> 6) & 0b1) * pow(2, 6) + ((val >> 5) & 0b1) * pow(2, 5) + ((val >> 4) & 0b1) * pow(2, 4) + ((val >> 3) & 0b1) * pow(2, 3) + ((val >> 2) & 0b1) * pow(2, 2) + ((val >> 1) & 0b1) * pow(2, 1) + ((val >> 0) & 0b1) * pow(2, 0);
}

int32_t sottraction(int32_t *hex, int dW, int shift)
{
    int8_t tmp;
    // printf("%d\n",(*dW)[update_place]);
    printf("hex prima era uguale a = %x\n", *hex);
    tmp = mod2((*hex >> shift) & 0xff) - mod2(dW);
    printf("mod2(dw) = %d\n",mod2(0xe4));
    printf("tmp = %x\n", tmp);
    printf("hexincula= %x\n", ((mod2((*hex >> shift) & 0xff) - mod2(tmp)) << shift));
    *hex = *hex - ((mod2((*hex >> shift) & 0xff) - mod2(tmp)) << shift);
    printf("hex ora è uguale a = %x\n", *hex);

    return *hex;
}

int round_mio(double num)
{
    printf("num = %f\n", num);
    if (num < 0.5 && num > -0.5)
        return 0;
    if (num < -0.5)
        return -1;
    if (num > 0.5)
        return 1;
    return 5;
}

int main()
{
    int32_t a = 0x95f90ce4;
    int32_t *hex1;
    hex1 = &a;
    sottraction(hex1,300,0);
    // int aka = 30171;
    // int taka = 32767;
    // double b = (double)aka / (double)taka;
    // int c = 0;
    // int f;
    // f = round(b) - c;
    // printf("%d\n", f);

    // float learn = 0.1;
    // int16_t delta = 2000;
    // int a = (float)learn * delta;
    // printf("%d\n",a);
}

