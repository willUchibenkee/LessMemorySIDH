//test_isogeny.cpp
#include "test_isogeny.h"
#include "isogeny.h"
#include <cstdio>

void keycon(efp2_t *P2, efp2_t *Q2, efp2_t *P3, efp2_t *Q3){
    // 鍵共有

    printf("keycon starts.\n");

    efp2_t S, R;
    efp2_init(&S);
    efp2_init(&R);

    //Ea, Eb: Bobのパラメータ  tmp_a, tmp_b: Aliceのパラメータ
    //Aliceの鍵共有から行う　Bobの点と楕円曲線パラメータを使ってkaで計算

    isogeny_gets(&S, P2, Q2, ka_z, &Ea);
    efp2_checkOnCurve(&S, &Ea, &Eb);

    efp2_printf("S = ", &S);

    // ループ(R=Sまで)

    mpz_t j, i;
    mpz_init(j);
    mpz_init(i);

    mpz_set(j, ea_z);

    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 0); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

            efp2_ecd(&R, &R, &Ea, &Eb);

        }

        // Rからaを2or3同種写像で求める
        isogeny_changea(&Ea, &Eb, &Eb, &R.x);
        fp2_printf("newa = ", &Ea);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(&S, &S, &R.x, 2);

        efp2_recover_y(&S, S.x);

    }

    efp2_set(&R, &S);
    isogeny_changea(&Ea, &Eb, &Eb, &R.x);
    fp2_printf("newa = ", &Ea);

    printf("-------------------\n");

    efp2_printf("P3 = ", P3);
    efp2_printf("Q3 = ", Q3);
    fp2_printf("tmp_a =", &tmp_a);
    isogeny_gets(&S, P3, Q3, kb_z, &tmp_a);

    efp2_checkOnCurve(&S, &tmp_a, &Eb);

    efp2_printf("S = ", &S);

    fp2_t ja, jb;
    fp2_init(&ja);
    fp2_init(&jb);
    isogeny_getj(&ja, &Ea);

    // fp2_set(&Ea, &tmp_a);
    // fp2_set(&Eb, &tmp_b);

    mpz_set(j, eb_z);

    // Alice, Bobどっちもやる
    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 0); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

            isogeny_mgec3(&R, &R, &tmp_a);
            //efp2_ecd(&R, &R, &a, &b);
            printf("a");
            
        }

        // Rを2or3同種写像で求める
        //isogeny_changeb(fp2_t *nexta, fp2_t *nextb, fp2_t *beta, fp2_t *olda, fp2_t *oldb)
        isogeny_changeb(&tmp_a, &Eb, &R.x, &tmp_a, &Eb);
        fp2_printf("newa = ", &tmp_a);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(&S, &S, &R.x, 3);

        efp2_recover_y(&S, S.x);

    }

    efp2_set(&R, &S);
    //fp2_printf("Rx = ", &R.x);
    isogeny_changeb(&tmp_a, &Eb, &R.x, &tmp_a, &Eb);
    fp2_printf("newa = ", &tmp_a);

    // 最後のaを使ってjvalを両者で求める

    isogeny_getj(&jb, &Ea);

    // 比較して同じなら共有成功
    if(fp2_cmp(&ja, &jb) == 0){

        printf("keycon OK.\n");
        fp2_printf("ja = ", &ja);
        fp2_printf("jb = ", &jb);

    }else{

        printf("keycon Failed!!\n");
        fp2_printf("ja = ", &ja);
        fp2_printf("jb = ", &jb);

    }
}

void keygen(){
    // 鍵生成

    printf("keygen starts.\n");

    gmp_randinit_default(state);
    gmp_randseed_ui(state, (unsigned long)time(NULL));
    gmp_randseed_ui(state, 1);

    efp2_t P2, Q2, P3, Q3;
    efp2_init(&P2);
    efp2_init(&Q2);
    efp2_init(&P3);
    efp2_init(&Q3);

    // efp2_rational_point(&P3);
    // efp2_rational_point(&Q3);
    efp2_set_a_b_c_d(&P3, 275, 358, 104, 410);
    efp2_set_a_b_c_d(&Q3, 185, 20, 239, 281);
    efp2_set_a_b_c_d(&P2, 248, 100, 199, 304);
    efp2_set_a_b_c_d(&Q2, 394, 426, 79, 51);
    // efp2_println("P3 = ",&P3);
    // efp2_println("Q3 = ",&Q3);
    printf("---------------------------------\n");

    // 秘密鍵
    // ka, kb createで作るよ

    // p = 2^ea*3^eb - 1 eaとebはcreateで作成

    // getsでSを求める
    efp2_t S, R;
    efp2_init(&S);
    efp2_init(&R);

    //printf("gets\n");

    isogeny_gets(&S, &P2, &Q2, ka_z, &Ea);

    //efp2_checkOnCurve(&S, &Ea, &Eb);
    // fp2_printf("Ea = ", &Ea);
    // efp2_printf("S = ", &S);

    mpz_t j, i;
    mpz_init(j);
    mpz_init(i);

    //printf("isogeny-2 loop\n");

    mpz_set(j, ea_z);

    // ループ(R=Sまで)
    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 0); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

        efp2_ecd(&R, &R, &Ea, &Eb);

        //efp2_checkOnCurve(&R, &a2, &b);

        //efp2_printf("R = ", &R);
        //getchar();
        //printf("a");

        }

        // printf("R check\n");
        // efp2_checkOnCurve(&R, &Ea, &Eb);

        // Rを2or3同種写像で求める
        //isogeny_changea(fp2_t *nexta, fp2_t *nextb, fp2_t *oldb, fp2_t *alpha)
        isogeny_changea(&Ea, &Eb, &Eb, &R.x);

        // fp2_printf("Rx = ", &R.x);
        // fp2_printf("newa = ", &Ea);
        // fp2_printf("newb = ", &Eb);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(&P3, &P3, &R.x, 2);
        isogeny_nextp(&Q3, &Q3, &R.x, 2);
        isogeny_nextp(&S, &S, &R.x, 2);

        // efp2_printf("P = ", &P3);
        // efp2_printf("Q = ", &Q3);
        // efp2_printf("S = ", &S);
        
        efp2_recover_y(&S, S.x);

        // printf("S check\n");
        // efp2_checkOnCurve(&S, &Ea, &Eb);
        
        // efp2_printf("S = ", &S);

        //gmp_printf("j: %Zd\n", j);

        //getchar();

    }

    //printf("recover_y\n");

    efp2_set(&R, &S);
    isogeny_changea(&Ea, &Eb, &Eb, &R.x);

    // fp2_printf("Rx = ", &R.x);
    // fp2_printf("newa = ", &Ea);
    // fp2_printf("newb = ", &Eb);

    // Rxを使ってP,Qを更新する
    isogeny_nextp(&P3, &P3, &R.x, 2);
    isogeny_nextp(&Q3, &Q3, &R.x, 2);

    // efp2_printf("P = ", &P3);
    // efp2_printf("Q = ", &Q3);

    efp2_recover_y(&P3, P3.x);
    efp2_recover_y(&Q3, Q3.x);

    // efp2_checkOnCurve(&P3, &Ea, &Eb);
    // efp2_checkOnCurve(&Q3, &Ea, &Eb);

    //結果保持
    fp2_set(&tmp_a, &Ea);
    fp2_set(&tmp_b, &Eb);
    
    efp2_set(&Ptmp3, &P3);
    efp2_set(&Qtmp3, &Q3);

    // efp2_printf("P'3 = ", &Ptmp3);
    // efp2_printf("Q'3 = ", &Qtmp3);
    // fp2_printf("a' = ", &tmp_a);

    //printf("---------------------------------\n");

    // efp2_println("P2 = ",&P2);
    // efp2_println("Q2 = ",&Q2);

    //リセット
    fp2_set_ui_ui(&Ea, 329);
    fp2_add_ui(&Ea, &Ea, 94);
    fp2_set_ui(&Eb, 1);
    efp2_set_a_b_c_d(&P3, 275, 358, 104, 410);
    efp2_set_a_b_c_d(&Q3, 185, 20, 239, 281);

    isogeny_gets(&S, &P3, &Q3, kb_z, &Ea);

    // efp2_checkOnCurve(&S, &Ea, &Eb);
    // efp2_printf("S = ", &S);

    // Alice, Bobどっちもやる

    mpz_set(j, eb_z);


    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 0); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

            isogeny_mgec3(&R, &R, &Ea);
            //efp2_ecd(&R, &R, &a, &b);
            //printf("a");
            
        }

        // Rを2or3同種写像で求める
        //isogeny_changeb(fp2_t *nexta, fp2_t *nextb, fp2_t *beta, fp2_t *olda, fp2_t *oldb)
        isogeny_changeb(&Ea, &Eb, &R.x, &Ea, &Eb);

        // fp2_printf("Rx = ", &R.x);
        // fp2_printf("newa = ", &Ea);
        // fp2_printf("newb = ", &Eb);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(&P2, &P2, &R.x, 3);
        isogeny_nextp(&Q2, &Q2, &R.x, 3);
        isogeny_nextp(&S, &S, &R.x, 3);

        // efp2_printf("P = ", &P2);
        // efp2_printf("Q = ", &Q2);
        // efp2_printf("S = ", &S);

        efp2_recover_y(&S, S.x);

        // printf("S check\n");
        // efp2_checkOnCurve(&S, &Ea, &Eb);
        // efp2_printf("S = ", &S);

    }

    //fp2_printf("Rx = ", &R.x);

    efp2_set(&R, &S);
    //fp2_printf("Rx = ", &R.x);
    isogeny_changeb(&Ea, &Eb, &R.x, &Ea, &Eb);

    // fp2_printf("newa = ", &Ea);
    // fp2_printf("newb = ", &Eb);

    // Rxを使ってP,Q,Sを更新する
    isogeny_nextp(&P2, &P2, &R.x, 3);
    isogeny_nextp(&Q2, &Q2, &R.x, 3);
    // efp2_printf("P = ", &P2);
    // efp2_printf("Q = ", &Q2);

    efp2_recover_y(&P2, P2.x);
    efp2_recover_y(&Q2, Q2.x);

    // efp2_checkOnCurve(&P2, &Ea, &Eb);
    // efp2_checkOnCurve(&Q2, &Ea, &Eb);

    // A(P,Q,a), B(P.Q.a)

    printf("Aliceの鍵:");
    efp2_println("P3 = ",&Ptmp3);
    efp2_println("Q3 = ",&Qtmp3);
    fp2_println("a = ", &tmp_a);

    printf("Bobの鍵:");
    efp2_println("P2 = ",&P2);
    efp2_println("Q2 = ",&Q2);
    fp2_println("a = ", &Ea);

    keycon(&P2, &Q2, &Ptmp3, &Qtmp3);

}

