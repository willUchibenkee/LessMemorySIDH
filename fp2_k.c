//fp2_k.c(Montgomery)

#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>
#include<stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include<time.h>
#include"fp2.h"

#define TIMES 200

void check_fp2();

void check_fp2_34();

void check_fp2_cmp();

int main(void){
    mpz_init(prime_z);
    // mpz_set_ui(prime_z, p);
    mpz_set_str(prime_z,"0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",16);
    gmp_printf("prime:%Zd",prime_z);
    for(int g = 0; g < TIMES; g++){
        // check_fp2_34();
        //check_fp2_cmp();
        check_fp2();
        getchar();
    }


    return 0;
}

void check_fp2(){

    printf("check_fp2() 開始\n");

    fp2 A,ANS,fp2_order;

    fp2_init(&A);

    fp2_init(&ANS);

    gmp_randstate_t state;

    gmp_randinit_default(state);

    gmp_randseed_ui(state,(unsigned long int)time(NULL));

    mpz_urandomm(A.x0, state, prime_z);
    mpz_urandomm(A.x1, state, prime_z);
    
    printf("A = ");
    fp2_printf(&A);

    fp2_inv(&ANS,&A);
    printf("A^-1 = ");
    fp2_printf(&ANS);

    fp2_mul(&ANS,&ANS,&A);

    printf("A * A^-1 = ");
    fp2_printf(&ANS);

    printf("---------------------------------\n");

    printf("平方根アルゴリズムの確認\n");

    int flag=fp2_legendre(&A);

    printf("fp2_legendre(A) = %d\n",flag);

    if(flag==1){

    fp2_sqrt(&ANS,&A);

    printf("fp2_sqrt(A) = ");
    fp2_printf(&ANS);

    fp2_mul(&ANS,&ANS,&ANS);

        if(fp2_cmp(&ANS,&A)==0){

            printf("(fp2_sqrt(A))^2 = A\n\n");

        }else{

            printf("(fp2_sqrt(A))^2 != A\n\n");
        }
    }
        printf("---------------------------------\n");

    printf("フェルマーの小定理の確認\n");

    mpz_t tmp;

    mpz_init(tmp);

    mpz_pow_ui(tmp, prime_z ,2);

    mpz_sub_ui(tmp,tmp,1);

    fp2_scalarexp(&ANS,&A,tmp);

    printf("A^(p^2-1) = ");
    fp2_printf(&ANS);

    printf("---------------------------------\n");
    printf("A = ");
    fp2_printf(&A);//Aが変わっていないことの確認
    printf("*********************************************************************************************\n\n");

}

void check_fp2_34(){

    printf("check_fp2() 開始\n");

    fp2 A,ANS;

    fp2_init(&A);

    fp2_init(&ANS);

    fp2 alpha;

    fp2_init(&alpha);

    gmp_randstate_t state;

    mpz_t m, bai;

    mpz_init(bai);

    mpz_init(m);

    mpz_set_ui(bai, 185760);

    gmp_randinit_default(state);

    gmp_randseed_ui(state,(unsigned long int)time(NULL));

    mpz_set_ui(m, 430);

    mpz_urandomm(A.x0, state, m);
    mpz_urandomm(A.x1, state, m);

    // A = 58
    // A = 387
    // A = 3a 183

    // mpz_set_ui(A.x0, 58);
    // mpz_set_ui(A.x1, 387);

    //fp2_set_ui(&A, 6, 310);
    //358i + 275, 410i + 104
    // fp2_set_ui(&alpha, 37, 18);  

    // fp2_sub(&A, &A, &alpha);

    // fp2_mul(&A, &A, &A);

    printf("A = ");
    fp2_printf(&A);

    // fp2_scalarexp(&ANS, &A, bai);
    // printf("A**p*p-1:");
    // fp2_printf(&ANS);

    fp2_inv(&ANS,&A);

    printf("A^-1 = ");
    fp2_printf(&ANS);

    fp2_mul(&ANS,&ANS,&A);

    printf("A * A^-1 = ");
    fp2_printf(&ANS);

    printf("---------------------------------\n");

    printf("平方根アルゴリズムの確認\n");

    int flag=fp2_legendre(&A);

    printf("fp2_legendre(A) = %d\n",flag);

    if(flag==1){

    fp2_sqrt_34(&ANS,&A);

    printf("fp2_sqrt(A) = ");
    fp2_printf(&ANS);

    fp2_mul(&ANS,&ANS,&ANS);

    if(fp2_cmp(&ANS,&A)==0){

        printf("(fp2_sqrt(A))^2 = A\n");

    }else{

        printf("(fp2_sqrt(A))^2 != A\n");
        fp2_printf(&ANS);
    }

    printf("---------------------------------\n");

    printf("フェルマーの小定理の確認\n");

    mpz_t tmp;

    mpz_init(tmp);

    mpz_pow_ui(tmp, prime_z ,430);

    mpz_sub_ui(tmp,tmp,1);

    fp2_scalarexp(&ANS,&A,tmp);

    printf("A^(p^430-1) = ");
    fp2_printf(&ANS);

    printf("---------------------------------\n");

    printf("A = ");
    fp2_printf(&A);//Aが変わっていないことの確認



    printf("*********************************************************************************************\n\n");

    }
}
