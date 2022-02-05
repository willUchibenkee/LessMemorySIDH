//fp2_k.c(Montgomery)

#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>
#include<stdlib.h>
#include"fp2.h"

int main(void){
//     r=0x100000000
// p=0x1af



// a0=0xB
// a1=0x4E
// b0=0x6
// b1=0x17A

    fp2 a,b, c;
    fp2_init(&a);
    fp2_init(&b);
    fp2_init(&c);

    fp2_set_ui(&a, 423, 329);
    //1a7
    fp2_set_ui(&b, 248, 100);

    fp2_mul(&c, &a, &b);

    printf("a*P->x:");
    fp2_printf(&c);
    //1b c3

}