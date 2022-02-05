//

#define TTT_INSTANCE_HERE
#include "small_Fp1.c"
#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
#define curve(p)   (p->ec)

#define TIMES 1

void check_fp();

int main(void){

    Fp_set_p();
    Fp_set_Rsq();
    Fp_set_one();


    for(int g = 0; g < TIMES; g++){
        check_fp();
    }

    // mpz_t r, n;
    // gmp_randstate_t state;

    // gmp_randinit_default(state);

    // mpz_init(n);
    // mpz_init(r);

    // mpz_set_ui(n, 430);

    // mpz_urandomm(r, state, n);

    // gmp_printf("%Zd\n",r);

    // Fp_set_p();
    // Fp_set_Rsq();
    // Fp_set_one();

    // Fp a, c;

    // char *av;
    // char v[20];
    // av = v;

    // Fp_print(one);
    // Fp_print(Rsq);
    // Fp_print(p);

    // for(int i = 0; i < TIMES; i++){

    //     mpz_urandomm(r, state, n);

    //     mpz_get_str(av, 16, r);

    //     Fp_set_str(&a, av);

    //     printf("a:");
    //     Fp_print(&a);

    //     Fp_to_Mont(&a, &a);
    //     Fp_set(&c, one);

    //     for(int k = 0; k < 430; k++){
    //         Fp_mul(&c, &c, &a);
    //     }
    //     if(Fp_cmp_one(&c) == 0){
    //         printf("not 1\n");
    //         Fp_from_Mont(&a);
    //         printf("a:");
    //         Fp_print(&a);

    //         printf("c:");
    //         Fp_print(&c);
    //         getchar();
    //     }
    // }

    // printf("ok\n");

    return 0;
}

void check_fp(){

    printf("check_fp() 開始\n");

    mpz_t A, ANS, n;

    gmp_randstate_t state;

    Fp a, ans;

    char v[20];

    char *av = v;

    mpz_init(A);

    mpz_init(ANS);

    mpz_init(n);

    gmp_randinit_default(state);
    gmp_randseed_ui(state,(unsigned long int)time(NULL));

    mpz_set_ui(n, 430);

    mpz_urandomm(A, state, n);

    gmp_printf("A = %Zd\n", A);

    mpz_get_str(av, 16, A);

    Fp_set_str(&a, av);

    Fp_to_Mont(&a, &a);

    Fp_inv(&ans,&a);

    Fp_from_Mont(&ans);
    
    printf("A^-1 = ");
    Fp_print(&ans);

    Fp_to_Mont(&ans, &ans);

    Fp_mul(&ans,&ans,&a);

    if(Fp_cmp_one(&ans) ==0){
        Fp_from_Mont(&ans);

        printf("A * A^-1 = ");
        Fp_print(&ans);
        exit(1);

    }
    Fp_from_Mont(&ans);

    printf("A * A^-1 = ");
    Fp_print(&ans);

    Fp_to_Mont(&ans, &ans);

    printf("---------------------------------\n");



    // printf("平方根アルゴリズムの確認\n");

    // int flag=fp_legendre(&a);

    // printf("fp_legendre(A) = %d\n",flag);

    // if(flag==1){

    // fp_sqrt(&ans,&a);

    // printf("fp_sqrt(A) = ");
    // Fp_print(&ans);

    // //fp_mul(&ANS,&ANS,&ANS);

    // fp_sqr(&ANS,&ANS);

    // if(fp_cmp(&ANS,&A)==0){

    // printf("(fp_sqrt(A))^2 = A\n\n");

    // }

    // elseprintf("(fp_sqrt(A))^2 != A\n\n");

    // }

    // printf("---------------------------------\n");



    printf("フェルマーの小定理の確認\n");

    //mpz_init(tmp);

    //mpz_sub_ui(tmp,prime_z,1);

    //fp_pow(&ANS,&A,tmp);

    Fp_set(&ans, one);


    for(int u = 0; u < 429; u++){
        Fp_mul(&ans, &ans, &a);
    }
;
    Fp_from_Mont(&ans);
    printf("A^(p-1) = ");
    Fp_print(&ans);

    printf("---------------------------------\n");



    Fp_from_Mont(&a);

    Fp_get_str(av , &a);

    mpz_set_str(A, av, 16);

    gmp_printf("A = %Zd\n", A);//Aが変わっていないことの確認



    printf("*********************************************************************************************\n\n");

}