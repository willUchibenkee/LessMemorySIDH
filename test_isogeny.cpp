#include "test_isogeny.h"
#include "isogeny.h"
#include <cstdio>

void check_gets(){
  printf("check_gets() 開始\n");
  efp2_t P, Q, ANS;
  efp2_init(&P);
  efp2_init(&Q);
  efp2_init(&ANS);

  efp2_rational_point(&P);
  efp2_rational_point(&Q);
  efp2_println("P = ",&P);
  efp2_println("Q = ",&P);

  printf("---------------------------------\n");

  Isogeny_set_a0();
  mpz_t k;
  mpz_init_set_str(k, ka, 16);

  printf("getsの確認\n");
  Isogeny_gets(&ANS, &P, &Q, k, &A0);
  efp2_println("P + kQ = ",&ANS);
  printf("---------------------------------\n");

  efp2_println("P = ",&P);//Aが変わっていないことの確認
  efp2_println("Q = ",&Q);//Aが変わっていないことの確認
  printf("*********************************************************************************************\n\n");
}

void check_isogeny(efp2_t *P, efp2_t *Q, efp2_t *S, fp2_t *A, int flag){

    mpz_t lat, lbt;
    mpz_init(lat); 
    mpz_init(lbt);
    mpz_set_ui(lat, la);
    mpz_set_ui(lbt, lb);

    mpz_t py, eat, one;
    mpz_init(py);
    mpz_init(eat);
    mpz_init(one);

    mpz_set_ui(one, 1);
    //py=la**(eA-1)

    mpz_t q;
    mpz_init(q);
    int i = 0;

    Isogeny_set_a0();

    efp2_t ecneg, R;
    efp2_init(&ecneg);
    efp2_init(&R);

    fp2_t ai;
    fp2_init(&ai);

  printf("check_isogeny() 開始\n");
  
  efp2_println("P = ",P);
  efp2_println("Q = ",Q);
  efp2_println("S = ",S);

  printf("---------------------------------\n");

  if(flag == 2){
      mpz_set_str(eat, eA, 16);
      fp_sub(eat, eat, one);
      fp_pow(py, lat, eat);
      while(mpz_cmp_ui(py, 0) != 0){

        fp2_mgecSCM(&R, S, py, A);

        Isogeny_changea(&ai, &R.x);
        // printf("newa:");
        // fp2_printf(aip);

        Isogeny_nextp(P, P, &R.x, lat);
        Isogeny_nextp(Q, Q, &R.x, lat);
        Isogeny_nextp(S, S, &R.x, lat);

        if(mpz_cmp_ui(py, 1) == 0){
            //isogeny_gety(&Pbp->y, &Pbp->x, aip);
            efp2_recover_y(P, &P->x);
            //printf("a\n");
            //isogeny_gety(&Qbp->y, &Qbp->x, aip);
            efp2_recover_y(Q, &Q->x);

            efp2_recover_y(S, &S->x);

        }

        fp2_set(A, &ai);
        
        mpz_set_ui(py, mpz_get_ui(py)/la);
        //gmp_printf("py = %Zd\n", py);
        //getchar();
    }

    //fp2_set(&aap, A);

    fp2_neg(&ecneg.y, &P->y);

    // fp2_printf(&Pbp->y);
    // fp2_printf(&ecneg.y);

    if(fp2_cmp_n(&P->y, &ecneg.y) == -1){
        // fp2_printf(&Pbp->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&P->y, &ecneg.y);
    }

    fp2_neg(&ecneg.y, &Q->y);

    if(fp2_cmp_n(&Q->y, &ecneg.y) == -1){
        // fp2_printf(&Qbp->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Q->y, &ecneg.y);
    }

    printf("PKa:");
    fp2_printf(&aap);
    printf("Pb:");
    PrintEC2(Pbp);
    printf("Qb:");
    PrintEC2(Qbp);
  }else{
    mpz_t ebt;
    mpz_init(ebt);
    mpz_set_str(ebt, eB, 16);
    fp_sub(ebt, ebt, one);
    //mpz_set_ui(py, (int)(pow((double)lb, (double)eB))/lb);
    fp_pow(py, lbt, ebt);
    //gmp_printf("py = %Zd\n", py);

    Isogeny_set_a0();
    
    //fp2_printf(ap);
    while(mpz_cmp_ui(py, 0) != 0){

        fp2_set(&R.x, &S->x);
        fp2_set(&R.y, &S->y);
        mpz_set(q,py);
        i = 0;
        while(mpz_cmp_ui(q, 1) != 0){

            mpz_tdiv_q_ui(q, q, 3);
            i++;
        }
        for(int j = 0; j < i; j++){

            isogeny_mgec3(&R, &R, A);

        }

        Isogeny_changeb(&ai, &R.x, A);

        // printf("newb:");
        // fp2_printf(aip);

        Isogeny_nextp(P, P, &R.x, lbt);
        Isogeny_nextp(Q, Q, &R.x, lbt);
        Isogeny_nextp(S, S, &R.x, lbt);
        fp2_set(A, &ai);

        //fp2_printf(ap);
        mpz_set_ui(py, mpz_get_ui(py)/lb);
        
        //getchar();
    }

    Isogeny_gety(&P->y, &P->x, ap);
    Isogeny_gety(&Q->y, &Q->x, ap);
    Isogeny_gety(&S->y, &S->x, ap);

    fp2_neg(&ecneg.y, &P->y);

    if(fp2_cmp_n(&Pap->y, &ecneg.y) == -1){
        // fp2_printf(&Pap->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Pap->y, &ecneg.y);
    }

    fp2_neg(&ecneg.y, &Qap->y);

    if(fp2_cmp_n(&Q->y, &ecneg.y) == -1){
        // fp2_printf(&Qap->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Q->y, &ecneg.y);
    }

    printf("PKb:");
    fp2_printf(ap);
    printf("Pa:");
    PrintEC2(Pap);
    printf("Qa:");
    PrintEC2(Qap);
  }

  printf("weil定理の確認\n");
  efp2_scm(&ANS,&P,efp2_total);
  efp2_println("[p^2 +1 -t2]P = ",&ANS);
  printf("---------------------------------\n");

  efp2_println("P = ",&P);//Aが変わっていないことの確認

  printf("*********************************************************************************************\n\n");
}

void check_getj(){

}