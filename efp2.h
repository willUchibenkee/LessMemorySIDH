// efp2.h(Montgomery)

#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>
#include<stdlib.h>
#include"fp2.h"

typedef struct ec2
{
    fp2 x;
    fp2 y;
    mpz_t inf;
    // 楕円曲線の点 無限遠にいったらinfを１に
}ec2;

//点の出力
int PrintEC2(ec2 *op){
    if(mpz_cmp_ui(op->inf, 1) == 0 )printf("!Inf!\n");
    else gmp_printf("(x(a,b),y(c,d))=((%Zd,%Zd),(%Zd,%Zd))\n",op->x.x0,op->x.x1, op->y.x0, op->y.x1);
}

int fp2_checkans(ec2 *P, fp2 *ap){
    fp2 wx, wy, uhen, sahen, work;
    fp2 *wxp; fp2 *wyp;
    wxp = &wx; wyp = &wy;
    fp2 *uhenp; fp2 *sahenp;
    uhenp = &uhen; sahenp = &sahen;
    fp2 *wp; wp = &work;
    //printf("check ans start\n");
    fp2_init(wxp);
    fp2_init(wyp);
    //printf("a\n");
    fp2_set(wxp, &P->x);
    //printf("b\n");
    fp2_set(wyp, &P->y);
    fp2_init(uhenp);
    fp2_init(sahenp);
    fp2_init(wp);
    mpz_t three;
    fp2 bt; fp2 *bp;
    bp = &bt;
    mpz_init(three);
    fp2_init(bp);
    mpz_set_ui(three, 3);
    fp2_set_ui(bp, B, 0);
    fp2_mul(sahenp, wyp, wyp);
    fp2_mul(sahenp, sahenp, bp);
    fp2_scalarexp(uhenp, wxp, three);
    fp2_mul(wp, wxp, wxp);
    fp2_mul(wp, wp, ap);
    fp2_add(uhenp, uhenp, wp);
    fp2_add(uhenp, uhenp, wxp);
    if(fp2_cmp(uhenp, sahenp) == 0){
        return 0;
    }else{
        return 1;
    }
}

void fp2_mgecD(ec2 *R, ec2 *P, fp2 *ap){
    fp2 bumbo, bunshi, bumbo2, bunshi2, katamari, katamari2;
    fp2 *bumbop; bumbop = &bumbo;
    fp2 *bunship; bunship = &bunshi;
    fp2 *bumbo2p; bumbo2p = &bumbo2;
    fp2 *bunshi2p; bunshi2p = &bunshi2;
    fp2 *katamarip; katamarip = &katamari;
    fp2 *katamari2p; katamari2p = &katamari2;
    mpz_t two, three;
    fp2 one, four, two2, three2, bt;
    fp2 *op; op = &one;
    fp2 *fp; fp = &four;
    fp2 *t2p; t2p = &two2;
    fp2 *tr2p; tr2p = &three2;
    fp2 *bp; bp = &bt;
    fp2 work, work2, work3;
    fp2 *wp; wp = &work;
    fp2 *w2p; w2p = &work2;
    fp2 *w3p; w3p = &work3;
    ec2 U; ec2 *up; up = &U;
    mpz_init(two);
    mpz_init(three);
    fp2_init(&up->x);
    fp2_init(&up->y);
    mpz_init(up->inf);
    fp2_init(bumbop);
    fp2_init(bunship);
    fp2_init(bumbo2p);
    fp2_init(bunshi2p);
    fp2_init(katamarip);
    fp2_init(katamari2p);
    fp2_init(op);
    fp2_init(bp);
    fp2_init(fp);
    fp2_init(t2p);
    fp2_init(tr2p);
    fp2_init(wp);
    fp2_init(w2p);
    fp2_init(w3p);
    fp2_set_ui(op, 1, 0);
    fp2_set_ui(bp, B, 0);
    fp2_set_ui(fp, 4, 0);
    mpz_set_ui(two, 2);
    mpz_set_ui(three, 3);
    fp2_set_ui(t2p, 2, 0);
    fp2_set_ui(tr2p, 3, 0);

    //fp2_printf(&P->x);

    //printf("ecd start \n");
    if(mpz_cmp_ui(P->inf, 1) == 0){
        //printf("a\n");
        mpz_set_ui(R->inf, 1);
    }else{
        if(fp2_cmp_ui(&P->x, 0, 0) == 0 || fp2_cmp_ui(&P->y, 0, 0) == 0){
            mpz_set_ui(P->inf, 1);
            //printf("b\n");
        }else{
            //x座標
            //分子の計算
            //printf("x \n");
            fp2_mul(bunship, &P->x, &P->x);
            //fp2_printf(bunship);
            fp2_sub(bunship, bunship, op);
            //fp2_printf(bunship);
            fp2_mul(bunship, bunship, bunship);
            //printf("bunshi:");
            // fp2_printf(bunship);
            //gmp_printf("bunshi = %Zd\n", bunshi);
            //分母の計算(最後にinv)
            //printf("bumbo \n");
            fp2_mul(bumbop, &P->x, &P->x);
            //fp2_printf(bumbop);
            fp2_mul(wp, ap, &P->x);
            //fp2_printf(wp);
            fp2_add(bumbop, bumbop, wp);
            //fp2_printf(bumbop);
            fp2_add(bumbop, bumbop, op);
            //fp2_printf(bumbop);
            fp2_mul(bumbop, bumbop, &P->x);
            //fp2_printf(bumbop);
            fp2_mul(bumbop, bumbop, fp);
            //fp2_printf(bumbop);
            //gmp_printf("bumbo = %Zd\n", bumbo);
            //printf("bumbo inv \n");
            fp2_inv(bumbop, bumbop);
            // printf("bumbo:");
            // fp2_printf(bumbop);
            //gmp_printf("bumbo = %Zd\n", bumbo);
            //分子/分母
            //printf("x ok\n");
            fp2_mul(&up->x, bunship, bumbop);
            // printf("U.x:");
            // fp2_printf(&up->x);
            //y座標
            //かたまり１
            //分子の計算
            //gmp_printf("two = %Zd\n", two);
            //gmp_printf("x = %Zd\n", P->x);
            //printf("katamari1\n");
            fp2_mul(wp, &P->x, t2p);
            //gmp_printf("2x = %Zd\n", work);
            fp2_add(wp, wp, &P->x);
            //gmp_printf("3x = %Zd\n", work);
            fp2_add(wp, wp, ap);
            //gmp_printf("work = %Zd\n", work);
            fp2_mul(w2p, &P->x, &P->x);
            fp2_mul(w2p, w2p, tr2p);
            fp2_mul(w3p, &P->x, ap);
            fp2_mul(w3p, w3p, t2p);
            fp2_add(w2p, w2p, w3p);
            fp2_add(w2p, w2p, op);
            //gmp_printf("work2 = %Zd\n", work2);
            
            fp2_mul(bunship, wp, w2p);
            // printf("bunshi:");
            // fp2_printf(bunship);
            //gmp_printf("bunshi = %Zd\n", bunshi);
            //分母の計算(最後にinv)
            //printf("bumbo1\n");
            fp2_mul(bumbop, t2p, bp);
            fp2_mul(bumbop, bumbop, &P->y);
            
            fp2_set(bumbo2p, bumbop);
            fp2_inv(bumbop, bumbop);
            // printf("inv 2y:");
            // fp2_printf(bumbop);
            //gmp_printf("bumbo = %Zd\n", bumbo);
            //分子/分母
            fp2_mul(katamarip, bunship, bumbop);
            // printf("katamari:");
            // fp2_printf(katamarip);
            //printf("katamari1 ok\n");
            //かたまり２
            //分子の計算
            //printf("katamari2\n");
            fp2_scalarexp(bunshi2p, w2p, three);
            fp2_mul(bunshi2p, bunshi2p, bp);
            // printf("bunshi2:");
            // fp2_printf(bunshi2p);
            //gmp_printf("bunshi = %Zd\n", bunshi);
            //分母の計算(最後にinv)
            fp2_scalarexp(bumbo2p, bumbo2p, three);
            fp2_inv(bumbo2p, bumbo2p);
            //gmp_printf("bumbo = %Zd\n", bumbo);
            //分子/分母
            fp2_mul(katamari2p, bunshi2p, bumbo2p);
            fp2_sub(&up->y, katamarip, katamari2p);
            fp2_sub(&up->y, &up->y, &P->y);
            // printf("U.y:");
            // fp2_printf(&up->y);
            //printf("R set\n");
            fp2_set(&R->x, &up->x);
            fp2_set(&R->y, &up->y);
            //printf("R ok\n");
        }
    }
    
}

void fp2_mgecA(ec2 *R, ec2 *P, ec2 *Q, fp2 *ap){
    fp2 bumbo, bunshi, bumbo2, bunshi2;
    fp2 *bumbop; bumbop = &bumbo;
    fp2 *bunship; bunship = &bunshi;
    fp2 *bumbo2p; bumbo2p = &bumbo2;
    fp2 *bunshi2p; bunshi2p = &bunshi2;
    fp2 xsa, ysa, work, work2, katamari, katamari2, temp, temp2;
    fp2 *xsap; xsap = &xsa;
    fp2 *ysap; ysap = &ysa;
    fp2 *wp; wp = &work;
    fp2 *w2p; w2p = &work2;
    fp2 *katamarip; katamarip = &katamari;
    fp2 *katamari2p; katamari2p =&katamari2;
    fp2 *tempp; tempp = &temp;
    fp2 *temp2p; temp2p = &temp2;
    fp2 two, bt;
    fp2 *t2p; t2p = &two;
    fp2 *bp; bp = &bt;
    mpz_t three;
    fp2_init(bumbop);
    fp2_init(bumbo2p);
    fp2_init(bunship);
    fp2_init(bunshi2p);
    fp2_init(xsap);
    fp2_init(ysap);
    fp2_init(wp);
    fp2_init(w2p);
    fp2_init(katamarip);
    fp2_init(katamari2p);
    fp2_init(tempp);
    fp2_init(temp2p);
    fp2_init(t2p);
    mpz_init(three);
    fp2_init(bp);
    fp2_set_ui(t2p, 2, 0);
    mpz_set_ui(three, 3);
    fp2_set_ui(bp, B, 0);

    //printf("set ok \n");
    if(mpz_cmp_ui(P->inf, 1) == 0){
        if(mpz_cmp_ui(Q->inf, 1) == 0){
            mpz_set_ui(R->inf, 1);
            //printf("P,Q inf\n");
        }else{
            fp2_set(&R->x, &Q->x);
            fp2_set(&R->y, &Q->y);
            mpz_set_ui(R->inf, 0);
            //printf("Q = R \n");
         }
    }else{
        if(mpz_cmp_ui(Q->inf, 1) == 0){
            fp2_set(&R->x, &P->x);
            fp2_set(&R->y, &P->y);
            mpz_set_ui(R->inf, 0);
            //printf("P = R \n");
        }else{
            if(fp2_cmp(&P->x, &Q->x) == 0 || fp2_cmp(&P->y, &Q->y) == 0){
                if(fp2_cmp(&P->x, &Q->x) == 0 && fp2_cmp(&P->y, &Q->y) == 0){
                    fp2_mgecD(R, P, ap);
                    //printf("R = 2P or 2Q \n");
                }else{
                    //gmp_printf("inf gen\n");
                    mpz_set_ui(R->inf, 1);
                }
            }else{
                //printf("eca start \n");
                //gmp_printf("P(%Zd, %Zd) Q(%Zd, %Zd)\n", P->x, P->y, Q->x, Q->y);
                fp2_sub(xsap, &Q->x, &P->x);
                fp2_sub(ysap, &Q->y, &P->y);
                //x座標
                //分子の計算
                fp2_mul(wp, &Q->x, &P->y);
                fp2_mul(w2p, &Q->y, &P->x);
                fp2_sub(bunship, wp, w2p); 
                fp2_mul(bunship, bunship, bunship);
                fp2_mul(bunship, bunship, bp);
                
                //分母の計算(最後にinv)
                fp2_mul(wp, xsap, xsap);
                fp2_mul(bumbop, wp, &P->x);
                fp2_mul(bumbop, bumbop, &Q->x);
                fp2_inv(bumbop, bumbop);

                //分子/分母
                fp2_mul(temp2p, bumbop, bunship);

                //y座標
                //かたまり１
                //分子の計算
                fp2_mul(bunship, &P->x, t2p);
                //gmp_printf("px = %Zd\n", P->x);
                //gmp_printf("two = %Zd\n", two);
                //gmp_printf("bunshi1 = %Zd\n", bunshi);
                fp2_add(bunship, bunship, &Q->x);
                //gmp_printf("bunshi1 = %Zd\n", bunshi);
                fp2_add(bunship, bunship, ap);
                //gmp_printf("bunshi1 = %Zd\n", bunshi);
                fp2_mul(bunship, bunship, ysap);
                //gmp_printf("bunshi1 = %Zd\n", bunshi);
                //getchar();

                //分母の計算(最後にinv)
                fp2_inv(bumbop, xsap);
                //gmp_printf("bumbo1 = %Zd\n", bumbo);

                //分子/分母
                fp2_mul(katamarip, bumbop, bunship);

                //かたまり２
                //分子の計算
                fp2_scalarexp(bunshi2p, ysap, three);
                fp2_mul(bunshi2p, bunshi2p, bp);
                //gmp_printf("bunshi2 = %Zd\n", bunshi2);

                //分母の計算(最後にinv)
                fp2_scalarexp(bumbo2p, xsap, three);
                fp2_inv(bumbo2p, bumbo2p);
                //gmp_printf("bumbo2 = %Zd\n", bumbo2);

                //分子/分母
                fp2_mul(katamari2p, bumbo2p, bunshi2p);
                fp2_sub(tempp, katamarip, katamari2p);
                fp2_sub(&R->y, tempp, &P->y);
                fp2_set(&R->x, temp2p);
            }
        }
    }   
}

void fp2_mgecSCM(ec2 *R, ec2 *P, mpz_t n, fp2 *ap){
    ec2 S,T;
    ec2 *sp; ec2 *tp;
    sp = &S; tp = &T;
    fp2_init(&sp->x);
    fp2_init(&sp->y);
    mpz_init(sp->inf);
    mpz_set_ui(sp->inf, 1);
    fp2_init(&tp->x);
    fp2_init(&tp->y);
    mpz_init(tp->inf);
    int length = 0;
    length = (int)mpz_sizeinbase(n, 2);
    char binary[length + 1];
    fp2_set(&tp->x, &P->x);
    fp2_set(&tp->y, &P->y);
    mpz_set(tp->inf, P->inf);
    //PrintEC2(tp);

    if(mpz_cmp_ui(n, 1) == 0){
        fp2_set(&R->x, &P->x);
        fp2_set(&R->y, &P->y);
    }else{
        mpz_get_str(binary, 2, n);
        for(int k = length-1; k >= 0; k--){
            // printf("k = %d \n", k);
            // printf("bin[k]: %c\n", binary[k]);
            //if(k == 5 || k ==4){
                //gmp_printf("S.inf: %Zd  T.inf: %Zd\n", sp->inf, tp->inf);
            //}
            if(binary[k] == '1'){
                //printf("bin[k] == 1 \n");
                fp2_mgecA(sp, sp, tp, ap);
                // if(fp2_checkans(sp, ap) == 0){
                //     printf("after ECA S:");
                //     PrintEC2(sp);
                //     getchar();
                // }else{
                //     //printf("ECA failed\n");
                // }
                if(mpz_cmp_ui(sp->inf, 1) == 0){
                    //printf("S = inf\n");
                }else{
                    //printf("after ECA \nT:");
                    //PrintEC2(sp);
                }
            }
            fp2_mgecD(tp, tp, ap);
            //printf("ecd ok\n");
            if(fp2_checkans(tp, ap) == 1){
                //printf("ECD failed\n");
            }
            if(mpz_cmp_ui(tp->inf, 1) == 0){
                //printf("T = inf\n");
            }else{
                //printf("after ECD \nT:");
                //PrintEC2(tp);
            }
        }
        fp2_set(&R->x, &sp->x);
        fp2_set(&R->y, &sp->y);
        mpz_set(R->inf, sp->inf);
    }
}

