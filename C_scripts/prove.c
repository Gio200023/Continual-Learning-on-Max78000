#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

signed pesi[43]= {0x50180200, 0x00000029, 0x95f90ce4, 0xbb2e5e2c, 0xf0bccbff, 0x0b09fd09, 0xf5bbc8c8, 0x0900f8d5, 0xceeee63b, 0x131f070c, 0x14fd1ef9, 0x19e1fb1c, 0x08d5c6e2, 0x110810f6, 0xd81c1ffc, 0x0c161648, 0x2bc20c51, 0x2aa7cfe1, 0x154d3ddf, 0xf1e613ea, 0xfdf9eef0, 0xe7c9fd41, 0x3e3f4728, 0x4f38378a, 0x8cb88c89, 0x87325f4a, 0x33636154, 0x7c2aca6f, 0x7dfbb7c4, 0x213b4a58, 0x27213328, 0xfb9acfff, 0xfaedfc24, 0xc6e180a2, 0xf6163546, 0x4db987f1, 0x9480a8b2, 0x8080a8b4, 0x3c331d5a, 0x16315439, 0x19000019, 0x264a142b, 0x5351000};
signed first_row[16] ={0xf0 ,0x2c ,0x5e ,0x2e ,0xbb ,0xe4 ,0x0c ,0xf9 ,0x95 ,0xbb ,0xf5 ,0x09 ,0xfd ,0x09 ,0x0b ,0xff};
int cost[10] = {1,0,0,0,0,0,0,0,0,0};
int res[164]={0};

int mod2(int val){
        return pow(-((val >> 7) & 0b1)*2,7) + pow(((val >> 6) & 0b1)*2,6) + pow(((val >> 5) & 0b1)*2,5) + pow(((val >> 4) & 0b1)*2,4) + pow(((val >> 3) & 0b1)*2,3) + pow(((val >> 2) & 0b1)*2,2) + pow(((val >> 1) & 0b1)*2,1) + pow(((val >> 0) & 0b1)*2,0);
}

void array_substraction(int *result,int *arr1,int *arr2, int size ){

    int i=0;  
    printf("size: %d\n",size);
    for(i=0 ; i< size; i++){
        result[i]=arr1[i]-arr2[i];
    }
}

int main(){

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
    int count=0;
    printf("res= ");
    for(int i=2;i < 43; i++ ){
        res[count]=mod2((pesi[i]>>0) & 0xff);
        printf("%d,",res[count]);
        count++;
        res[count]=mod2((pesi[i]>>8) & 0xff);
        printf("%d,",res[count]);
        count++;
        res[count]=mod2((pesi[i]>>16) & 0xff);
        printf("%d,",res[count]);
        count++;
        res[count]=mod2((pesi[i]>>24) & 0xff);
        printf("%d,",res[count]);
        count++;
    }
    printf("\n count= %d",count);

    

    return 0;


}