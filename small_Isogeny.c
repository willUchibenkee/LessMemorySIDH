//isogeny.c   このプログラムの名前
#include<stdio.h>
#include<stdlib.h>
#include"small_Efp2.c"
#include<gmp.h>

#define aa0 "1a7 149"
#define ba0 "1a7 149"
#define ka "B"
#define kb "2"
#define eA 4 //216
#define eB 3 //137
#define la 2
#define lb 3

Fp2 aA0;
Fp2 bA0;

int ea, eb;

void Isogeny_set_a0(void){

    Fp2_set_str(&aA0, Aval);
    Fp2_set_str(&bA0, Aval);
 
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
    U.inf = 0;

    // printf("k: ");
    // Fp_print(k);
    // printf("Qx: ");
    // Fp2_print(xcoord(Q));
    // printf("Qy: ");
    // Fp2_print(ycoord(Q));
    // printf("A: ");
    // Fp2_print(ap);
    Efp2_mgecSCM(&U, Q, k, ap);
    // printf("kQ:");
    // Fp2_from_Mont(&U.x);
    // Fp2_from_Mont(&U.y);
    // Efp2_PrintEC2(&U);
    // Fp2_to_Mont(&U.x, &U.x);
    // Fp2_to_Mont(&U.y, &U.y);
    Efp2_mgecA(S, P, &U, ap);

    //free(&U);
}

void Isogeny_changea(Fp2 *nexta, Fp2 *alpha){
    Fp2 one, two;
    Fp2_set_str(&one, "91 0");
    Fp2_set_str(&two, "122 0");
    Fp2 temp;
    //Fp2_to_Mont(alpha, alpha);

    Fp2_mul(&temp, alpha, alpha);
    // printf("alpha**2: ");
    // Fp2_print_s(&temp);
    Fp2_mul(&temp, &temp, &two);
    // printf("2*alpha**2: ");
    // Fp2_print_s(&temp);
    Fp2_sub(&temp, &one, &temp);
    // printf("2*alpha**2 - 1: ");
    // Fp2_print_s(&temp);
    Fp2_mul(nexta, &two, &temp);
    // printf("nexta: ");
    // Fp2_print_s(nexta);

    // free(&one);
    // free(&two);
    // free(&temp);
    //Fp2_from_Mont(nexta);
}

void Isogeny_changeb(Fp2 *nexta, Fp2 *beta, Fp2 *olda){
    Fp2 six;
    Fp2_set_str(&six, "8 0");

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
    ec2 U, V; 

    Fp2 temp; 
    Fp2 bumbo; 
    Fp2 temp2; 

    Fp2 two; 
    Fp2_set_str(&two, "122 0");

    Fp2_set(&U.x, &P->x);
    Fp2_set(&U.y, &P->y);
    U.inf = 0;
    V.inf = 0;
    Fp2_set_str(&V.x, "0 0");
    Fp2_set_str(&V.y, "0 0");

    if(l == 2){
        //alice       
        //分子 xp px x2 alpha
        
        Fp2_mul(&temp, &U.x, &U.x);
        Fp2_mul(&temp, &temp, alpha);
        Fp2_sub(&temp, &temp, &U.x);
        

        //分母
        Fp2_sub(&bumbo, &U.x, alpha);
        
        Fp2_inv(&bumbo, &bumbo);

        
        //掛け算
        Fp2_mul(&V.x, &temp, &bumbo);
        
        //set
        Fp2_set(&ans->x, &V.x);
        //Fp2_from_Mont(&ans->x);

        //y 分子 xP**2* alpha − 2*xP*alpha**2 + alpha
        Fp2_mul(&temp, &U.x, &U.x);
        Fp2_mul(&temp, &temp, alpha);
        Fp2_sub(&temp, &temp, &U.x);

        Fp2_mul(&temp2, &two, &U.x);
        Fp2_mul(&temp2, &temp2, alpha);
        Fp2_mul(&temp2, &temp2, alpha);

        Fp2_sub(&temp, &temp, &temp2);

        Fp2_add(&temp, &temp, alpha);

        //分母　(xP − alpha)**2
        Fp2_sub(&bumbo, &U.x, alpha);
        Fp2_mul(&bumbo, &bumbo, &bumbo);

        Fp2_inv(&bumbo, &bumbo);

        Fp2_mul(&temp, &temp, &bumbo);
        Fp2_mul(&V.y, &temp, &U.y);

        Fp2_set(&ans->y, &V.y);
        
    }else{
        //bob

        Fp2 three;
        Fp2_set_str(&three, "4 0");
        
        Fp2 one, temp3; 
        Fp2_set_str(&one, "91 0");
        // Fp2 temp; 
        // Fp2 bumbo; 
        // Fp2 temp2;

        //
        Fp2_mul(&temp, alpha, &U.x);
        Fp2_sub(&temp, &temp, &one);
        Fp2_mul(&temp, &temp, &temp);
        Fp2_mul(&temp, &temp, &U.x);
        
        //
        Fp2_sub(&bumbo, &U.x, alpha);
        Fp2_mul(&bumbo, &bumbo, &bumbo);
        Fp2_inv(&bumbo, &bumbo);
        

        //
        Fp2_mul(&V.x, &temp, &bumbo);

        //
        Fp2_set(&ans->x, &V.x);

        //y 分子 (xP*a − 1)(xP**2*a − 3*xP*a**3 + xP + a)
        // printf("alpha:");
        // Fp2_print_s(alpha);
        // printf("U:");
        // Efp2_PrintEC2_s(&U);

        Fp2_mul(&temp, &U.x, alpha);
        Fp2_sub(&temp, &temp, &one);

        //////////////////////////////////////

        Fp2_mul(&temp2, &U.x, alpha);
        Fp2_mul(&temp2, &temp2, &U.x);

        Fp2_mul(&temp3, &three, &U.x);
        Fp2_mul(&temp3, &temp3, alpha);
        Fp2_mul(&temp3, &temp3, alpha);

        Fp2_sub(&temp2, &temp2, &temp3);

        Fp2_add(&temp2, &temp2, &U.x);

        Fp2_add(&temp2, &temp2, alpha);

        ///////////////////////////////////////

        Fp2_mul(&temp, &temp, &temp2);

        //分母 (xP − x3)3
        Fp2_sub(&temp3, &U.x, alpha);
        Fp2_mul(&bumbo, &temp3, &temp3);
        Fp2_mul(&bumbo, &bumbo, &temp3);

        Fp2_inv(&bumbo, &bumbo);

        ///////////////////////////////////////

        Fp2_mul(&V.y, &temp, &bumbo);

        Fp2_mul(&V.y, &V.y, &U.y);

        Fp2_set(&ans->y, &V.y);

    }
}

// void Isogeny_mgec3(ec2 *R, ec2 *P, Fp2 *ap){
//     ec2 U; 
    
//     Fp2 temp, temp2, temp3; 

//     // Fp four, three;
//     // Fp_set_str(&four, "95");
//     // Fp_set_str(&three, "3");

//     Fp2 six, four2, three2, one;
    
//     Fp2_set_str(&six, "8 0");
//     Fp2_set_str(&four2, "95 0");
//     Fp2_set_str(&three2, "4 0");
//     Fp2_set_str(&one, "91 0");

//     Fp2_to_Mont(&P->x, &P->x);
//     Fp2_to_Mont(&P->y, &P->y);
//     Fp2_to_Mont(ap, ap);

//     Fp2 bunshi, bumbo;

//     Fp2_mul(&temp, &P->x, &P->x);
//     Fp2_mul(&temp, &temp, &P->x);
//     Fp2_mul(&temp, &temp, &P->x);
//     //x^4

//     Fp2_mul(&temp2, &six, &P->x);
//     Fp2_mul(&temp2, &temp2, &P->x);
//     //6x^2

    
//     Fp2_mul(&temp3, &P->x, &four2);
//     Fp2_mul(&temp3, &temp3, &A);
//     //4ax^3

//     Fp2_sub(&temp, &temp, &temp2);
//     Fp2_sub(&temp, &temp, &temp3);
//     Fp2_sub(&temp, &temp, &three2);
//     //()

//     Fp2_mul(&temp, &temp, &temp);
//     //()^2

//     Fp2_mul(&temp, &temp, &P->x);
//     //x*()^2

//     Fp2_set(&bunshi, &temp);


//     Fp2_mul(&temp, &P->x, &P->x);
//     Fp2_mul(&temp, &temp, &P->x);
//     Fp2_mul(&temp, &temp, &P->x);
//     Fp2_mul(&temp, &temp, &three2);
//     //3x^4

//     Fp2_mul(&temp3, &P->x, &P->x);
//     Fp2_mul(&temp3, &temp3, &P->x);
//     Fp2_mul(&temp3, &temp3, &four2);
//     Fp2_mul(&temp3, &temp3, &A);
//     //4ax^3
    
//     Fp2_add(&temp, &temp, &temp2);
//     Fp2_add(&temp, &temp, &temp3);
//     Fp2_sub(&temp, &temp, &one);
//     //()

//     Fp2_mul(&temp, &temp, &temp);
//     //()^2

//     Fp2_inv(&temp, &temp);
//     // /

//     Fp2_set(&bumbo, &temp);

//     Fp2_mul(&U.x, &bunshi, &bumbo);
    
//     Fp2_set(&R->x, &U.x);
//     Fp2_from_Mont(&R->x);
// }