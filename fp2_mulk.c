#define TTT_INSTANCE_HERE
#include "small_Fp2.c"

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
#define curve(p)   (p->ec)


int main(void){

    Fp2 A, B2, C;

    Fp_set_one();
    Fp_set_p();
    Fp_set_Rsq();

    Fp2_set_str(&A, "149 1a7");
    Fp2_set_str(&B2, "f8 64");

    printf("A:");
    Fp2_print(&A);
    printf("B:");
    Fp2_print(&B2);

    Fp2_to_Mont(&A, &A);
    Fp2_to_Mont(&B2, &B2);

    Fp2_mul(&C, &A, &B2);
    printf("C:");
    Fp2_from_Mont(&C);
    Fp2_print(&C);

}