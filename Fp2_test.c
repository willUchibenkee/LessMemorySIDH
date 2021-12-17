// Fp2_test.c

#define TTT_INSTANCE_HERE
#include "Fp2.c"

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
//#define ec_field(p)   (p->ec->field)
#define curve(p)   (p->ec)

#define TIMES 1,000,000

int main(void){

    Fp2 a, b, c;

    printf("Fp1 test starts.\n");
    // Fp_set_R();
    // Fp_set_r();
    // // printf("a\n");
    //  Fp_set_N();
    // // Fp_set_str(N, Nval);
    // // printf("b\n");
    //  Fp_set_p();
    // printf("c\n");
     Fp_set_one();
    // printf("d\n");
     Fp_set_Rsq();

    // Fp_print(r);
    // Fp_print(N);
    // Fp_print(p);
    Fp_print(one);
    Fp_print(Rsq);

    Fp2 onefp2;
    Fp2_set_fp(&onefp2, one);

    printf("add test\n");
    for(int i = 0; i < TIMES; i++){
        for(int k = 0; k < MOD_WORDS; k++){
            a.element[0].value[k] = (rand()) << 32768 + rand();
            a.element[1].value[k] = (rand()) << 32768 + rand();
        }
        for(int l = 0; l < MOD_WORDS; l++){
            for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
                Fp2_add(&c, &c, &a);
            }
        }
        if(Fp2_cmp_zero(&c) != 0){
            printf("failed. value = ");
            Fp2_print(&c);
        }
    }

     printf("sub test\n");
    for(int i = 0; i < TIMES; i++){
        for(int k = 0; k < MOD_WORDS; k++){
            a.element[0].value[k] = (rand()) << 32768 + rand();
            a.element[1].value[k] = (rand()) << 32768 + rand();
        }
        for(int l = 0; l < MOD_WORDS; l++){
            for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
                Fp2_sub(&c, &c, &a);
            }
        }
        if(Fp2_cmp_zero(&c) != 0){
            printf("failed. value = ");
            Fp2_print(&c);
        }
    }

    printf("mul test\n");
    for(int i = 0; i < TIMES; i++){
        for(int k = 0; k < MOD_WORDS; k++){
            a.element[0].value[k] = (rand()) << 32768 + rand();
            a.element[1].value[k] = (rand()) << 32768 + rand();
        }
        Fp2_set_str(&c, "1 0");
        for(int l = 0; l < MOD_WORDS; l++){
            for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
                Fp2_mul(&c, &c, &a);
            }
        }
        if(Fp2_cmp(&c, &onefp2) != 0){
            printf("failed. value = ");
            Fp2_print(&c);
        }
    }

    printf("inv test\n");
    for(int i = 0; i < TIMES; i++){
        for(int k = 0; k < MOD_WORDS; k++){
            a.element[0].value[k] = (rand()) << 32768 + rand();
            a.element[1].value[k] = (rand()) << 32768 + rand();
        }
        Fp2_set_str(&c, "1");
        for(int l = 0; l < MOD_WORDS; l++){
            for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
                Fp2_inv(&c, &a);
            }
        }
        Fp2_mul(&c, &c, &a);
        if(Fp2_cmp(&c, &onefp2) != 0){
            printf("failed. value = ");
            Fp2_print(&c);
        }
    }

    //legendre srqt test

    printf("test complete.\n");

    return 0;
}