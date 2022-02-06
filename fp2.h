#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>
#include"fp.h"

#define Ax0 423
#define Ax1 329
#define B 1

//struct to express an Affine Rational Point on E/Fp
typedef struct fp2
{
    mpz_t x0;
    mpz_t x1;
}fp2;

void fp2_init(fp2 *in){
    mpz_init(in->x0);
    mpz_init(in->x1);
}

void fp2_set(fp2 *ans, fp2 *in){
    mpz_set(ans->x0, in->x0);
    mpz_set(ans->x1, in->x1);
}

void fp2_set_ui(fp2 *ans, int x0, int x1){
    mpz_set_ui(ans->x0, x0);
    mpz_set_ui(ans->x1, x1);
}

int fp2_cmp(fp2 *in1, fp2 *in2){
    if(mpz_cmp(in1->x0, in2->x0) == 0){
        if(mpz_cmp(in1->x1, in2->x1) == 0){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int fp2_cmp_ui(fp2 *in1, int x0, int x1){
    if(mpz_cmp_ui(in1->x0, x0) == 0){
        if(mpz_cmp_ui(in1->x1, x1) == 0){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

void fp2_printf(fp2 *in){
    gmp_printf("(%Zd, %Zd)\n", in->x0, in->x1);
}

void fp2_mod(fp2 *ans, fp2 *in){
    if(mpz_sgn (in->x0) != -1){
        mpz_mod_ui (ans->x0, in->x0, p);
    }else{
        while(mpz_sgn (in->x0) < 0){
            mpz_add_ui (in->x0, in->x0, p);
        }
    }
    if(mpz_sgn (in->x1) != -1){
        mpz_mod_ui (ans->x1, in->x1, p);
    }else{
        while(mpz_sgn (in->x1) < 0){
            mpz_add_ui (in->x1, in->x1, p);
        }
    }
}

void fp2_add(fp2 *ans, fp2 *in1, fp2 *in2){
    mpz_add(ans->x0, in1->x0, in2->x0);
    mpz_add(ans->x1, in1->x1, in2->x1);
    fp2_mod(ans, ans);
}

void fp2_neg(fp2 *ans, fp2 *in){
    mpz_neg(ans->x0, in->x0);
    mpz_neg(ans->x1, in->x1);
    fp2_mod(ans, ans);
}

void fp2_sub(fp2 *ans, fp2 *in1, fp2 *in2){
    fp2 neg;  fp2 *negp; negp = &neg;
    fp2_init(negp);
    fp2_neg(negp, in2);
    fp2_add(ans, in1, negp);
    fp2_mod(ans, ans);
}

void fp2_mul(fp2 *ans, fp2 *in1, fp2 *in2){
    // fp2 x,y; fp2 *xp; fp2 *yp;
    // xp = &x; yp = &y;
    // fp2_init(xp); fp2_init(yp);
    // fp_mul(xp->x0, in1->x0, in2->x0);
    // fp_mul(xp->x1, in1->x1, in2->x1); 
    // fp_neg(xp->x1, xp->x1);
    // fp_mul(yp->x1, in1->x0, in2->x1);
    // fp_mul(yp->x0, in1->x1, in2->x0);
    // fp_add(ans->x0, xp->x0, xp->x1);
    // fp_add(ans->x1, yp->x0, yp->x1);
    // fp2_mod(ans, ans);

    mpz_t t[2];
    mpz_init(t[0]);
    mpz_init(t[1]);
    
    fp_add(t[0], in1->x0, in1->x1);    //T0  141
    //gmp_printf("t[0] %Zd\n",t[0]);
    fp_add(t[1], in2->x0, in2->x1);    //T1  15c
    //gmp_printf("t[1] %Zd\n",t[1]);
    fp_mul(t[0], t[0], t[1]);   //T0=(a0+a1)*(b0+b1)  4f
    //gmp_printf("t[0] %Zd\n",t[0]);
    fp_mul(t[1], in1->x0, in2->x0);    //T0  ab
    //gmp_printf("t[1] %Zd\n",t[1]);
    fp_mul(ans->x1, in1->x1, in2->x1);    //T1  90
    //gmp_printf("ans->x1 %Zd\n",ans->x1);
    fp_sub(ans->x0, t[1], ans->x1);   //T4  1b
    //gmp_printf("ans->x0 %Zd\n",ans->x0);
    fp_add(t[1], ans->x1, t[1]);    //T3  13b
    //gmp_printf("t[1] %Zd\n",t[1]);
    fp_sub(ans->x1, t[0], t[1]);   //T3  c3
    //gmp_printf("ans->x1 %Zd\n",ans->x1);
}

void fp2_exp(fp2 *ans, fp2 *tei, mpz_t kata){
    mpz_set_ui(ans->x0, 1); mpz_set_ui(ans->x1, 0);
    fp2 mod; fp2 *modp; modp = &mod;
    fp2_init(modp);
    mpz_set_ui(modp->x0, p); mpz_set_ui(modp->x1, p);
    mpz_powm(ans->x0, tei->x0, kata, modp->x0);
    mpz_powm(ans->x1, tei->x1, kata, modp->x1);
}



void fp2_scalarmul(fp2 *ans, fp2 *c, fp2 *d){
    int length = 0; 
    length = (int)mpz_sizeinbase(d->x0, 2);
    char binary[length + 1]; 
    fp2 s,t; fp2 *sp; fp2 *tp;
    sp = &s; tp = &t;
    fp2_init(sp); fp2_init(tp);
    mpz_set_ui(sp->x0, 0); mpz_set(tp->x0, c->x0);
    mpz_set_ui(sp->x1, 0); mpz_set(tp->x1, c->x1);

    if(mpz_cmp_ui(d->x0, 0) == 0 || mpz_cmp_ui(d->x1, 0) == 0){
        mpz_set_ui(ans->x0, 0); mpz_set_ui(ans->x1, 0);
    }else{
        mpz_get_str(binary, 2, d->x0);
        mpz_get_str(binary, 2, d->x1);
        for(int k = length-1; k >= 0; k--){
            if(binary[k] == '1'){
                fp2_add(sp, sp, tp);
            }
            fp2_add(tp, tp, tp);
        }
        mpz_set(ans->x0, sp->x0); mpz_set(ans->x1, sp->x1);
    }

}

void fp2_scalarsub(fp2 *ans, fp2 *c, fp2 *d){
    int length = 0; 
    length = (int)mpz_sizeinbase(d->x0, 2);
    char binary[length + 1]; 
    fp2 s,t; fp2 *sp; fp2 *tp;
    sp = &s; tp = &t;
    fp2_init(sp); fp2_init(tp);
    mpz_set_ui(sp->x0, 0); mpz_set(tp->x0, c->x0);
    mpz_set_ui(sp->x1, 0); mpz_set(tp->x1, c->x1);

    if(mpz_cmp_ui(d->x0, 0) == 0 || mpz_cmp_ui(d->x1, 0) == 0){
        mpz_set_ui(ans->x0, 0); mpz_set_ui(ans->x1, 0);
    }else{
        mpz_get_str(binary, 2, d->x0);
        mpz_get_str(binary, 2, d->x1);
        for(int k = length-1; k >= 0; k--){
            if(binary[k] == '1'){
                fp2_sub(sp, sp, tp);
            }
            fp2_add(tp, tp, tp);
        }
        mpz_set(ans->x0, sp->x0); mpz_set(ans->x1, sp->x1);
    }

}

void fp2_scalarexp(fp2 *ans, fp2 *c, mpz_t d){
    int length = 0;
    length = (int)mpz_sizeinbase(d, 2);
    char binary[length + 1];
    fp2 s,t; fp2 *sp; fp2 *tp;
    sp = &s; tp = &t;
    fp2_init(sp); fp2_init(tp);
    mpz_set_ui(sp->x0, 1); mpz_set(tp->x0, c->x0);
    mpz_set_ui(sp->x1, 0); mpz_set(tp->x1, c->x1);

    if(mpz_cmp_ui(d, 0) == 0  || (mpz_cmp_ui(c->x0, 0) == 0 && mpz_cmp_ui(c->x1, 0) == 0)){
        mpz_set_ui(ans->x0, 1); mpz_set_ui(ans->x1, 0);
    }else{
        mpz_get_str(binary, 2, d);
        for(int k = length-1; k >= 0; k--){
            if(binary[k] == '1'){
                fp2_mul(sp, sp, tp);
            }
            fp2_mul(tp, tp, tp);
        }
        mpz_set(ans->x0, sp->x0); mpz_set(ans->x1, sp->x1);
    }
}

void fp2_legendre(fp2 *ans, fp2 *in){
    // legendre //
    mpz_t work;
    mpz_init(work);
    mpz_set_ui(work, (p*p-1)/2);
    fp2_scalarexp(ans, in, work);
}

void fp2_inv(fp2 *ans, fp2 *in){
    mpz_t two,d,pp;
    mpz_init(d); 
    mpz_init(pp);
    mpz_init(two);
    mpz_set_ui(pp, p);
    mpz_set_ui(two, 2);
    mpz_mul(d, pp, pp);
    mpz_sub(d, d, two);
    mpz_mod_ui(d, d, p*p-1);
    fp2 w;
    fp2 *wp;
    wp = &w;
    fp2_init(wp);
    if(mpz_cmp_ui(in->x0, 0) == 0 && mpz_cmp_ui(in->x1, 0) == 0){
        //printf("in = 0,0 \n");
        mpz_set_ui(wp->x0, 1); mpz_set_ui(wp->x1, 0);
    }else{
        fp2_scalarexp(wp, in, d);
    }
    //fp2_printf(wp);
    fp2_set(ans, wp);
}