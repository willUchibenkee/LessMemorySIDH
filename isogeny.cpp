#include "isogeny.h"

void isogeny_gets(efp2_t *S, efp2_t *P, efp2_t *Q, mpz_t k, fp2_t *ap){
    // SaやSbを求めます
    //Sa = Pa + ka*Qa
    efp2_t U;
    efp2_init(&U);

    fp2_t b;
    fp2_init(&b);
    fp2_set_ui(&b, 1);

    efp2_scm(&U, Q, k);

    //efp2_checkOnCurve(&U, ap, &b);

    efp2_eca(S, P,  &U, ap, &b);

}

void isogeny_changea(fp2_t *nexta, fp2_t *nextb, fp2_t *oldb, fp2_t *alpha){
    fp2_t one, two;
    fp2_init(&one);
    fp2_init(&two);
    fp2_set_ui(&one, 1);
    fp2_set_ui(&two, 2);

    fp2_t temp;
    fp2_init(&temp);

    //a = 2(1 - 2alpha^2)
    
    fp2_mul(&temp, alpha, alpha);

    //fp2_printf("temp = ", &temp);
    
    fp2_mul(&temp, &temp, &two);

    //fp2_printf("temp = ", &temp);
    
    fp2_sub(&temp, &one, &temp);

    //fp2_printf("temp = ", &temp);
    
    fp2_mul(nexta, &two, &temp);

    //b = oldb * alpha

    // ここの処理の有無でA. Costello B. SIDHspec 楕円曲線式を切り替える

    fp2_mul(nextb, oldb, alpha);
    
}

void isogeny_changeb(fp2_t *nexta, fp2_t *nextb, fp2_t *beta, fp2_t *olda, fp2_t *oldb){

    fp2_t temp, temp2;
    fp2_init(&temp);
    fp2_init(&temp2);

    fp2_mul(&temp, olda, beta);
    fp2_mul_ui(&temp2, beta, 6);
    fp2_mul(&temp2, &temp2, beta);
    fp2_sub(&temp, &temp, &temp2);
    fp2_add_ui(&temp, &temp, 6);
    fp2_mul(&temp, &temp, beta);

    fp2_set(nexta, &temp);

    // ここの処理の有無でA. Costello B. SIDHspec 楕円曲線式を切り替える
    // b = oldb * beta**2

    fp2_sqr(&temp, beta);
    fp2_mul(&temp, &temp, oldb);

    fp2_set(nextb, &temp);

}

void isogeny_nextp(efp2_t *ans, efp2_t *P, fp2_t *alpha, int l){
    //同種写像Φを求めます
    //P...点 alpha...スタート地点 l...AliceですかBobですか
    efp2_t U,V; 
    efp2_init(&U);
    efp2_init(&V);

    efp2_set(&U, P);
    //U.infinity =  P->infinity;

    fp2_t temp, temp2, bumbo;
    fp2_init(&temp);
    fp2_init(&temp2);
    fp2_init(&bumbo);

    if(l == 2){
        //alice       
        //分子

        //xφ2(P) =xP**2 * x2 − xP/ xP − x2

        fp2_mul(&temp, &U.x, &U.x);
        fp2_mul(&temp, &temp, alpha);
        fp2_sub(&temp, &temp, &U.x);

        //fp2_printf("bunshi = ", &temp);

        //分母
        fp2_sub(&bumbo, &P->x, alpha);

        //fp2_printf("bumbo = ", &bumbo);

        fp2_inv(&bumbo, &bumbo);

        //fp2_printf("inv bumbo = ", &bumbo);

        //掛け算
        fp2_mul(&V.x, &temp, &bumbo);

        //set
        fp2_set(&ans->x, &V.x);

        //y 分子 xP**2* alpha − 2*xP*alpha**2 + alpha
        fp2_mul(&temp, &U.x, &U.x);
        fp2_mul(&temp, &temp, alpha);
        fp2_sub(&temp, &temp, &U.x);

        fp2_add(&temp2, &U.x, &U.x);
        fp2_mul(&temp2, &temp2, alpha);
        fp2_mul(&temp2, &temp2, alpha);

        fp2_sub(&temp, &temp, &temp2);

        fp2_add(&temp, &temp, alpha);

        //fp2_printf("bunshi =", &temp);

        //分母　(xP − alpha)**2
        fp2_sub(&bumbo, &U.x, alpha);
        fp2_mul(&bumbo, &bumbo, &bumbo);

        //fp2_printf("bumbo =", &bumbo);

        fp2_inv(&bumbo, &bumbo);

        //fp2_printf("inv bumbo =", &bumbo);

        fp2_mul(&temp, &temp, &bumbo);
        fp2_mul(&V.y, &temp, &U.y);

        // c**2 = alpha からcを求めて掛ける
        //(C), (D)の切り替え
        if(fp2_legendre(alpha) == 1){
            fp2_sqrt(&temp, alpha);
            fp2_mul(&V.y, &V.y, &temp);
        }

        fp2_set(&ans->y, &V.y);

    }else{
        //bob

        mpz_t three;
        mpz_init(three);
        mpz_set_ui(three, 3);

        //printf("bob\n");

        fp2_t one, temp3, temp4; 
        fp2_init(&one);
        fp2_set_ui(&one, 1);
        fp2_init(&temp3);
        fp2_init(&temp4);

        //
        fp2_mul(&temp, alpha, &U.x);
        fp2_sub(&temp, &temp, &one);
        fp2_mul(&temp, &temp, &temp);
        fp2_mul(&temp, &temp, &U.x);
        //fp2_printff(tempp);

        //
        fp2_sub(&bumbo, &P->x, alpha);
        fp2_mul(&bumbo, &bumbo, &bumbo);
        fp2_inv(&bumbo, &bumbo);
        //fp2_printff(bumbop);

        //
        fp2_mul(&V.x, &temp, &bumbo);

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

void isogeny_mgec3(efp2_t *R, efp2_t *P, fp2_t *ap){
    fp2_t temp, temp2;
    fp2_init(&temp);
    fp2_init(&temp2);

    fp2_t six, four2, three2, one, nihachi, hex;
    fp2_init(&six);
    fp2_init(&four2);
    fp2_init(&three2);
    fp2_init(&one);
    fp2_set_ui(&six, 6);
    fp2_set_ui(&four2, 4);
    fp2_set_ui(&three2, 3);
    fp2_set_ui(&one, 1);
    fp2_init(&nihachi);
    fp2_set_ui(&nihachi, 28);
    fp2_init(&hex);
    fp2_set_ui(&hex, 16);

    efp2_t U, V; 
    efp2_init(&U);
    efp2_init(&V);

    efp2_set(&U, P);
    //U.infinity = P->infinity;

    mpz_t four, three;
    mpz_init(four);
    mpz_init(three);
    
    mpz_set_ui(four, 4);
    mpz_set_ui(three, 3);

    fp2_mul(&V.x, &U.x, &U.x);
    fp2_mul(&V.x, &V.x, &U.x);
    fp2_mul(&V.x, &V.x, &U.x);

    fp2_mul(&temp, ap, &four2);
    fp2_mul(&temp, &temp, &U.x);

    // printf("4Ax:");
    // fp2_printf_s(&temp);

    fp2_sub(&V.x, &V.x, &temp);

    // printf("x**4 - 4Ax:");
    // fp2_printf_s(&V.x);

    fp2_mul(&temp, &six, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    // printf("6x**2:");
    // fp2_printf_s(&temp);

    fp2_sub(&V.x, &V.x, &temp);

    // printf("x**4 - 4Ax - 6x**2:");
    // fp2_printf_s(&V.x);

    fp2_sub(&V.x, &V.x, &three2);

    // printf("x**4 - 4Ax - 6x**2 - 3:");
    // fp2_printf_s(&V.x);

    fp2_mul(&V.x, &V.x, &V.x);

    // printf("(x**4 - 4Ax - 6x**2 - 3)**2:");
    // fp2_printf_s(&V.x);

    fp2_mul(&V.x, &V.x, &U.x);

    // printf("(x**4 - 4Ax - 6x**2 - 3)**3:");
    // fp2_printf_s(&V.x);

    //分母 (4apx**3 + 3x**4 + 6x**2 − 1)**2
    fp2_mul(&temp, &four2, ap);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    // printf("4Ax**3:");
    // fp2_printf_s(&temp);

    fp2_mul(&temp2, &three2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("3x**4:");
    // fp2_printf_s(&temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("4Ax**3 + 3x**4:");
    // fp2_printf_s(&temp);

    fp2_mul(&temp2, &six, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("6x**2:");
    // fp2_printf_s(&temp2);

    fp2_add(&temp, &temp, &temp2);

    // printf("4Ax**3 + 3x**4 + 6x**2:");
    // fp2_printf_s(&temp);

    fp2_sub(&temp, &temp, &one);

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

    fp2_mul(&temp, &four2, ap);
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

    fp2_mul(&temp, &six, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    fp2_sub(&V.y, &V.y, &temp);

    fp2_sub(&V.y, &V.y, &three2);

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

    fp2_mul(&temp2, &four2, ap);
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

    fp2_add(&temp2, &temp2, &six);

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

    fp2_mul(&temp2, &four2, ap);
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

    fp2_add(&temp, &temp, &one);

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
    fp2_mul(&temp, &four2, ap);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);
    fp2_mul(&temp, &temp, &U.x);

    // printf("x3:");
    // // fp2_from_Mont(&temp);
    // fp2_printf(&temp);
    // fp2_to_Mont(&temp, &temp);

    fp2_mul(&temp2, &three2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x4:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    fp2_mul(&temp2, &six, &U.x);
    fp2_mul(&temp2, &temp2, &U.x);

    // printf("x2:");
    // // fp2_from_Mont(&temp2);
    // fp2_printf(&temp2);
    // fp2_to_Mont(&temp2, &temp2);

    fp2_add(&temp, &temp, &temp2);

    fp2_sub(&temp, &temp, &one);

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
    R->infinity = V.infinity;
    
}

void isogeny_getj(fp2_t *jval, fp2_t *A){
    
    fp2_t temp, temp2;

    fp2_init(&temp);
    fp2_init(&temp2);

    fp2_t three, four, hex2;

    fp2_init(&three);
    fp2_init(&four);
    fp2_init(&hex2);

    fp2_set_ui(&three, 3);
    fp2_set_ui(&four, 4);
    fp2_set_ui(&hex2, 256);

    mpz_t kata;

    mpz_init(kata);

    mpz_set_ui(kata, 3);

    //分子256*(A**2 − 3)**3

    fp2_mul(&temp, A, A);
    fp2_sub(&temp, &temp, &three);
    fp2_pow(&temp, &temp, kata);
    fp2_mul(&temp, &temp, &hex2);

    //分母A**2 − 4
    fp2_mul(&temp2, A, A);
    fp2_sub(&temp2, &temp2, &four);

    fp2_inv(&temp2, &temp2);

    fp2_mul(jval, &temp, &temp2);

}