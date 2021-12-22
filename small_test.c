// Fp1_test.c
// #include "test_mypairing.h"
#define TTT_INSTANCE_HERE
#include "small_fp.c"

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
#define curve(p)   (p->ec)

#define TIMES 1,000,000

int main(void){

    Fp a, b, c;
    char *av = "B";
    char *bv = "4";

    Fp_set_str(&a, av);
    Fp_set_str(&b, bv);

    printf("Fp1 test starts.\n");
    Fp_set_one();
    Fp_set_Rsq();
    Fp_set_p();

    Fp_print(one);
    Fp_print(Rsq);
    Fp_print(p);

    printf("add test\n");
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
    Fp_print(&a);
    Fp_print(&b);
    Fp_add(&c, &a, &b); // c = 56026a9ebae6aba9998df54035e257f368967695146187646f353aacaccaee5cff22389a8da55aa19a9be738d84f
    Fp_print(&c);

    printf("sub test\n");
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
    Fp_sub(&c, &a, &b); // 55535851d1fc7f195301121765b985ca9769896aeb9e789b8c861aacaccaee67a9abf1f19d7aa55e64d6c03f27db
    Fp_print(&c);

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
    Fp_to_Mont(&a, &a);
    Fp_to_Mont(&b, &b);

    Fp_print(&a);
    Fp_print(&b);
    Fp_mul(&c, &a, &b); 
    Fp_from_Mont(&c);
    //1802cc6e9e4dc9fa43e8765d18376b5579ea29bf060927569b0e8e91b60e762f9c00dde44fa791ca29ddd9ec0e857116b805ade3b8fc479bb30ccbe6eef554f3ed5200182d124331217cd978edca2779d2881f93bc31274cefc00dcac095f6ddd3950148ab9ff415ecb6f2f02
    Fp_print(&c);

    printf("inv test\n");
    // for(int i = 0; i < TIMES; i++){
    //     for(int k = 0; k < MOD_WORDS; k++){
    //         a.value[k] = (rand()) << 32768 + rand();
    //     }
    //     Fp_set_str(&c, "1");
    //     for(int l = 0; l < MOD_WORDS; l++){
    //         for(int j = 0; j < N->value[l] << ((int)pow(2, l)); j++){
    //             Fp_inv(&c, &a);
    //         }
    //     }
    //     Fp_mul(&c, &c, &a);
    //     if(Fp_cmp(&c, one) != 0){
    //         printf("failed. value = ");
    //         Fp_print(&c);
    //     }
    // }
    Fp_inv(&c, &a);
    Fp_mul(&c, &c, &a);
    Fp_print(&c);

    Fp_inv(&c, &b);
    Fp_mul(&c, &c, &b);
    Fp_print(&c);

    printf("test complete.\n");

    return 0;
}