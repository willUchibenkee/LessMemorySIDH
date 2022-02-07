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

    fp2 at, aap; fp2 *ap;
    ap = &at;
    fp2_init(ap);
    fp2_set_ui(ap, a0x0, a0x1);
    fp2 ai; fp2 *aip;
    aip = &ai;
    fp2_init(aip);
    fp2_init(&aap);
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
    isogeny_gets(Sbp, Pbp, Qbp, kbm, ap);
    printf("Sb:");
    PrintEC2(Sbp);

    while(mpz_cmp_ui(py, 0) != 0){
        // gmp_printf("py = %Zd\n", py);
        // printf("Sa:");
        // PrintEC2(Sap);
        // printf("a:");
        // fp2_printf(ap);
        fp2_mgecSCM(Rap, Sap, py, ap);

        // printf("Ra:");
        // fp2_printf(&Rap->x);
        // fp2_printf(&Rap->y);

        isogeny_changea(aip, &Rap->x);
        // printf("newa:");
        // fp2_printf(aip);

        isogeny_nextp(Pbp, Pbp, &Rap->x, lat);
        isogeny_nextp(Qbp, Qbp, &Rap->x, lat);
        isogeny_nextp(Sap, Sap, &Rap->x, lat);
        fp2_set(ap, aip);

        // printf("Pb:");
        // PrintEC2(Pbp);
        // printf("Qb:");
        // PrintEC2(Qbp);
        // printf("Sa:");
        // PrintEC2(Sap);
        
        mpz_set_ui(py, mpz_get_ui(py)/la);
        //gmp_printf("py = %Zd\n", py);
        //getchar();
    }

    fp2_set(&aap, ap);

    printf("PKa:");
    fp2_printf(&aap);
    printf("Pb:");
    PrintEC2(Pbp);
    printf("Qb:");
    PrintEC2(Qbp);

    

    printf("//////////////////////////////////////\n");

    //test(bob)
    mpz_set_ui(py, (int)(pow((double)lb, (double)eB))/lb);
    //gmp_printf("py = %Zd\n", py);

    fp2_set_ui(ap, a0x0, a0x1);
    
    //fp2_printf(ap);
    while(mpz_cmp_ui(py, 0) != 0){
        
        //fp2_mgecSCM(Rbp, Sbp, py, ap);
        gmp_printf("loop: %Zd / 3\n", py);
        printf("Sb:");
        PrintEC2(Sbp);
        printf("ap:");
        fp2_printf(ap);

        fp2_set(&Rbp->x, &Sbp->x);
        fp2_set(&Rbp->y, &Sbp->y);
        mpz_set(q,py);
        i = 0;
        while(mpz_cmp_ui(q, 1) != 0){
            mpz_tdiv_q_ui(q, q, 3);
            i++;
        }
        for(int j = 0; j < i; j++){
            isogeny_mgec3(Rbp, Rbp, ap);

            printf("_______________________\n");
            printf("Rb:");
            fp2_printf(&Rbp->x);
            fp2_printf(&Rbp->y);
            printf("_______________________\n");
            //printf("a\n");
        }

        isogeny_changeb(aip, &Rbp->x, ap);

        printf("newb:");
        fp2_printf(aip);

        isogeny_nextp(Pap, Pap, &Rbp->x, lbt);
        isogeny_nextp(Qap, Qap, &Rbp->x, lbt);
        isogeny_nextp(Sbp, Sbp, &Rbp->x, lbt);
        fp2_set(ap, aip);
        
        printf("Pa:");
        PrintEC2(Pap);
        printf("Qa:");
        PrintEC2(Qap);
        printf("Sb:");
        PrintEC2(Sbp);

        //fp2_printf(ap);
        mpz_set_ui(py, mpz_get_ui(py)/lb);
        
        //getchar();
    }

    // ec2 A; ec2 BB;
    // ec2 *Ap;
    // ec2 *Bp;
    // Ap = &A;
    // Bp = &BB;
    // fp2_init(&Ap->x); fp2_init(&Ap->y); mpz_init(Ap->inf);
    // fp2_init(&Bp->x); fp2_init(&Bp->y); mpz_init(Bp->inf);
    // fp2_set_ui(&Ap->x, 3,0);
    // isogeny_mgec3(Bp, Ap, ap);
    // PrintEC2(Bp);

    //鍵共有
    printf("ここから鍵共有です\n");
    while(fp2_checkans(Pap, ap) != 0){
        mpz_urandomm(Pap->y.x0, state, mp); 
        mpz_urandomm(Pap->y.x1, state, mp);
    }
    while(fp2_checkans(Qap, ap) != 0){
        mpz_urandomm(Qap->y.x0, state, mp); 
        mpz_urandomm(Qap->y.x1, state, mp);
    }
    while(fp2_checkans(Pbp, &aap) != 0){
        mpz_urandomm(Pbp->y.x0, state, mp); 
        mpz_urandomm(Pbp->y.x1, state, mp);
    }
    while(fp2_checkans(Qbp, &aap) != 0){
        mpz_urandomm(Qbp->y.x0, state, mp); 
        mpz_urandomm(Qbp->y.x1, state, mp);
    }

    //alice
    printf("aliceの操作\n");
    isogeny_gets(Sap, Pap, Qap, kam, ap);
    mpz_set_ui(py, (int)(pow((double)la, (double)eA))/2);
    while(mpz_cmp_ui(py, 0) != 0){
        fp2_mgecSCM(Rap, Sap, py, ap);
        //fp2_printf(&Rap->x);

        isogeny_changea(aip, &Rap->x);
        fp2_printf(aip);

        isogeny_nextp(Sap, Sap, &Rap->x, lat);
        fp2_set(ap, aip);

        //PrintEC2(Pbp);
        //PrintEC2(Qbp);
        //PrintEC2(Sap);
        
        mpz_set_ui(py, mpz_get_ui(py)/la);
        //gmp_printf("py = %Zd\n", py);
        //getchar();
    }

    //bob
    printf("bobの操作\n");
    PrintEC2(Pbp);
    //PrintEC2(Qbp);
    fp2_neg(&Qbp->y, &Qbp->y);
    PrintEC2(Qbp);
    isogeny_gets(Sbp, Pbp, Qbp, kbm, &aap);
    mpz_set_ui(py, (int)(pow((double)lb, (double)eB))/lb);
    while(mpz_cmp_ui(py, 0) != 0){
        
        //fp2_mgecSCM(Rbp, Sbp, py, ap);
        //PrintEC2(Sbp);
        //fp2_printf(ap);
        fp2_set(&Rbp->x, &Sbp->x);
        mpz_set(q,py);
        i = 0;
        while(mpz_cmp_ui(q, 1) != 0){
            mpz_tdiv_q_ui(q, q, 3);
            i++;
        }
        for(int j = 0; j < i; j++){
            isogeny_mgec3(Rbp, Rbp, &aap);
            //printf("a\n");
        }
        //isogeny_mgec3(Rbp, Rbp, ap);
        //fp2_printf(&Rbp->x);

        isogeny_changeb(aip, &Rbp->x, &aap);
        //fp2_printf(aip);

        isogeny_nextp(Sbp, Sbp, &Rbp->x, lbt);
        fp2_set(&aap, aip);
        
        //PrintEC2(Pap);
        //PrintEC2(Qap);
        //PrintEC2(Sbp);

        fp2_printf(&aap);
        mpz_set_ui(py, mpz_get_ui(py)/lb);
        
        //getchar();
    }

    return 0;
}