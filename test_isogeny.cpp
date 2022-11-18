//test_isogeny.cpp

#include "test_isogeny.h"
#include "isogeny.h"
#include <cstdio>

/*①補助点P,QからSを計算(eca,scm P+kQ)
　②SからRを計算 (αの決定 ecd or ect)
　③αからP,Q,S,aを再決定 (changea(), nextp())
　最終形 PKa (Pb, Qb, aA), PKb(Pa, Qa, aB)
　ある関数：gets(), changa(), changeb(), nextp(), eca(), ecd(), scm(), ect(), gety(), getj()
　作る関数　keygen():公開鍵作成まで keyexcng():j不変量一致まで*/

void keycon(efp2_t *P2, efp2_t *Q2, efp2_t *P3, efp2_t *Q3){
    // 鍵共有

    printf("keycon starts.\n");

    efp2_t S, R;
    efp2_init(&S);
    efp2_init(&R);

    //Ea, Eb: Bobのパラメータ  tmp_a, tmp_b: Aliceのパラメータ
    //Aliceの鍵共有から行う　Bobの点と楕円曲線パラメータを使ってkaで計算

    isogeny_gets(&S, P3, Q3, ka_z, &Ea);
    efp2_checkOnCurve(&S, &Ea, &Eb);

    // ループ(R=Sまで)

    mpz_t j, i;
    mpz_init(j);
    mpz_init(i);

    mpz_set(j, ea_z);

    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 1); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

            efp2_ecd(&R, &R, &Ea, &Eb);

        }

        // Rを2or3同種写像で求める
        isogeny_changea(&Ea, &Eb, &Eb, &R.x);

        efp2_checkOnCurve(&R, &Ea, &Eb);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(P3, P3, &R.x, 2);
        isogeny_nextp(Q3, Q3, &R.x, 2);
        isogeny_nextp(&S, &S, &R.x, 2);

        //efp2_recover_y(&S, S.x);

    }

    isogeny_gets(&S, P2, Q2, kb_z, &Ea);

    efp2_checkOnCurve(&S, &Ea, &Eb);

    fp2_t ja, jb;
    fp2_init(&ja);
    fp2_init(&jb);
    isogeny_getj(&ja, &Ea);

    fp2_set(&Ea, &tmp_a);
    fp2_set(&Eb, &tmp_b);

    mpz_set(j, eb_z);

    // Alice, Bobどっちもやる
    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 1); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

            isogeny_mgec3(&R, &R, &Ea);
            //efp2_ecd(&R, &R, &a, &b);
            
        }

        // Rを2or3同種写像で求める
        //isogeny_changeb(fp2_t *nexta, fp2_t *nextb, fp2_t *beta, fp2_t *olda, fp2_t *oldb)
        isogeny_changeb(&Ea, &Eb, &R.x, &Ea, &Eb);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(P2, P2, &R.x, 3);
        isogeny_nextp(Q2, Q2, &R.x, 3);
        isogeny_nextp(&S, &S, &R.x, 3);

        efp2_recover_y(&S, S.x);

    }

    // 最後のaを使ってjvalを両者で求める

    isogeny_getj(&jb, &Ea);

    // 比較して同じなら共有成功
    if(fp2_cmp(&ja, &jb) == 0){

        printf("keycon OK.\n");

    }else{

        printf("keycon Failed!!\n");
        fp2_printf("ja = ", &ja);
        fp2_printf("jb = ", &jb);

    }
}

void keygen(){
    /*やること
    ①補助点P,QからSを計算(eca,scm P+kQ)
　　②SからRを計算 (αの決定 ecd or ect)
　　③αからP,Q,S,aを再決定 (changea(), nextp())
　　②、③は繰り返す*/
    printf("keygen starts.\n");

    gmp_randinit_default(state);
    gmp_randseed_ui(state, (unsigned long)time(NULL));
    gmp_randseed_ui(state, 1);

    efp2_t P2, Q2, P3, Q3;
    efp2_init(&P2);
    efp2_init(&Q2);
    efp2_init(&P3);
    efp2_init(&Q3);

    efp2_rational_point(&P3);
    efp2_rational_point(&Q3);
    // efp2_set_a_b_c_d(&P3, 275, 358, 104, 410);
    // efp2_set_a_b_c_d(&Q3, 185, 20, 239, 281);
    efp2_println("P3 = ",&P3);
    efp2_println("Q3 = ",&Q3);
    printf("---------------------------------\n");

    // 秘密鍵
    // ka, kb createで作るよ

    // p = 2^ea*3^eb - 1 eaとebはcreateで作成

    // getsでSを求める
    efp2_t S, R;
    efp2_init(&S);
    efp2_init(&R);

    printf("gets\n");

    isogeny_gets(&S, &P3, &Q3, ka_z, &Ea);

    efp2_checkOnCurve(&S, &Ea, &Eb);

    mpz_t j, i;
    mpz_init(j);
    mpz_init(i);

    printf("isogeny-2 loop\n");

    mpz_set(j, ea_z);

    // ループ(R=Sまで)
    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 1); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

            efp2_ecd(&R, &R, &Ea, &Eb);

            //efp2_checkOnCurve(&R, &a2, &b);

            //efp2_printf("R = ", &R);
            //getchar();

        }

        printf("R check\n");
        efp2_checkOnCurve(&R, &Ea, &Eb);

        // Rを2or3同種写像で求める
        //isogeny_changea(fp2_t *nexta, fp2_t *nextb, fp2_t *oldb, fp2_t *alpha)
        isogeny_changea(&Ea, &Eb, &Eb, &R.x);

        fp2_printf("Rx = ", &R.x);
        fp2_printf("newa = ", &Ea);
        fp2_printf("newb = ", &Eb);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(&P3, &P3, &R.x, 2);
        isogeny_nextp(&Q3, &Q3, &R.x, 2);
        isogeny_nextp(&S, &S, &R.x, 2);

        //efp2_recover_y(&S, S.x);

        printf("S check\n");
        //efp2_checkOnCurve(&S, &Ea, &Eb);

        //gmp_printf("j: %Zd\n", j);

        //getchar();

    }

    printf("recover_y\n");

    efp2_recover_y(&P3, P3.x);
    efp2_recover_y(&Q3, Q3.x);

    efp2_checkOnCurve(&P3, &Ea, &Eb);
    efp2_checkOnCurve(&Q3, &Ea, &Eb);

    fp2_set(&tmp_a, &Ea);
    fp2_set(&tmp_b, &Eb);

    printf("---------------------------------\n");

    efp2_rational_point(&P2);
    efp2_rational_point(&Q2);
    efp2_println("P2 = ",&P2);
    efp2_println("Q2 = ",&Q2);

    fp2_set_ui(&Ea, 6);
    fp2_set_ui(&Eb, 1);

    isogeny_gets(&S, &P2, &Q2, kb_z, &Ea);

    efp2_checkOnCurve(&S, &Ea, &Eb);

    // Alice, Bobどっちもやる

    mpz_set(j, eb_z);


    for(mpz_sub_ui(j, j, 1); mpz_cmp_ui(j, 0) > 0; mpz_sub_ui(j, j, 1)){

        efp2_set(&R, &S);

        for(mpz_set_ui(i, 1); mpz_cmp(i, j) < 0; mpz_add_ui(i, i, 1)){

            isogeny_mgec3(&R, &R, &Ea);
            //efp2_ecd(&R, &R, &a, &b);
            
        }

        // Rを2or3同種写像で求める
        //isogeny_changeb(fp2_t *nexta, fp2_t *nextb, fp2_t *beta, fp2_t *olda, fp2_t *oldb)
        isogeny_changeb(&Ea, &Eb, &R.x, &Ea, &Eb);

        efp2_checkOnCurve(&R, &Ea, &Eb);

        // Rxを使ってP,Q,Sを更新する
        isogeny_nextp(&P2, &P2, &R.x, 3);
        isogeny_nextp(&Q2, &Q2, &R.x, 3);
        isogeny_nextp(&S, &S, &R.x, 3);

        efp2_recover_y(&S, S.x);

    }

    efp2_recover_y(&P2, P2.x);
    efp2_recover_y(&Q2, Q2.x);

    efp2_checkOnCurve(&P2, &Ea, &Eb);
    efp2_checkOnCurve(&Q2, &Ea, &Eb);

    // A(P,Q,a), B(P.Q.a)

    printf("Aliceの鍵:");
    efp2_println("P3 = ",&P3);
    efp2_println("Q3 = ",&Q3);
    fp2_println("a = ", &Ea);

    printf("Bobの鍵:");
    efp2_println("P2 = ",&P2);
    efp2_println("Q2 = ",&Q2);
    fp2_println("a = ", &Ea);

    keycon(&P2, &Q2, &P3, &Q3);

}

