//isogeny.h   このプログラムの名前
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

void isogeny_gets(ec2 *S, ec2 *P, ec2 *Q, mpz_t k, fp2 *ap){
    // SaやSbを求めます
    //Sa = Pa + ka*Qa
    ec2 U; ec2 *up;
    up = &U;
    fp2_init(&up->x);
    fp2_init(&up->y);
    mpz_init(up->inf);
    fp2_mgecSCM(up, Q, k, ap);
    printf("kQ:");
    PrintEC2(up);
    fp2_mgecA(S, P, up, ap);
}

void isogeny_changea(fp2 *nexta, fp2 *alpha){
    fp2 one, two;
    fp2 *onep; fp2 *twop;
    onep = &one; twop = &two;
    fp2_init(onep);
    fp2_init(twop);
    fp2_set_ui(onep, 1, 0);
    fp2_set_ui(twop, 2, 0);
    fp2 temp;
    fp2 *tempp;
    tempp = &temp;
    fp2_init(tempp);

    fp2_mul(tempp, alpha, alpha);
    fp2_mul(tempp, tempp, twop);
    fp2_sub(tempp, onep, tempp);
    fp2_mul(nexta, twop, tempp);
}

void isogeny_changeb(fp2 *nexta, fp2 *beta, fp2 *olda){
    fp2 six; fp2 *sixp;
    sixp = &six;
    fp2_init(sixp);
    fp2_set_ui(sixp, 6, 0);

    fp2 temp; fp2 * tempp;
    tempp = &temp;
    fp2_init(tempp);

    fp2 temp2; fp2 * temp2p;
    temp2p = &temp2;
    fp2_init(temp2p);

    fp2_mul(tempp, olda, beta);
    fp2_mul(temp2p, sixp, beta);
    fp2_mul(temp2p, temp2p, beta);
    fp2_sub(tempp, tempp, temp2p);
    fp2_add(tempp, tempp, sixp);
    fp2_mul(tempp, tempp, beta);

    fp2_set(nexta, tempp);
}

void isogeny_nextp(ec2 *ans, ec2 *P, fp2 *alpha, mpz_t l){
    //同種写像Φを求めます
    //P...点 alpha...スタート地点 l...AliceですかBobですか
    ec2 U; ec2 *Up;
    Up = &U;
    fp2_init(&Up->x);
    fp2_init(&Up->y);
    mpz_init(Up->inf);

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

    if(mpz_cmp_ui(l,2) == 0){
        //alice       
        //分子
        //printf("alice\n");
        fp2_mul(tempp, &P->x, &P->x);
        fp2_mul(tempp, tempp, alpha);
        fp2_sub(tempp, tempp, &P->x);
        //fp2_printf(tempp);

        //分母
        fp2_sub(bumbop, &P->x, alpha);
        //fp2_printf(bumbop);
        fp2_inv(bumbop, bumbop);

        //掛け算
        fp2_mul(&Up->x, tempp, bumbop);

        //set
        fp2_set(&ans->x,&Up->x);
        //fp2_set(&ans->y,&Up->y);

    }else{
        //bob

        mpz_t three;
        mpz_init(three);
        mpz_set_ui(three, 3);

        //printf("bob\n");

        fp2 one; fp2 *onep;
        onep = &one;
        fp2_init(onep);
        fp2_set_ui(onep, 1, 0);

        //
        fp2_mul(tempp, alpha, &P->x);
        fp2_sub(tempp, tempp, onep);
        fp2_mul(tempp, tempp, tempp);
        fp2_mul(tempp, tempp, &P->x);
        //fp2_printf(tempp);

        //
        fp2_sub(bumbop, &P->x, alpha);
        fp2_mul(bumbop, bumbop, bumbop);
        fp2_inv(bumbop, bumbop);
        //fp2_printf(bumbop);

        //
        fp2_mul(&Up->x, tempp, bumbop);

        //
        fp2_set(&ans->x, &Up->x);

    }
}

void isogeny_mgec3(ec2 *R, ec2 *P, fp2 *ap){
    ec2 U; ec2 *Up;
    Up = &U;
    fp2_init(&Up->x);
    fp2_init(&Up->y);
    mpz_init(Up->inf);
    
    fp2 temp; fp2 *tempp;
    tempp = &temp;
    fp2_init(tempp);
    fp2 temp2; fp2 *temp2p;
    temp2p = &temp2;
    fp2_init(temp2p);
    fp2 temp3; fp2 *temp3p;
    temp3p = &temp3;
    fp2_init(temp3p);

    mpz_t four, three;
    mpz_init(four);
    mpz_init(three);
    mpz_set_ui(four, 4);
    mpz_set_ui(three, 3);

    fp2 six, four2, three2, one;
    fp2 *sixp;
    fp2 *fourp;
    fp2 *threep;
    fp2 *onep;
    sixp = &six;
    fourp = &four2;
    threep = &three2;
    onep = &one;
    fp2_init(sixp);
    fp2_init(fourp);
    fp2_init(threep);
    fp2_init(onep);
    fp2_set_ui(sixp, 6, 0);
    fp2_set_ui(fourp, 4, 0);
    fp2_set_ui(threep, 3, 0);
    fp2_set_ui(onep, 1, 0);

    fp2 bunshi, bumbo;
    fp2 *bunship; fp2 *bumbop;
    bunship = &bunshi;
    bumbop = &bumbo;
    fp2_init(bunship);
    fp2_init(bumbop);

    fp2_scalarexp(tempp, &P->x, four);
    //x^4

    fp2_mul(temp2p, sixp, &P->x);
    fp2_mul(temp2p, temp2p, &P->x);
    //6x^2

    fp2_scalarexp(temp3p, &P->x, three);
    fp2_mul(temp3p, temp3p, fourp);
    fp2_mul(temp3p, temp3p, ap);
    //4ax^3

    fp2_sub(tempp, tempp, temp2p);
    fp2_sub(tempp, tempp, temp3p);
    fp2_sub(tempp, tempp, threep);
    //()

    fp2_mul(tempp, tempp, tempp);
    //()^2

    fp2_mul(tempp, tempp, &P->x);
    //x*()^2

    fp2_set(bunship, tempp);




    fp2_scalarexp(tempp, &P->x, four);
    fp2_mul(tempp, tempp, threep);
    //3x^4

    fp2_add(tempp, tempp, temp2p);
    fp2_add(tempp, tempp, temp3p);
    fp2_sub(tempp, tempp, onep);
    //()

    fp2_mul(tempp, tempp, tempp);
    //()^2

    fp2_inv(tempp, tempp);
    // /

    fp2_set(bumbop, tempp);

    fp2_mul(&Up->x, bunship, bumbop);
    
    fp2_set(&R->x, &Up->x);
}