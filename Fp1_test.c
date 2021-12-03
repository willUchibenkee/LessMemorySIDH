// Fp1_test.c
// #include "test_mypairing.h"
#define TTT_INSTANCE_HERE
#include "Fp1.c"

#define TIMES 1,000,000
// #define Avalue ""
// #define Bvalue ""
// #define Cvalue ""
// Fp po;
// Fp oneo;
// Fp rsqo;
// Fp ro;
// Fp No;

//  Fp *p;
//  Fp *one;
//  Fp *Rsq;
//  Fp *r;
//  Fp *N;

//  Fp *p= &po;
//  Fp *one= &oneo;
//  Fp *Rsq = &rsqo;
//  Fp *r= &ro;
//  Fp *N= &No;


int main(void){

    // Fp a, b, c;
    // // a[0]0~31 a[1]32~63
    // p = &po;
    // one = &oneo;
    // Rsq = &rsqo;
    // r = &ro;
    // N = &No;

    printf("Fp1 test starts.\n");
    // Fp_set_R();
    Fp_set_str(r, "00006FE5D541F71C0E12909F97BADC668562B5045CB25748084E9867D6EBE876DA959B1A13F7CC76E3EC968549F878A8EEAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    // printf("a\n");
    // // Fp_set_N();
    // Fp_set_str(N, Nval);
    // printf("b\n");
    // Fp_set_p();
    // printf("c\n");
    // Fp_set_one();
    // printf("d\n");
    // Fp_set_Rsq();

    Fp_print(r);
    // Fp_print(N);
    // Fp_print(p);
    // Fp_print(one);
    // Fp_print(Rsq);

    // printf("add test\n");
    // for(int i = 0; i < TIMES; i++){
    //     for(int k = 0; k < MOD_WORDS; k++){
    //         a.value[k] = (rand()) << 32768 + rand();
    //     }
    //     for(int l = 0; l < MOD_WORDS; l++){
    //         for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
    //             Fp_add(&c, &c, &a);
    //         }
    //     }
    //     if(Fp_cmp(&c, r) != 0){
    //         printf("failed. value = ");
    //         Fp_print(&c);
    //     }
    // }

    // printf("sub test\n");

    // printf("mul test\n");

    // printf("inv test\n");

    // printf("test complete.\n");

    return 0;
}