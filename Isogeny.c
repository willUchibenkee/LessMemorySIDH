//isogeny.h   このプログラムの名前
#include<stdio.h>
#include<stdlib.h>
#include"Efp2.c"
#include<gmp.h>

#define aa0 "0000F37AB34BA0CEAD94F43CDC50DE06AD19C67CE4928346E829CB92580DA84D7C36506A2516696BBE3AEB523AD7172A6D239513C5FD2516 000196CA2ED06A657E90A73543F3902C208F410895B49CF84CD89BE9ED6E4EE7E8DF90B05F3FDB8BDFE489D1B3558E987013F9806036C5AC"
#define ba0 "0001CD28597256D4FFE7E002E87870752A8F8A64A1CC78B5A2122074783F51B4FDE90E89C48ED91A8F4A0CCBACBFA7F51A89CE518A52B76C 000147073290D78DD0CC8420B1188187D1A49DBFA24F26AAD46B2D9BB547DBB6F63A760ECB0C2B20BE52FB77BD2776C3D14BCBC404736AE4"
#define ka 11
#define kb 2
#define eA "000000D8"
#define eB "00000089"
#define la 2
#define lb 3

Fp2 aA0;
Fp2 bA0;

int ea;
int eb;

void Isogeny_set_a0(void){

    mpz_set_str(aa0.x0, aa0x0, 16);
    //printf("x\n");
    mpz_set_str(ba0.x0, ba0x0, 16);
    //printf("y\n");
    mpz_set_str(aa0.x1, aa0x1, 16);
    //printf("u\n");
    mpz_set_str(ba0.x1, ba0x1, 16);
    //printf("v\n");
}

void Isogeny_set_e(void){
    mpz_init(ea);
    mpz_init(eb);
    mpz_set_str(ea, eA, 16);
    mpz_set_str(eb, eB, 16);
}

void Isogeny_gets(ec2 *S, ec2 *P, ec2 *Q, int k, Fp2 *ap){
    // SaやSbを求めます
    //Sa = Pa + ka*Qa
    ec2 U; 

    Fp2_mgecSCM(&U, Q, k, ap);
    Fp2_mgecA(S, P, &U, ap);

    free(&U);
}

void isogeny_changea(Fp2 *nexta, Fp2 *alpha){
    Fp2 one, two;
    Fp2_set_ui(&one, "1 0");
    Fp2_set_ui(&two, "2 0");
    Fp2 temp;

    Fp2_mul(&temp, alpha, alpha);
    Fp2_mul(&temp, &temp, &two);
    Fp2_sub(&temp, &one, &temp);
    Fp2_mul(nexta, &two, &temp);

    free(&one);
    free(&two);
    free(&temp);
}

void Isogeny_changeb(Fp2 *nexta, Fp2 *beta, Fp2 *olda){
    Fp2 six;
    Fp2_set_ui(&six, "6 0");

    Fp2 temp; 
    Fp2 temp2; 

    Fp2_mul(&temp, olda, beta);
    Fp2_mul(&temp2, &six, beta);
    Fp2_mul(&temp2, &temp2, beta);
    Fp2_sub(&temp, &temp, &temp2);
    Fp2_add(&temp, &temp, &six);
    Fp2_mul(&temp, &temp, beta);

    Fp2_set(nexta, &temp);
}

void Isogeny_nextp(ec2 *ans, ec2 *P, Fp2 *alpha, int l){
    //同種写像Φを求めます
    //P...点 alpha...スタート地点 l...AliceですかBobですか
    ec2 U; 

    Fp2 temp; 
    Fp2 bumbo; 
    Fp2 temp2; 

    Fp2 two; 
    Fp2_set_ui(&two, "2 0");

    if(l == 2){
        //alice       
        //分子
        
        Fp2_mul(&temp, &P->x, &P->x);
        Fp2_mul(&temp, &temp, alpha);
        Fp2_sub(&temp, &temp, &P->x);
        

        //分母
        Fp2_sub(&bumbo, &P->x, alpha);
        
        Fp2_inv(&bumbo, &bumbo);

        
        //掛け算
        Fp2_mul(&U.x, &temp, &bumbo);

        
        //set
        Fp2_set(&ans->x,&U.x);
        
    }else{
        //bob

        mpz_t three;
        mpz_init(three);
        mpz_set_ui(three, 3);

        
        fp2 one; 
        fp2_init(&one);
        fp2_set_ui(&one, 1, 0);

        //
        fp2_mul(&temp, alpha, &P->x);
        fp2_sub(&temp, &temp, &one);
        fp2_mul(&temp, &temp, &temp);
        fp2_mul(&temp, &temp, &P->x);
        

        //
        fp2_sub(&bumbo, &P->x, alpha);
        fp2_mul(&bumbo, &bumbo, &bumbo);
        fp2_inv(&bumbo, &bumbo);
        

        //
        fp2_mul(&U.x, &temp, &bumbo);

        //
        fp2_set(&ans->x, &U.x);

    }
}

void isogeny_mgec3(ec2 *R, ec2 *P, fp2 *ap){
    ec2 U; 
    fp2_init(&U.x);
    fp2_init(&U.y);
    mpz_init(U.inf);
    
    fp2 temp; 
    fp2_init(&temp);
    fp2 temp2; 
    fp2_init(&temp2);
    fp2 temp3; 
    fp2_init(&temp3);

    mpz_t four, three;
    mpz_init(four);
    mpz_init(three);
    mpz_set_ui(four, 4);
    mpz_set_ui(three, 3);

    fp2 six, four2, three2, one;
    
    fp2_init(&six);
    fp2_init(&four2);
    fp2_init(&three2);
    fp2_init(&one);
    fp2_set_ui(&six, 6, 0);
    fp2_set_ui(&four2, 4, 0);
    fp2_set_ui(&three2, 3, 0);
    fp2_set_ui(&one, 1, 0);

    fp2 bunshi, bumbo;
    
    fp2_init(&bunshi);
    fp2_init(&bumbo);

    fp2_scalarexp(&temp, &P->x, four);
    //x^4

    fp2_mul(&temp2, &six, &P->x);
    fp2_mul(&temp2, &temp2, &P->x);
    //6x^2

    
    fp2_mul(&temp3, &P->x, &four2);
    fp2_mul(&temp3, &temp3, &A);
    //4ax^3

    fp2_sub(&temp, &temp, &temp2);
    fp2_sub(&temp, &temp, &temp3);
    fp2_sub(&temp, &temp, &three2);
    //()

    fp2_mul(&temp, &temp, &temp);
    //()^2

    fp2_mul(&temp, &temp, &P->x);
    //x*()^2

    fp2_set(&bunshi, &temp);




    fp2_scalarexp(&temp, &P->x, four);
    fp2_mul(&temp, &temp, &three2);
    //3x^4

    fp2_scalarexp(&temp3, &P->x, three);
    fp2_mul(&temp3, &temp3, &four2);
    fp2_mul(&temp3, &temp3, &A);
    //4ax^3
    
    fp2_add(&temp, &temp, &temp2);
    fp2_add(&temp, &temp, &temp3);
    fp2_sub(&temp, &temp, &one);
    //()

    fp2_mul(&temp, &temp, &temp);
    //()^2

    fp2_inv(&temp, &temp);
    // /

    fp2_set(&bumbo, &temp);

    fp2_mul(&U.x, &bunshi, &bumbo);
    
    fp2_set(&R->x, &U.x);
}