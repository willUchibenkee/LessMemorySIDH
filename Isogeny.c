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

int ea, eb;

void Isogeny_set_a0(void){

    Fp2_set_str(&Aa0, aa0);
    Fp2_set_str(&Ba0, ba0);
 
}

void Isogeny_set_e(void){
    ea = 
    Fp_set_str(&ea, eA);
    Fp_set_str(&eb, eB);
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
    Fp2_to_Mont(alpha, alpha);

    Fp2_mul(&temp, alpha, alpha);
    Fp2_mul(&temp, &temp, &two);
    Fp2_sub(&temp, &one, &temp);
    Fp2_mul(nexta, &two, &temp);

    free(&one);
    free(&two);
    free(&temp);
    Fp2_from_Mont(nexta);
}

void Isogeny_changeb(Fp2 *nexta, Fp2 *beta, Fp2 *olda){
    Fp2 six;
    Fp2_set_ui(&six, "6 0");

    Fp2 temp; 
    Fp2 temp2;

    Fp2_to_Mont(olda, olda);
    Fp2_to_Mont(beta, beta);

    Fp2_mul(&temp, olda, beta);
    Fp2_mul(&temp2, &six, beta);
    Fp2_mul(&temp2, &temp2, beta);
    Fp2_sub(&temp, &temp, &temp2);
    Fp2_add(&temp, &temp, &six);
    Fp2_mul(&temp, &temp, beta);

    Fp2_set(nexta, &temp);
    Fp2_from_Mont(nexta);
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

    Fp2_to_Mont(alpha, alpha);
    Fp2_to_Mont(&P->x, &P->x);
    Fp2_to_Mont(&P->y, &P->y);

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
        Fp2_from_Mont(&ans->x);
        
    }else{
        //bob

        Fp three;
        Fp_set_str(&three, "3");
        
        Fp2 one; 
        Fp2_set_ui(&one, "1 0");

        //
        Fp2_mul(&temp, alpha, &P->x);
        Fp2_sub(&temp, &temp, &one);
        Fp2_mul(&temp, &temp, &temp);
        Fp2_mul(&temp, &temp, &P->x);
        

        //
        Fp2_sub(&bumbo, &P->x, alpha);
        Fp2_mul(&bumbo, &bumbo, &bumbo);
        Fp2_inv(&bumbo, &bumbo);
        

        //
        Fp2_mul(&U.x, &temp, &bumbo);

        //
        Fp2_set(&ans->x, &U.x);
        Fp2_from_Mont(&ans->x);

    }
}

void isogeny_mgec3(ec2 *R, ec2 *P, fp2 *ap){
    ec2 U; 
    
    Fp2 temp, temp2, temp3; 

    Fp four, three;
    Fp_set_str(&four, "4");
    Fp_set_str(&three, "3");

    Fp2 six, four2, three2, one;
    
    Fp2_set_str(&six, "6 0");
    Fp2_set_str(&four2, "4 0");
    Fp2_set_str(&three2, "3 0");
    Fp2_set_str(&one, "1 0");

    Fp2_to_Mont(&P->x, &P->x);
    Fp2_to_Mont(&P->y, &P->y);
    Fp2_to_Mont(ap, ap);

    Fp2 bunshi, bumbo;

    Fp2_mul(&temp, &P->x, &P->x);
    Fp2_mul(&temp, &temp, &P->x);
    Fp2_mul(&temp, &temp, &P->x);
    //x^4

    Fp2_mul(&temp2, &six, &P->x);
    Fp2_mul(&temp2, &temp2, &P->x);
    //6x^2

    
    Fp2_mul(&temp3, &P->x, &four2);
    Fp2_mul(&temp3, &temp3, &A);
    //4ax^3

    Fp2_sub(&temp, &temp, &temp2);
    Fp2_sub(&temp, &temp, &temp3);
    Fp2_sub(&temp, &temp, &three2);
    //()

    Fp2_mul(&temp, &temp, &temp);
    //()^2

    Fp2_mul(&temp, &temp, &P->x);
    //x*()^2

    Fp2_set(&bunshi, &temp);


    Fp2_mul(&temp, &P->x, &P->x);
    Fp2_mul(&temp, &temp, &P->x);
    Fp2_mul(&temp, &temp, &P->x);
    Fp2_mul(&temp, &temp, &three2);
    //3x^4

    Fp2_mul(&temp3, &P->x, &P->x);
    Fp2_mul(&temp3, &temp3, &P->x);
    Fp2_mul(&temp3, &temp3, &four2);
    Fp2_mul(&temp3, &temp3, &A);
    //4ax^3
    
    Fp2_add(&temp, &temp, &temp2);
    Fp2_add(&temp, &temp, &temp3);
    Fp2_sub(&temp, &temp, &one);
    //()

    Fp2_mul(&temp, &temp, &temp);
    //()^2

    Fp2_inv(&temp, &temp);
    // /

    Fp2_set(&bumbo, &temp);

    Fp2_mul(&U.x, &bunshi, &bumbo);
    
    Fp2_set(&R->x, &U.x);
    Fp2_from_Mont(&R->x);
}