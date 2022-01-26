//isogeny.c   このプログラムの名前
#include<stdio.h>
#include<stdlib.h>
#include"small_Efp2.c"
#include<gmp.h>

#define aa0 "329 423"
#define ba0 "329 423"
#define ka "0xB"
#define kb "0x2"
#define eA 4 //216
#define eB 3 //137
#define la 2
#define lb 3

Fp2 aA0;
Fp2 bA0;

int ea, eb;

void Isogeny_set_a0(void){

    Fp2_set_str(&aA0, aa0);
    Fp2_set_str(&bA0, ba0);
 
}

void Isogeny_set_e(void){
    //ea = 
    // Fp_set_str(&ea, eA);
    // Fp_set_str(&eb, eB);
    ea = eA;
    eb = eB;
}

void Isogeny_gets(ec2 *S, ec2 *P, ec2 *Q, Fp *k, Fp2 *ap){
    // SaやSbを求めます
    //Sa = Pa + ka*Qa
    ec2 U; 

    Efp2_mgecSCM(&U, Q, k, ap);
    Efp2_mgecA(S, P, &U, ap);

    //free(&U);
}

void Isogeny_changea(Fp2 *nexta, Fp2 *alpha){
    Fp2 one, two;
    Fp2_set_str(&one, "1 0");
    Fp2_set_str(&two, "2 0");
    Fp2 temp;
    Fp2_to_Mont(alpha, alpha);

    Fp2_mul(&temp, alpha, alpha);
    Fp2_mul(&temp, &temp, &two);
    Fp2_sub(&temp, &one, &temp);
    Fp2_mul(nexta, &two, &temp);

    // free(&one);
    // free(&two);
    // free(&temp);
    Fp2_from_Mont(nexta);
}

void Isogeny_changeb(Fp2 *nexta, Fp2 *beta, Fp2 *olda){
    Fp2 six;
    Fp2_set_str(&six, "6 0");

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
    Fp2_set_str(&two, "2 0");

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
        Fp2_set_str(&one, "1 0");

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

void Isogeny_mgec3(ec2 *R, ec2 *P, Fp2 *ap){
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