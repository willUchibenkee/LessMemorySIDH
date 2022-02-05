//efp2test.c(Montgomery)

#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>
#include<stdlib.h>
#include"efp2.h"

int main(void){
    //定義とかもろもろ
        ec2 rdm1, rdm2, ans;
        ec2 *rp1; ec2 *rp2; ec2 *ansp;
        rp1 = &rdm1; 
        rp2 = &rdm2; 
        ansp = &ans; 
        mpz_t pp, p1, nbai;
        fp2 uhen, sahen;
        fp2 *uhenp;
        fp2 *sahenp;
        uhenp = &uhen;
        sahenp = &sahen;
        mpz_t three;
        fp2 at, bt, work;
        fp2 *atp;
        fp2 *btp;
        fp2 *workp;
        atp = &at;
        btp = &bt;
        workp = &work;
        gmp_randstate_t state;
        gmp_randinit_default(state);
        fp2_init(&rp1->x);
        fp2_init(&rp1->y);
        mpz_init(rp1->inf);
        fp2_init(&rp2->x);
        fp2_init(&rp2->y);
        mpz_init(rp2->inf);
        fp2_init(&ansp->x);
        fp2_init(&ansp->y);
        mpz_init(ansp->inf);
        mpz_init(pp);
        mpz_init(p1);
        mpz_init(nbai);
        fp2_init(uhenp);
        fp2_init(sahenp);
        mpz_init(three);
        fp2_init(atp);
        fp2_init(btp);
        fp2_init(workp);
        mpz_set_ui(pp, p);
        mpz_set_ui(atp->x0, Ax0);
        mpz_set_ui(atp->x1, Ax1);
        mpz_set_ui(btp->x0, B);
        mpz_set_ui(btp->x1, 0);
        mpz_set_ui(three, 3);
        mpz_set_ui(p1, p-1);

    // test
        ec2 P;

        fp2_init(&P.x);
        fp2_init(&P.y);
        mpz_init(P.inf);
        fp2_set_ui(&P.x, 248, 100);
        fp2_set_ui(&P.y, 199, 304);

        printf("P:");
        PrintEC2(&P);
        printf("A:");
        fp2_printf(atp);

        ec2 eca,ecd;
        fp2_init(&eca.x);
        fp2_init(&eca.y);
        mpz_init(eca.inf);
        fp2_init(&ecd.x);
        fp2_init(&ecd.y);
        mpz_init(ecd.inf);

        fp2_mgecD(&ecd, &P, atp);
        printf("ecd:");
        PrintEC2(&ecd);

        fp2_mgecA(&eca, &P, &ecd, atp);
        printf("eca:");
        PrintEC2(&eca);

        mpz_set_ui(nbai, 432);
        printf("/////////////////////////////////////////////\n");
        fp2_mgecSCM(ansp, &P, nbai, atp);

        //248
// #define Paxx1 100
// #define Payx0 199
// #define Payx1 304
        // do{
        //     mpz_urandomm(rp1->x.x0, state, pp);
        //     mpz_urandomm(rp1->x.x1, state, pp);
        //     fp2_scalarexp(workp, &rp1->x, three);
        //     fp2_mul(uhenp, &rp1->x, &rp1->x);
        //     fp2_mul(uhenp, uhenp, atp);
        //     fp2_add(uhenp, uhenp, workp);
        //     fp2_add(uhenp, uhenp, &rp1->x);
        //     gmp_printf("uhen = %Zd, %Zd\n", uhenp->x0, uhenp->x1);
        //     fp2_legendre(workp, uhenp);
        //     gmp_printf("work = %Zd, %Zd\n", workp->x0, workp->x1);
        // }while(fp2_cmp_ui(workp, 1, 0) != 0);
        // while(fp2_checkans(rp1,atp) != 0){
        //     mpz_urandomm(rp1->y.x0, state, pp);
        //     mpz_urandomm(rp1->y.x1, state, pp);
        //     //getchar();
        // }
        // //fp2_TonelliShanks(&rp1->y, uhenp);
        // mpz_set_ui(nbai, p+1);
        // gmp_printf("r1(x(a,b), y(c,d)) = ((%Zd, %Zd), (%Zd, %Zd))\n", rp1->x.x0, rp1->x.x1, rp1->y.x0, rp1->y.x1);
        // if(fp2_checkans(rp1,atp) == 0){
        //     printf("rp ok\n");
        // }else{
        //     printf("rp ng\n");
        // }
        
        if(mpz_cmp_ui(ansp->inf, 1) == 0){
            printf("ans = inf\n");
        }else{
            gmp_printf("ans(x(a,b), y(c,d)) = ((%Zd, %Zd), (%Zd, %Zd))\n", ansp->x.x0, ansp->x.x1, ansp->y.x0, ansp->y.x1);
        }

        return 0;
}