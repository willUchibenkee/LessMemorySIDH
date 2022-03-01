#include "isogeny.h"

//fp2_t A0;
int ea, eb;
efp2_t P,Q;

void Isogeny_set_a0(void){

    mpz_t tmp, tmp2;
    mpz_init_set_str(tmp, Aval0, 16);
    mpz_init_set_str(tmp2, Aval1, 16);

    fp_t temp, temp2;
    fp_init(&temp);
    fp_init(&temp2);
    mpn_set_mpz(temp.x0, tmp);
    mpn_set_mpz(temp2.x0, tmp2);

    fp2_set_fp(&A0, &temp, &temp2);

    mpz_clear(tmp);
    mpz_clear(tmp2);
 
}

void Isogeny_set_e(void){
    ea = eA;
    eb = eB;
}

void Isogeny_set_point(void){
    mpz_t tmp;

    mpz_init_set_str(&tmp, Pax0, 16);
    mpn_set_mpz(P.x.x0.x0, &tmp);

    mpz_init_set_str(&tmp, Pax1, 16);
    mpn_set_mpz(P.x.x1.x0, &tmp);

    mpz_init_set_str(&tmp, Pay0, 16);
    mpn_set_mpz(P.y.x0.x0, &tmp);

    mpz_init_set_str(&tmp, Pay1, 16);
    mpn_set_mpz(P.y.x1.x0, &tmp);

    mpz_init_set_str(&tmp, Qax0, 16);
    mpn_set_mpz(Q.x.x0.x0, &tmp);

    mpz_init_set_str(&tmp, Qax1, 16);
    mpn_set_mpz(Q.x.x1.x0, &tmp);

    mpz_init_set_str(&tmp, Qay0, 16);
    mpn_set_mpz(Q.y.x0.x0, &tmp);

    mpz_init_set_str(&tmp, Qay1, 16);
    mpn_set_mpz(Q.y.x1.x0, &tmp);

}

void Isogeny_gets(efp2_t *S, efp2_t *P, efp2_t *Q, mpz_t k, fp2_t *ap){
    // SaやSbを求めます
    //Sa = Pa + ka*Qa
    efp2_t U;
    efp2_init(&U);
    //U.infinity = 0;
    
    efp2_scm(&U, Q, k);

    fp2_t eb;
    fp2_init(&eb);
    fp2_set_ui(&eb, 1);

    efp2_eca(S, P, &U, ap, &eb);

}

void Isogeny_changea(fp2_t *nexta, fp2_t *alpha){
    fp2_t one, two;
    fp2_set_ui(&one, 1);
    fp2_set_ui(&two, 2);
    fp2_t temp;


    fp2_mul(&temp, alpha, alpha);

    fp2_mul(&temp, &temp, &two);

    fp2_sub(&temp, &one, &temp);

    fp2_mul(nexta, &two, &temp);

}

void Isogeny_changeb(fp2_t *nexta, fp2_t *beta, fp2_t *olda){
    fp2_t six;
    fp2_set_ui(&six, 6);

    fp2_t temp, temp2;

    fp2_mul(&temp, olda, beta);
    fp2_mul(&temp2, &six, beta);
    fp2_mul(&temp2, &temp2, beta);
    fp2_sub(&temp, &temp, &temp2);
    fp2_add(&temp, &temp, &six);
    fp2_mul(&temp, &temp, beta);

    fp2_set(nexta, &temp);
}

void Isogeny_nextp(efp2_t *ans, efp2_t *P, fp2_t *alpha, int l){
    //同種写像Φを求めます
    //P...点 alpha...スタート地点 l...AliceですかBobですか
    efp2_t U, V; 

    fp2_t temp, bumbo, temp2; 

    fp2_t two; 
    fp2_set_ui(&two, 2);

    fp2_set(&U.x, &P->x);
    fp2_set(&U.y, &P->y);
    U.infinity = 0;
    V.infinity = 0;
    fp2_set_ui(&V.x, 0);
    fp2_set_ui(&V.y, 0);

    if(l == 2){
        //alice       
        //分子 xp px x2 alpha
        
        fp2_mul(&temp, &U.x, &U.x);
        fp2_mul(&temp, &temp, alpha);
        fp2_sub(&temp, &temp, &U.x);
        

        //分母
        fp2_sub(&bumbo, &U.x, alpha);
        
        fp2_inv(&bumbo, &bumbo);

        
        //掛け算
        fp2_mul(&V.x, &temp, &bumbo);
        
        //set
        fp2_set(&ans->x, &V.x);
        //Fp2_from_Mont(&ans->x);

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
        
        fp2_t one, temp3, temp4; 
        fp2_set_ui(&one, 1);

        //
        fp2_mul(&temp, alpha, &U.x);
        fp2_sub(&temp, &temp, &one);
        fp2_mul(&temp, &temp, &temp);
        fp2_mul(&temp, &temp, &U.x);
        
        //
        fp2_sub(&bumbo, &U.x, alpha);
        fp2_mul(&bumbo, &bumbo, &bumbo);
        fp2_inv(&bumbo, &bumbo);
        

        //
        fp2_mul(&V.x, &temp, &bumbo);

        //
        fp2_set(&ans->x, &V.x);

        //y 分子 (xP*a − 1)(xP**2*a − 3*xP*a**3 + xP + a)

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

void Isogeny_mgec3(efp2_t *R, efp2_t *P, fp2_t *ap){
    efp2_t U; 
    
    fp2_t temp, temp2, temp3; 

    fp2_t six, four2, three2, one;
    
    fp2_set_ui(&six, 6);
    fp2_set_ui(&four2, 4);
    fp2_set_ui(&three2, 3);
    fp2_set_ui(&one, 1);

    fp2_t bunshi, bumbo;

    fp2_mul(&temp, &P->x, &P->x);
    fp2_mul(&temp, &temp, &P->x);
    fp2_mul(&temp, &temp, &P->x);
    //x^4

    fp2_mul(&temp2, &six, &P->x);
    fp2_mul(&temp2, &temp2, &P->x);
    //6x^2

    
    fp2_mul(&temp3, &P->x, &four2);
    fp2_mul(&temp3, &temp3, ap);
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


    fp2_mul(&temp, &P->x, &P->x);
    fp2_mul(&temp, &temp, &P->x);
    fp2_mul(&temp, &temp, &P->x);
    fp2_mul(&temp, &temp, &three2);
    //3x^4

    fp2_mul(&temp3, &P->x, &P->x);
    fp2_mul(&temp3, &temp3, &P->x);
    fp2_mul(&temp3, &temp3, &four2);
    fp2_mul(&temp3, &temp3, ap);
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

// void isogeny_gety(Fp2 *y, Fp2 *x, Fp2 *A){
//     // y**2=x**3+Ax**2+x
//     Fp2 temp, temp2;

//     //Fp three;
//     //mpz_init(three);
//     //Fp_set_str(&three, "3");

//     Fp2_mul(&temp, x, x);
//     Fp2_mul(&temp, &temp, x);

//     Fp2_mul(&temp2, A, x);
//     Fp2_mul(&temp2, &temp2, x);

//     Fp2_add(&temp, &temp, &temp2);

//     Fp2_add(&temp, &temp, x);

//     if(Fp2_legendre(&temp) == 1){
//         printf("temp:");

//         Fp2_print(&temp);

//         Fp2_sqrt_34(y, &temp);
//     }else{
//         printf("no y\n");
//     }
// }

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

    mpz_clear(kata);

}