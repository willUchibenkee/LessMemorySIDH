#include<stdio.h>
#include<stdlib.h>
#include"efp2.h"
#include<gmp.h>

#define a0x0 423
#define a0x1 329
#define ka 11
#define kb 2
#define eA 4
#define eB 3
#define la 2
#define lb 3

void y3isogeny(ec2 *ans, ec2 *P, fp2 *alpha);

int main(void){
    ec2 P, ans;
    fp2 alpha;

    fp2_init(&ans.x);
    fp2_init(&ans.y);

    fp2_init(&P.x);
    fp2_init(&P.y);

    fp2_init(&alpha);

    mpz_init(P.inf);
    mpz_init(ans.inf);

    fp2_set_ui(&P.x, 248, 100);
    fp2_set_ui(&P.y, 199, 304);

    //100i + 248, 304i + 199

    fp2_set_ui(&alpha, 37, 23);

    y3isogeny(&ans, &P, &alpha);

    printf("Pa': ");
    PrintEC2(&ans);

    //418i + 155, 288i + 331

    return 0;
}

void y3isogeny(ec2 *ans, ec2 *P, fp2 *alpha){
    ec2 U,V; 
    fp2_init(&U.x);
    fp2_init(&U.y);
    mpz_init(U.inf);

    fp2_set(&U.x, &P->x);
    fp2_set(&U.y, &P->y);
    mpz_set(U.inf, P->inf);

    fp2_init(&V.x);
    fp2_init(&V.y);
    mpz_init(V.inf);

    fp2 temp; fp2 *tempp;
    tempp = &temp;
    fp2_init(tempp);

    fp2 bumbo; fp2 *bumbop;
    bumbop = &bumbo;
    fp2_init(bumbop);

    fp2 temp2; fp2 *temp2p;
    temp2p = &temp2;
    fp2_init(temp2p);

    fp2 two; fp2 *t2p;
    t2p = &two;
    fp2_init(t2p);
    fp2_set_ui(t2p, 2, 0);

    mpz_t three;
    mpz_init(three);
    mpz_set_ui(three, 3);

    //printf("bob\n");

    fp2 one, temp3, temp4; 
    fp2 *onep;
    onep = &one;
    fp2_init(onep);
    fp2_set_ui(onep, 1, 0);
    fp2_init(&temp3);
    fp2_init(&temp4);

    //x 

    fp2_mul(tempp, alpha, &U.x);
    fp2_sub(tempp, tempp, onep);
    fp2_mul(tempp, tempp, tempp);
    fp2_mul(tempp, tempp, &U.x);
    //fp2_printff(tempp);

    //
    fp2_sub(bumbop, &U.x, alpha);
    fp2_mul(bumbop, bumbop, bumbop);
    fp2_inv(bumbop, bumbop);
    //fp2_printff(bumbop);

    //
    fp2_mul(&V.x, tempp, bumbop);

    //
    fp2_set(&ans->x, &V.x);

    //y

    fp2_init(&temp);
    fp2_init(&temp2);
    fp2_init(&temp3);
    fp2_init(&temp4);
    fp2_init(&bumbo);
    
    printf("U:");
    PrintEC2(&U);

    printf("alpha:");
    fp2_printf(alpha);

    printf("one:");
    fp2_printf(onep);

    //(x*a − 1)

    fp2_mul(&temp, &U.x, alpha);

    fp2_sub(&temp, &temp, onep);

    printf("zenhan:");
    fp2_printf(&temp);

    //////////////////////////////////////

    //x**2*a

    fp2_mul(&temp2, &U.x, alpha);
    fp2_mul(&temp2, &temp2, &U.x);

    printf("x**2 * a:");
    fp2_printf(&temp2);

    //x*a**2

    fp2_mul(&temp3, &U.x, alpha);
    fp2_mul(&temp3, &temp3, alpha);

    printf("x * a**2 :");
    fp2_printf(&temp3);

    //3*

    fp2_add(&temp4, &temp3, &temp3);
    fp2_add(&temp4, &temp4, &temp3);
    // fp2 t3;
    // fp2_init(&t3);
    // fp2_set_ui(&t3, 3, 0);
    // fp2_mul(&temp4, &temp3, &t3);

    printf("3 * x * a**2 :");
    fp2_printf(&temp4);

    fp2_sub(&temp2, &temp2, &temp4);

    printf("x * a**2 - 3 * x * a**2:");
    fp2_printf(&temp2);

    fp2_add(&temp2, &temp2, &U.x);

    printf("x * a**2 - 3 * x * a**2 + x:");
    fp2_printf(&temp2);

    fp2_add(&temp2, &temp2, alpha);

    printf("kouhan:");
    fp2_printf(&temp2);

    ///////////////////////////////////////

    fp2_mul(&temp, &temp, &temp2);

    printf("bunshi:");
    fp2_printf(&temp);

    fp2_init(&temp3);

    //分母 (xP − x3)3
    fp2_sub(&temp3, &U.x, alpha);

    printf("x - a:");
    fp2_printf(&temp3);

    fp2_mul(&bumbo, &temp3, &temp3);
    fp2_mul(&bumbo, &bumbo, &temp3);
    // fp2_scalarexp(&bumbo, &temp3, three);

    printf("bumbo:");
    fp2_printf(&bumbo);

    fp2_inv(&bumbo, &bumbo);

    printf("inv bumbo:");
    fp2_printf(&bumbo);

    ///////////////////////////////////////

    fp2_mul(&V.y, &temp, &bumbo);

    printf("bunsuu:");
    fp2_printf(&V.y);

    fp2_mul(&V.y, &V.y, &U.y);

    printf("bunsuu * Py:");
    fp2_printf(&V.y);

    fp2_set(&ans->y, &V.y);
}