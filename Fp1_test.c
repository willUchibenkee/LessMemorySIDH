// Fp1_test.c
// #include "test_mypairing.h"
#define TTT_INSTANCE_HERE
#include "Fp1.c"

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
#define curve(p)   (p->ec)

#define TIMES 1,000,000

int main(void){

    Fp a, b, c, AR, BR, ABR, R;
    char *av = "55AAE17846719561764783ABCDCDEEDEFFFFFFFFFFFFFFFFFDDDAAACACCAEE6254671546158FFFFFFFB953BC0015";
    char *bv = "578926747516482346719468146914689676951461876471578FFFFFFFFFFAAABb235478155AA19AE2937CD83A";

    Fp_set_str(&a, av);
    Fp_set_str(&b, bv);

    printf("Fp1 test starts.\n");
    Fp_set_one();
    Fp_set_Rsq();
    Fp_set_p();
    Fp_set_r();
    Fp_print(r);

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
    
    // Fp_add(&c, &a, &b); // c = 56026a9ebae6aba9998df54035e257f368967695146187646f353aacaccaee5cff22389a8da55aa19a9be738d84f
    // Fp_print(&c);

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
    Fp_print(&a);
    printf("B:0x");
    Fp_print(&b);

    Fp_set_str(&AR, av);
    Fp_set_str(&BR, bv);
    Fp_to_Mont(&AR, &AR);
    Fp_to_Mont(&BR, &BR);
    Fp_to_Mont(&R, &R);

    Fp_AR(&AR);
    Fp_AR(&BR);
    Fp_from_Mont(&AR);
    printf("AR:0x");
    Fp_print(&AR);
    Fp_from_Mont(&BR);
    printf("BR:0x");
    Fp_print(&BR);

    Fp_to_Mont(&AR, &AR);
    Fp_to_Mont(&b, &b);
    Fp_mul(&ABR, &AR, &b);
    Fp_from_Mont(&ABR);
    printf("ABR:0x");
    Fp_print(&ABR);

    Fp_to_Mont(&a, &a);
    //Fp_to_Mont(&b, &b);
    Fp_mul(&c, &a, &b); 
    Fp_from_Mont(&c);
    printf("AB:0x");
    Fp_print(&c);

    //printf("inv test\n");
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
    // Fp_inv(&c, &a);
    // Fp_mul(&c, &c, &a);
    // Fp_print(&c);

    // Fp_inv(&c, &b);
    // Fp_mul(&c, &c, &b);
    // Fp_print(&c);

    //printf("test complete.\n");

    return 0;
}