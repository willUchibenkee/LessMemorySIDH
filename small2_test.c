// small2_test.c
// #include "test_mypairing.h"
#define TTT_INSTANCE_HERE
#include "small_Fp2.c"

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
#define curve(p)   (p->ec)

#define TIMES 1,000,000

int main(void){

    Fp2 a, b, c, AR, BR, ABR, R;
    Fp2 d, e, f;
    Fp2 add, sub;
    char *av = "B 4E";
    char *bv = "6 17A";
    //char *lng = "11133333332834572365923658932758047609749767432674573257382456746574657534275672465894754867423659847585682436584";

    Fp2_set_str(&a, av);
    Fp2_set_str(&b, bv);

    printf("Fp2 test starts.\n");
    Fp_set_one();
    //printf("a");
    Fp_set_Rsq();
    //printf("b");
    Fp_set_p();
    //printf("c");
    //printf("rval: %s\n", rval);
    //Fp_set_r();
    //Fp_set_str(&c, lng);
    //Fp_print(&c);
    //Fp_print(r);

    //printf("add test\n");
    // for(int i = 0; i < TIMES; i++){
    //     for(int k = 0; k < MOD_WORDS; k++){
    //         a.value[k] = (rand()) << 32768 + rand();
    //     }
    //     for(int l = 0; l < MOD_WORDS; l++){
    //         for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
    //             Fp_add(&c, &c, &a);
    //         }
    //     }
    //     if(Fp_cmp_zero(&c) != 0){
    //         printf("failed. value = ");
    //         Fp_print(&c);
    //     }
    // }
    
    

    //printf("sub test\n");
    // for(int i = 0; i < TIMES; i++){
    //     for(int k = 0; k < MOD_WORDS; k++){
    //         a.value[k] = (rand()) << 32768 + rand();
    //     }
    //     for(int l = 0; l < MOD_WORDS; l++){
    //         for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
    //             Fp_sub(&c, &c, &a);
    //         }
    //     }
    //     if(Fp_cmp_zero(&c) != 0){
    //         printf("failed. value = ");
    //         Fp_print(&c);
    //     }
    // }
    // Fp_sub(&c, &a, &b); // 55535851d1fc7f195301121765b985ca9769896aeb9e789b8c861aacaccaee67a9abf1f19d7aa55e64d6c03f27db
    // Fp_print(&c);

    printf("mul test\n");
    // for(int i = 0; i < TIMES; i++){
    //     for(int k = 0; k < MOD_WORDS; k++){
    //         a.value[k] = (rand()) << 32768 + rand();
    //     }
    //     Fp_set_str(&c, "1");
    //     for(int l = 0; l < MOD_WORDS; l++){
    //         for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
    //             Fp_mul(&c, &c, &a);
    //         }
    //     }
    //     if(Fp_cmp(&c, one) != 0){
    //         printf("failed. value = ");
    //         Fp_print(&c);
    //     }
    // }
    printf("A:0x");
    Fp2_print(&a);
    printf("B:0x");
    Fp2_print(&b);

    Fp2_set_str(&add, "0 0");
    Fp2_add(&add, &a, &b); // c = 56026a9ebae6aba9998df54035e257f368967695146187646f353aacaccaee5cff22389a8da55aa19a9be738d84f
    printf("A+B:0x");
    Fp2_print(&add);

    Fp2_sub(&sub, &a, &b); // c = 56026a9ebae6aba9998df54035e257f368967695146187646f353aacaccaee5cff22389a8da55aa19a9be738d84f
    printf("A-B:0x");
    Fp2_print(&sub);

    Fp2_to_Mont(&a, &a);
    printf("AR:0x");
    Fp2_print(&a);
    Fp2_to_Mont(&b, &b);
    printf("BR:0x");
    Fp2_print(&b);

    Fp2_mul(&c, &a, &b); 
    printf("ABR:0x");
    Fp2_print(&c);
    Fp2_from_Mont(&c);
    printf("AB:0x");
    Fp2_print(&c);

    Fp2_inv(&f, &a);
    Fp2_mul(&f, &f, &a);
    Fp2_from_Mont(&f);
    printf("A*(1/A):0x");
    Fp2_print(&f);
    //Fp_print(one);

    // Fp test;
    // Fp2_set_str(&test, "9");
    // printf("test=");
    // Fp_print(&test);
    // Fp_to_Mont(&test, &test);
    // //printf("a");
    // Fp_div3(&test, &test);
    // Fp_from_Mont(&test);
    // printf("9/3=");
    // Fp_print(&test);

    // Fp ichi, num;
    // Fp_set_str(&ichi, "1");
    // Fp_set_str(&num, "7");
    // Fp_print(&num);
    // Fp_print(&ichi);
    // Fp_sub(&num, &num, &ichi);
    // printf("7-1=");
    // Fp_print(&num);

    printf("test complete.\n");

    return 0;
}