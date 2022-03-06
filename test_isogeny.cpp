#include "test_isogeny.h"
#include "isogeny.h"
#include <cstdio>

void check_gets(efp2_t *ANS, efp2_t *P, efp2_t *Q, fp2_t *A, int flag){
  printf("check_gets() 開始\n");

  efp2_println("P = ",P);
  efp2_println("Q = ",Q);

  printf("---------------------------------\n");

  mpz_t k;
  if(flag== 2){
    mpz_init_set_str(k, ka, 16);
  }else{
    mpz_init_set_str(k, kb, 16);
  }

  printf("getsの確認\n");
  Isogeny_gets(ANS, P, Q, k, A);
  efp2_println("P + kQ = ",ANS);
  printf("---------------------------------\n");

  efp2_println("P = ", P);//Aが変わっていないことの確認
  efp2_println("Q = ", Q);//Aが変わっていないことの確認

  mpz_clear(k);
  printf("*********************************************************************************************\n\n");
}

void check_isogeny(efp2_t *P, efp2_t *Q, efp2_t *S, fp2_t *A, int flag){

    mpz_t lat, lbt;
    mpz_init(lat); 
    mpz_init(lbt);
    mpz_set_ui(lat, la);
    mpz_set_ui(lbt, lb);

    fp_t py, temp, one;
    fp_init(&py);
    fp_init(&temp);
    fp_init(&one);

    fp_set_ui(&one, 1);
    //py=la**(eA-1)

    mpz_t q;
    mpz_init(q);
    int i = 0;

    efp2_t ecneg, R;
    efp2_init(&ecneg);
    efp2_init(&R);

    fp2_t ai;
    fp2_init(&ai);

    mpz_t tmp;
    mpz_init(tmp);

  printf("check_isogeny() 開始\n");
  
  efp2_println("P = ",P);
  efp2_println("Q = ",Q);
  efp2_println("S = ",S);

  printf("---------------------------------\n");

  if(flag == 2){
      //mpz_set_str(tmp, pya, 16);
    //   mpn_set_mpz(eat.x0, tmp);
    //   fp_sub(&eat, &eat, &one);
    //   fp_pow(&py, &lat, eat);
      //mpn_set_mpz(py.x0, tmp);
      fp_sub_ui(&py, &ea, 1);
      while(fp_cmp_ui(&py, 0) != 0){

        //efp2_scm(&R, S, tmp);
        
        for(fp_init(&temp); fp_cmp(&py, &temp) != 0; fp_add_ui(&temp, &temp, 1)){

          efp2_ecd(&R, S, A, &B);

        }

        Isogeny_changea(&ai, &R.x);
        // printf("newa:");
        // fp2_printf(aip);

        Isogeny_nextp(P, P, &R.x, la);
        Isogeny_nextp(Q, Q, &R.x, la);
        Isogeny_nextp(S, S, &R.x, la);

        if(fp_cmp_ui(&py, 1) == 0){
            //isogeny_gety(&Pbp->y, &Pbp->x, aip);
            efp2_recover_y(P, P->x);
            //printf("a\n");
            //isogeny_gety(&Qbp->y, &Qbp->x, aip);
            efp2_recover_y(Q, Q->x);

            efp2_recover_y(S, S->x);

        }

        fp2_set(A, &ai);
        
        //mpz_set_ui(tmp, fp_get_ui(py)/la);
        fp_sub_ui(&py, &py, 1);
        //fp_set_ui(py, fp_get_ui(py)/la);
        //gmp_printf("py = %Zd\n", py);
        //getchar();
    }

    //fp2_set(&aap, A);

    fp2_set_neg(&ecneg.y, &P->y);

    // fp2_printf(&Pbp->y);
    // fp2_printf(&ecneg.y);

    if(fp2_cmp_n(&P->y, &ecneg.y) == -1){
        // fp2_printf(&Pbp->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&P->y, &ecneg.y);
    }

    fp2_set_neg(&ecneg.y, &Q->y);

    if(fp2_cmp_n(&Q->y, &ecneg.y) == -1){
        // fp2_printf(&Qbp->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Q->y, &ecneg.y);
    }

    printf("PKa:");
    fp2_println("Aa = ",A);
    efp2_println("Pb = ", P);
    efp2_println("Qb = ", Q);
  }else{
    // mpz pyb;
    // mpz_init(pyb);
    // mpz_set_str(pyb, pyb, 16);
    //mpz_set_str(tmp, eb, 16);
    fp_set(&py, &eb);
    fp_sub_ui(&py, &py, 1);
    //fp_sub(ebt, ebt, one);
    //mpz_set_ui(py, (int)(pow((double)lb, (double)eB))/lb);
    
    //fp_pow(py, lbt, ebt);
    //gmp_printf("py = %Zd\n", py);
    
    //fp2_printf(ap);
    while(fp_cmp_ui(&py, 0) != 0){

        fp2_set(&R.x, &S->x);
        fp2_set(&R.y, &S->y);
        //mpz_set(q,py);
        //i = 0;
        // while(fp_cmp_ui(q, 1) != 0){

        //     mpz_tdiv_q_ui(q, q, 3);
        //     i++;
        // }
        for(fp_init(&temp); fp_cmp(&py, &temp) != 0; fp_add_ui(&temp, &temp, 1)){

            Isogeny_mgec3(&R, &R, A);

        }

        Isogeny_changeb(&ai, &R.x, A);

        // printf("newb:");
        // fp2_printf(aip);

        Isogeny_nextp(P, P, &R.x, lb);
        Isogeny_nextp(Q, Q, &R.x, lb);
        Isogeny_nextp(S, S, &R.x, lb);
        fp2_set(A, &ai);

        //fp2_printf(ap);
        //mpz_set_ui(py, mpz_get_ui(py)/lb);
        fp_sub_ui(&py, &py, 1);
        
        //getchar();
    }

    // Isogeny_gety(&P->y, &P->x, ap);
    // Isogeny_gety(&Q->y, &Q->x, ap);
    // Isogeny_gety(&S->y, &S->x, ap);
    efp2_recover_y(P, P->x);
            //printf("a\n");
    efp2_recover_y(Q, Q->x);

    efp2_recover_y(S, S->x);

    fp2_set_neg(&ecneg.y, &P->y);

    if(fp2_cmp_n(&P->y, &ecneg.y) == -1){
        // fp2_printf(&Pap->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&P->y, &ecneg.y);
    }

    fp2_set_neg(&ecneg.y, &Q->y);

    if(fp2_cmp_n(&Q->y, &ecneg.y) == -1){
        // fp2_printf(&Qap->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Q->y, &ecneg.y);
    }

    printf("PKb:");
    fp2_println("Ab = ", A);
    efp2_println("Pb = ", P);
    efp2_println("Pb = ", Q);
  }

  //printf("weil定理の確認\n");
  //efp2_scm(&ANS,P,efp2_total);
  //efp2_println("[p^2 +1 -t2]P = ",&ANS);
  //printf("---------------------------------\n");

  //efp2_println("P = ", P);//Aが変わっていないことの確認

  printf("*********************************************************************************************\n\n");
}

void check_getj(fp2_t *A){
  
  fp2_t ANS;
  fp2_init(&ANS);

  isogeny_getj(&ANS, A);

  printf("getjの確認\n");
  fp2_println("j = ", &ANS);

}