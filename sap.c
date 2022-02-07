//isogenytest.c   このプログラムの名前

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gmp.h>
#include"isogeny.h"

#define Paxx0 248
#define Paxx1 100
#define Payx0 199
#define Payx1 304

#define Qaxx0 394
#define Qaxx1 426
#define Qayx0 79
#define Qayx1 51

#define Pbxx0 275
#define Pbxx1 358
#define Pbyx0 104
#define Pbyx1 410

#define Qbxx0 185
#define Qbxx1 20
#define Qbyx0 239
#define Qbyx1 281

int main(void){
    //define
    ec2 Pa, Qa, Ra, Sa;
    ec2 *Pap; ec2 *Qap; ec2 *Rap; ec2 *Sap;
    Pap = &Pa; Qap = &Qa; Rap = &Ra; Sap = &Sa;

    fp2_init(&Pap->x); fp2_init(&Pap->y); mpz_init(Pap->inf);
    fp2_init(&Qap->x); fp2_init(&Qap->y); mpz_init(Qap->inf);
    fp2_init(&Rap->x); fp2_init(&Rap->y); mpz_init(Rap->inf);
    fp2_init(&Sap->x); fp2_init(&Sap->y); mpz_init(Sap->inf);

    ec2 Pb, Qb, Rb, Sb;
    ec2 *Pbp; ec2 *Qbp; ec2 *Rbp; ec2 *Sbp;
    Pbp = &Pb; Qbp = &Qb; Rbp = &Rb; Sbp = &Sb;

    fp2_init(&Pbp->x); fp2_init(&Pbp->y); mpz_init(Pbp->inf);
    fp2_init(&Qbp->x); fp2_init(&Qbp->y); mpz_init(Qbp->inf);
    fp2_init(&Rbp->x); fp2_init(&Rbp->y); mpz_init(Rbp->inf);
    fp2_init(&Sbp->x); fp2_init(&Sbp->y); mpz_init(Sbp->inf);

    fp2_set_ui(&Pap->x, Paxx0, Paxx1);
    fp2_set_ui(&Pap->y, Payx0, Payx1);
    fp2_set_ui(&Qap->x, Qaxx0, Qaxx1);
    fp2_set_ui(&Qap->y, Qayx0, Qayx1);

    fp2_set_ui(&Pbp->x, Pbxx0, Pbxx1);
    fp2_set_ui(&Pbp->y, Pbyx0, Pbyx1);
    fp2_set_ui(&Qbp->x, Qbxx0, Qbxx1);
    fp2_set_ui(&Qbp->y, Qbyx0, Qbyx1);

    mpz_t kam, kbm;
    mpz_init(kam);
    mpz_init(kbm);
    mpz_set_ui(kam, ka);
    mpz_set_ui(kbm, kb);

    mpz_t py;
    mpz_init(py);
    mpz_set_ui(py, (int)(pow((double)la, (double)eA))/2);

    mpz_t q;
    mpz_init(q);
    int i = 0;

    mpz_t lat, lbt;
    mpz_init(lat); 
    mpz_init(lbt);
    mpz_set_ui(lat, la);
    mpz_set_ui(lbt, lb);
    //gmp_printf("la = %Zd\n", lat);

    fp2 at; fp2 *ap;
    ap = &at;
    fp2_init(ap);
    fp2_set_ui(ap, a0x0, a0x1);
    fp2 ai; fp2 *aip;
    aip = &ai;
    fp2_init(aip);
    //fp2_printf(ap);

    fp2 alpha; fp2 *alphap;
    alphap = &alpha;
    fp2_init(alphap);
    //fp2_printf(alphap);

    gmp_randstate_t state;
    gmp_randinit_default(state);

    mpz_t mp;
    mpz_init(mp);
    mpz_set_ui(mp, p);

    //test(alice)
    isogeny_gets(Sap, Pap, Qap, kam, ap);
    printf("Sa:");
    PrintEC2(Sap);

    ec2 U, V, ANS;
    fp2_init(&U.x);
    fp2_init(&U.y);
    fp2_init(&V.x);
    fp2_init(&V.y);
    mpz_init(U.inf);
    mpz_init(V.inf);
    fp2_init(&ANS.x);
    fp2_init(&ANS.y);
    mpz_init(ANS.inf);

    fp2_set_ui(&U.x, 394, 426);
    fp2_set_ui(&U.y, 79, 51);
    fp2_set_ui(&V.x, 59, 167);
    fp2_set_ui(&V.y, 144, 108);

    fp2_mgecA(&ANS, &U, &V, ap);
    printf("ANS:");
    PrintEC2(&ANS);

    return 0;

}