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
    // printf("kQ:");
    // PrintEC2(up);
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
    // printf("alpha**2: ");
    // fp2_printff(tempp);
    fp2_mul(tempp, tempp, twop);
    // printf("2*alpha**2: ");
    // fp2_printff(tempp);
    fp2_sub(tempp, onep, tempp);
    // printf("2*alpha**2 - 1: ");
    // fp2_printff(tempp);
    //printf("nexta: ");
    fp2_mul(nexta, twop, tempp);
    //fp2_printff(nexta);
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

    if(mpz_cmp_ui(l,2) == 0){
        //alice       
        //分子
        //printf("alice\n");
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
        fp2_set(&ans->x, &V.x);
        //fp2_set(&ans->y,&Up->y);

        //y 分子 xP**2* alpha − 2*xP*alpha**2 + alpha
        fp2_mul(&temp, &U.x, &U.x);
        fp2_mul(&temp, &temp, alpha);
        fp2_sub(&temp, &temp, &U.x);

        fp2_mul(&temp2, &two, &U.x);
        fp2_mul(&temp2, &temp2, alpha);
        fp2_mul(&temp2, &temp2, alpha);

        fp2_sub(&temp, &temp, &temp2);

        fp2_add(&temp, &temp, alpha);

        //分母　(xP − alpha)**2
        fp2_sub(&bumbo, &U.x, alpha);
        fp2_mul(&bumbo, &bumbo, &bumbo);

        fp2_inv(&bumbo, &bumbo);

        fp2_mul(&temp, &temp, &bumbo);
        fp2_mul(&V.y, &temp, &U.y);

        fp2_set(&ans->y, &V.y);

    }else{
        //bob

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

        //
        fp2_mul(tempp, alpha, &U.x);
        fp2_sub(tempp, tempp, onep);
        fp2_mul(tempp, tempp, tempp);
        fp2_mul(tempp, tempp, &U.x);
        //fp2_printff(tempp);

        //
        fp2_sub(bumbop, &P->x, alpha);
        fp2_mul(bumbop, bumbop, bumbop);
        fp2_inv(bumbop, bumbop);
        //fp2_printff(bumbop);

        //
        fp2_mul(&V.x, tempp, bumbop);

        //
        fp2_set(&ans->x, &V.x);

        //y 分子 (xP*a − 1)(xP**2*a − 3*xP*a**3 + xP + a)
        // printf("alpha:");
        // fp2_printf_s(alpha);
        // printf("U:");
        // Efp2_PrintEC2_s(&U);

        fp2_mul(&temp, &U.x, alpha);
        fp2_sub(&temp, &temp, &one);

        //////////////////////////////////////

        fp2_mul(&temp2, &U.x, alpha);
        fp2_mul(&temp2, &temp2, &U.x);

        fp2_mul(&temp3, &U.x, alpha);
        fp2_mul(&temp3, &temp3, alpha);
        fp2_mul(&temp3, &temp3, alpha);

        fp2_add(&temp4, &temp3, &temp3);
        fp2_add(&temp4, &temp4, &temp3);

        fp2_sub(&temp2, &temp2, &temp4);

        fp2_add(&temp2, &temp2, &U.x);

        fp2_add(&temp2, &temp2, alpha);

        ///////////////////////////////////////

        fp2_mul(&temp, &temp, &temp2);

        //分母 (xP − x3)3
        fp2_sub(&temp3, &U.x, alpha);
        fp2_mul(&bumbo, &temp3, &temp3);
        fp2_mul(&bumbo, &bumbo, &temp3);

        fp2_inv(&bumbo, &bumbo);

        ///////////////////////////////////////

        fp2_mul(&V.y, &temp, &bumbo);

        fp2_mul(&V.y, &V.y, &U.y);

        fp2_set(&ans->y, &V.y);

    }
}

void isogeny_mgec3(ec2 *R, ec2 *P, fp2 *ap){
    fp2 temp, temp2;
    fp2 six, four2, three2, one, nihachi, hex; 

    ec2 U, V; 
    fp2_init(&U.x);
    fp2_init(&U.y);
    mpz_init(U.inf);

    fp2_set(&U.x, &P->x);
    fp2_set(&U.y, &P->y);
    mpz_set(U.inf, P->inf);

    // printf("U.y:");
    // fp2_printf(&U.y);

    fp2_init(&V.x);
    fp2_init(&V.y);
    mpz_init(V.inf);
    
    fp2 *tempp;
    tempp = &temp;
    fp2_init(tempp);
    fp2 *temp2p;
    temp2p = &temp2;
    fp2_init(temp2p);

    
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

    fp2_init(&nihachi);
    fp2_set_ui(&nihachi, 28, 0);

    fp2_init(&hex);
    fp2_set_ui(&hex, 16, 0);

    mpz_t four, three;
    mpz_init(four);
    mpz_init(three);
    
    mpz_set_ui(four, 4);
    mpz_set_ui(three, 3);

    fp2_mul(&V.x, &U.x, &U.x);
    fp2_mul(&V.x, &V.x, &U.x);
    fp2_mul(&V.x, &V.x, &U.x);

    // printf("x**4:");
    // fp2_printf_s(&V.x);

    fp2_mul(&temp, ap, fourp);
    fp2_mul(&temp, &temp, &U.x);

    // printf("4Ax:");
    // fp2_printf_s(&temp);

    fp2_sub(&V.x, &V.x, &temp);

    // printf("x**4 - 4Ax:");
    // fp2_printf_s(&V.x);

    fp2_mul(&temp, sixp, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    // printf("6x**2:");
    // fp2_printf_s(&temp);

    fp2_sub(&V.x, &V.x, &temp);

    // printf("x**4 - 4Ax - 6x**2:");
    // fp2_printf_s(&V.x);

    fp2_sub(&V.x, &V.x, threep);

    // printf("x**4 - 4Ax - 6x**2 - 3:");
    // fp2_printf_s(&V.x);

    fp2_mul(&V.x, &V.x, &V.x);

    // printf("(x**4 - 4Ax - 6x**2 - 3)**2:");
    // fp2_printf_s(&V.x);

    fp2_mul(&V.x, &V.x, &U.x);

    // printf("(x**4 - 4Ax - 6x**2 - 3)**3:");
    // fp2_printf_s(&V.x);

    //分母 (4apx**3 + 3x**4 + 6x**2 − 1)**2
    fp2_mul(&temp, fourp, ap);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    // printf("4Ax**3:");
    // fp2_printf_s(&temp);

    fp2_mul(&temp2, threep, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("3x**4:");
    // fp2_printf_s(&temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("4Ax**3 + 3x**4:");
    // fp2_printf_s(&temp);

    fp2_mul(&temp2, sixp, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("6x**2:");
    // fp2_printf_s(&temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("4Ax**3 + 3x**4 + 6x**2:");
    // fp2_printf_s(&temp);

    fp2_sub(&temp, &temp, onep);

    // printf("4Ax**3 + 3x**4 + 6x**2 -1:");
    // fp2_printf_s(&temp);

    fp2_mul(&temp, &temp, &temp);

    // printf("(4Ax**3 + 3x**4 + 6x**2 -1)**2:");
    // fp2_printf_s(&temp);

    fp2_inv(&temp, &temp);

    // printf("inv (4Ax**3 + 3x**4 + 6x**2 -1)**2:");
    // fp2_printf_s(&temp);

    fp2_mul(&V.x, &V.x, &temp);

    // y  分子 (x**4 − 4Ax − 6x**2 − 3)(x**8 + 4Ax**7 + 28x**6 + 28Ax**5 + (16A**2 + 6)x**4 + 28Ax**3 + 28x**2 + 4Ax + 1)
    fp2_mul(&V.y, &U.x, &U.x);
    fp2_mul(&V.y, &V.y, &U.x);
    fp2_mul(&V.y, &V.y, &U.x);

    // printf("x**4:");
    // // fp2_from_Mont(ycoord(R));
    // fp2_printf(&V.y);
    // // fp2_to_Mont(ycoord(R), ycoord(R));

    fp2_mul(&temp, fourp, ap);
    fp2_mul(&temp, &temp, &U.x);

    // printf("4ax:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_sub(&V.y, &V.y, &temp);

    // printf("hiki:");
    // // fp2_from_Mont(ycoord(R));
    // fp2_printf(&V.y);
    // // fp2_to_Mont(ycoord(R), ycoord(R));

    fp2_mul(&temp, sixp, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    fp2_sub(&V.y, &V.y, &temp);

    fp2_sub(&V.y, &V.y, threep);

    // printf("zenhan:");
    // // fp2_from_Mont(ycoord(R));
    // fp2_printf(&V.y);
    // // fp2_to_Mont(ycoord(R), ycoord(R));
    //13

    //////////////////////////////////////////////////////////////////////

    fp2_mul(&temp, &U.x, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    // printf("x8:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, fourp, ap);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x7:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("tasu:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, &nihachi, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x6:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("tasu2:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, &nihachi, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, ap);

    // printf("x5:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("tasu3:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, &hex, ap);

    // printf("16A:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_mul(&temp2, &temp2, ap);

    // printf("16A**2:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp2, &temp2, sixp);

    // printf("+6:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_mul(&temp2, &temp2, &U.x);

    // printf("*x:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x**2:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_mul(&temp2, &temp2, &U.x);
     
    // printf("x**3:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_mul(&temp2, &temp2, &U.x);

    // printf("(16A**2+6)x4:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("tasu4:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, &nihachi, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, ap);

    // printf("x3:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("tasu5:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, &nihachi, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x3:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("tasu6:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, fourp, ap);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("tasu7:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);

    fp2_add(&temp, &temp, onep);

    // printf("kouhan:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // // fp2_to_Mont(&temp, &temp);
    //18a

    fp2_mul(&V.y, &V.y, &temp);

    // printf("bunshi:");
    // // fp2_from_Mont(ycoord(R));
    // fp2_printf(&V.y);
    // fp2_to_Mont(ycoord(R), ycoord(R));
    //9f

    //分母 (4Ax**3 + 3x**4 + 6x**2 − 1)**3
    fp2_mul(&temp, fourp, ap);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    // printf("x3:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, threep, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x4:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    fp2_mul(&temp2, sixp, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x2:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    fp2_sub(&temp, &temp, onep);

    // printf("katamari:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, &temp, &temp);
    fp2_mul(&temp2, &temp2, &temp);

    // printf("ans:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // fp2_to_Mont(&temp2, &temp2);

    fp2_inv(&temp2, &temp2);
    //188

    // printf("inv:");
    // fp2_printf(&temp2);

    //////////////////////////////////////////////////////////////

    fp2_mul(&V.y, &V.y, &temp2);

    // printf("分数:");
    // fp2_printf(&V.y);

    //////////////////////////////////////////////////////////////

    fp2_mul(&V.y, &V.y, &U.y);

    // printf("分数*y:");
    // fp2_printf(&V.y);


    fp2_set(&R->x, &V.x);
    fp2_set(&R->y, &V.y);
    mpz_set(R->inf, V.inf);
    
}