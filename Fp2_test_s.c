//fp2_k.c(Montgomery)

#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>
#include<stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include<time.h>
#include"small_Efp2.c"

#define TIMES 200

void check_fp2_34();

void check_fp2_cmp();

int main(void){
    // mpz_init(prime_z);
    // mpz_set_ui(prime_z, p);

    Fp_set_prime_z();
    Fp_set_p();
    Fp_set_one();
    Fp_set_Rsq();

    for(int g = 0; g < TIMES; g++){
        check_fp2_34();
        check_fp2_cmp();
        getchar();
    }

    //check_fp2();

    return 0;
}

void check_fp2_34(){

    printf("check_fp2() 開始\n");

    mpz_t A, n;

    gmp_randstate_t state;

    Fp2 a, ans;

    char v[20];

    char *av = v;

    mpz_init(A);

    //mpz_init(ANS);

    mpz_init(n);

    gmp_randinit_default(state);
    gmp_randseed_ui(state,(unsigned long int)time(NULL));

    mpz_set_ui(n, 430);

    mpz_urandomm(A, state, n);

    gmp_printf("A = %Zd\n", A);

    mpz_get_str(av, 16, A);

    Fp_set_str(&a.element[0], av);

    mpz_urandomm(A, state, n);

    gmp_printf("A = %Zd\n", A);

    mpz_get_str(av, 16, A);

    Fp_set_str(&a.element[1], av);

    Fp2_to_Mont(&a, &a);

    //fp2_set_ui(&A, 6, 310);
    //358i + 275, 410i + 104
    // fp2_set_ui(&alpha, 37, 18);  

    // fp2_sub(&A, &A, &alpha);

    // fp2_mul(&A, &A, &A);

    Fp pm;
    Fp_set_str(&pm,"1ae");

    printf("A = ");
    Fp2_print_s(&a);

    Fp2_scalarexp(&ans, &a, pm);
    printf("A ** p-1 = ");
    Fp2_print_s(&ans);

    printf("--------------------------------\n");

    Fp2_inv(&ans,&a);

    printf("A^-1 = ");
    Fp2_print_s(&ans);

    Fp2_mul(&ans,&ans,&a);

    printf("A * A^-1 = ");
    Fp2_print_s(&ans);

    printf("---------------------------------\n");

    printf("平方根アルゴリズムの確認\n");

    int flag=Fp2_legendre(&a);

    printf("fp2_legendre(A) = %d\n",flag);

    if(flag==1){

    Fp2_sqrt_34(&ans,&a);

    printf("fp2_sqrt(A) = ");
    Fp2_print_s(&ans);

    Fp2_mul(&ans,&ans,&ans);

    //fp2_sqr(&ANS,&ANS);

    if(Fp2_cmp(&ans,&a)==0){

        printf("(fp2_sqrt(A))^2 = A\n\n");

    }else{

        printf("(fp2_sqrt(A))^2 != A\n\n");

    }

    printf("---------------------------------\n");



    printf("フェルマーの小定理の確認\n");

    mpz_t tmp, mt;

    Fp temp;

    mpz_init(tmp);

    mpz_init(mt);

    mpz_set_ui(mt, 431);

    mpz_pow_ui(tmp, mt, 430);

    mpz_sub_ui(tmp,tmp,1);

    mpz_get_str(av, 16, tmp);

    Fp_set_str(&temp, av);

    Fp2_scalarexp(&ans, &a, temp);

    printf("A^(p^430-1) = ");
    Fp2_print_s(&ans);

    printf("---------------------------------\n");



    printf("A = ");
    Fp2_print_s(&a);//Aが変わっていないことの確認



    printf("*********************************************************************************************\n\n");

    }
}

void check_fp2_cmp(){
    printf("check_fp2_cmp() 開始\n");

    //Fp2 A, C;

    mpz_t A, n;

    gmp_randstate_t state;

    Fp2 a, c;

    char v[20];

    char *av = v;

    mpz_init(A);

    //mpz_init(ANS);

    mpz_init(n);

    gmp_randinit_default(state);
    gmp_randseed_ui(state,(unsigned long int)time(NULL));

    mpz_set_ui(n, 430);

    mpz_urandomm(A, state, n);

    gmp_printf("A = %Zd\n", A);

    mpz_get_str(av, 16, A);

    Fp_set_str(&a.element[0], av);

    mpz_urandomm(A, state, n);

    gmp_printf("A = %Zd\n", A);

    mpz_get_str(av, 16, A);

    Fp_set_str(&a.element[1], av);

    mpz_urandomm(A, state, n);

    gmp_printf("A = %Zd\n", A);

    mpz_get_str(av, 16, A);

    Fp_set_str(&c.element[0], av);

    mpz_urandomm(A, state, n);

    gmp_printf("A = %Zd\n", A);

    mpz_get_str(av, 16, A);

    Fp_set_str(&c.element[1], av);

    printf("A = ");
    Fp2_print(&a);

    printf("B = ");
    Fp2_print(&c);

    if(Fp2_cmp_n(&a, &c) == 1){
        printf("Aの方が大きい\n");
    }else{
        if(Fp2_cmp_n(&a, &c) == -1){
            printf("Bの方が大きい\n");
        }else{
            printf("A == B\n");
        }
    }
}