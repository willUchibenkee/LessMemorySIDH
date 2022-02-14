// yiso2.c

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

void isoy2(ec2 *ANS, ec2 *P, fp2 *alpha);

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

    fp2_set_ui(&P.x, 275, 358);
    fp2_set_ui(&P.y, 104, 410);

    //358i + 275, 410i + 104

    fp2_set_ui(&alpha, 37, 18);

    //18i +37

    isoy2(&ans, &P, &alpha);

    printf("Pb': ");
    PrintEC2(&ans);

    //118i+85, 274i+150

    return 0;
}

void isoy2(ec2 *ANS, ec2 *P, fp2 *alpha){
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

    fp2_mul(tempp, &U.x, &U.x);
    fp2_mul(tempp, tempp, alpha);
    fp2_sub(tempp, tempp, &U.x);
    //fp2_printff(tempp);

    //分母
    fp2_sub(bumbop, &P->x, alpha);
    //fp2_printff(bumbop);
    fp2_inv(bumbop, bumbop);

    //掛け算
    fp2_mul(&V.x, tempp, bumbop);

    //set
    fp2_set(&ANS->x, &V.x);
    //fp2_set(&ans->y,&Up->y);

    //y 分子 xP**2* alpha − 2*xP*alpha**2 + alpha
    //x**2 * alpha
    fp2_mul(&temp, &U.x, &U.x);
    fp2_mul(&temp, &temp, alpha);

    //fp2_sub(&temp, &temp, &U.x);

    fp2_add(&temp2, &U.x, &U.x);
    fp2_mul(&temp2, &temp2, alpha);
    fp2_mul(&temp2, &temp2, alpha);

    fp2_sub(&temp, &temp, &temp2);

    fp2_add(&temp, &temp, alpha);

    //分母　(xP − alpha)**2
    fp2_sub(&bumbo, &U.x, alpha);
    fp2_mul(&bumbo, &bumbo, &bumbo);

    printf("bumbo:");
    fp2_printf(&bumbo);

    fp2_inv(&bumbo, &bumbo);

    printf("bumbo inv:");
    fp2_printf(&bumbo);

    fp2_mul(&temp, &temp, &bumbo);
    fp2_mul(&V.y, &temp, &U.y);

    fp2_set(&ANS->y, &V.y);
}