#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>
#include <time.h>
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
    if(mpz_cmp_si(in1->x0, x0) == 0){
        if(mpz_cmp_si(in1->x1, x1) == 0){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int fp2_cmp_n(fp2 *in1, fp2 *in2){
    if(mpz_cmp(in1->x0, in2->x0) >= 0 && mpz_cmp(in1->x1, in2->x1) >= 0){
        return 1;
    }else{
        return -1;
    }
}

void fp2_printf(fp2 *in){
    gmp_printf("(%Zd, %Zd)\n", in->x0, in->x1);
}

void fp2_mod(fp2 *ans, fp2 *in){
    if(mpz_sgn (in->x0) != -1){
        mpz_mod (ans->x0, in->x0, prime_z);
    }else{
        while(mpz_sgn (in->x0) < 0){
            mpz_add (in->x0, in->x0, prime_z);
        }
    }
    if(mpz_sgn (in->x1) != -1){
        mpz_mod (ans->x1, in->x1, prime_z);
    }else{
        while(mpz_sgn (in->x1) < 0){
            mpz_add (in->x1, in->x1, prime_z);
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
    mpz_set(modp->x0, prime_z); mpz_set(modp->x1, prime_z);
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

    int i,length;

    length=(int)mpz_sizeinbase(d,2);

    char binary[length+1];

    mpz_get_str(binary , 2, d);

    fp2 tmp;

    fp2_init(&tmp);

    fp2_set(&tmp, c);



    for(i=1;i<length; i++){
        //printf("bin[%d]: %c\n", i, binary[i]);

        fp2_mul(&tmp, &tmp, &tmp);

        if(binary[i]=='1')  fp2_mul(&tmp, c, &tmp);

    }

    fp2_set(ans,&tmp);
}

int fp2_legendre(fp2 *in){
    // legendre //
    mpz_t work;
    fp2 temp, ans;
    fp2_init(&temp);
    fp2_init(&ans);
    fp2_set(&temp, in);
    mpz_init(work);
    mpz_mul(work, prime_z,prime_z);
    mpz_sub_ui(work,work,1);
    mpz_div_ui(work,work,2);

    fp2_scalarexp(&ans, &temp, work);
    if(fp2_cmp_ui(&ans, 1, 0) == 0){
        return 1;
    }else{
        return -1;
    }
}

void fp2_inv(fp2 *ans, fp2 *in){
    mpz_t two,d,pp, fp2_order;
    mpz_init(d); 
    mpz_init(pp);
    mpz_init(two);
    mpz_init(fp2_order);
    mpz_set(pp, prime_z);
    mpz_set_ui(two, 2);
    mpz_mul(d, pp, pp);
    mpz_sub(d, d, two);
    mpz_mul(fp2_order,prime_z,prime_z);
    mpz_sub_ui(fp2_order,fp2_order,1);
    mpz_mod(d, d, fp2_order);
    fp2 w;
    fp2 *wp;
    wp = &w;
    fp2_init(wp);
    if(mpz_cmp_si(in->x0, 0) == 0 && mpz_cmp_si(in->x1, 0) == 0){
        //printf("in = 0,0 \n");
        mpz_set_si(wp->x0, 1); mpz_set_si(wp->x1, 0);
    }else{
        fp2_scalarexp(wp, in, d);
    }
    //fp2_printf(wp);
    fp2_set(ans, wp);
}

void fp2_sqrt(fp2 *ANS, fp2 *A){
  fp2 x,y,t,k,n,tmp;
  fp2_init(&x);
  fp2_init(&y);
  fp2_init(&t);
  fp2_init(&k);
  fp2_init(&n);
  fp2_init(&tmp);
  unsigned long int e,m;
  mpz_t exp,q,z,result;
  mpz_init(exp);
  mpz_init(q);
  mpz_init(z);
  mpz_init(result);
  gmp_randstate_t state;
  gmp_randinit_default(state);
  gmp_randseed_ui(state,(unsigned long)time(NULL));

    mpz_urandomm(n.x0, state, prime_z);
    mpz_urandomm(n.x1, state, prime_z);
    while(fp2_legendre(&n)!=-1){
        mpz_urandomm(n.x0, state, prime_z);
        mpz_urandomm(n.x1, state, prime_z);
    }

  mpz_pow_ui(q,prime_z,2);
  mpz_sub_ui(q,q,1);
  mpz_mod_ui(result,q,2);
  e=0;
  while(mpz_cmp_ui(result,0)==0){
    mpz_tdiv_q_ui(q,q,2);
    mpz_mod_ui(result,q,2);
    e++;

  }
  fp2_scalarexp(&y,&n,q);
  mpz_set_ui(z,e);
  mpz_sub_ui(exp,q,1);
  mpz_tdiv_q_ui(exp,exp,2);
  fp2_scalarexp(&x,A,exp);
  fp2_mul(&tmp,&x,&x);
  fp2_mul(&k,&tmp,A);
  fp2_mul(&x,&x,A);
  while(fp2_cmp_ui(&k,1,0)!=0){
    m=1;
    mpz_ui_pow_ui(exp,2,m);
    fp2_scalarexp(&tmp,&k,exp);
    while(fp2_cmp_ui(&tmp,1,0)!=0){
      m++;
      mpz_ui_pow_ui(exp,2,m);
      fp2_scalarexp(&tmp,&k,exp);
    }
    mpz_sub_ui(exp,z,m);
    mpz_sub_ui(exp,exp,1);
    mpz_ui_pow_ui(result,2,mpz_get_ui(exp));
    fp2_scalarexp(&t,&y,result);
    fp2_mul(&y,&t,&t);
    mpz_set_ui(z,m);
    fp2_mul(&x,&x,&t);
    fp2_mul(&k,&k,&y);
  }
  fp2_set(ANS,&x);

  mpz_clear(exp);
  mpz_clear(q);
  mpz_clear(z);
  mpz_clear(result);
}

void fp2_sqrt_34(fp2 *ANS, fp2 *A){
    fp2 temp, alpha, temp2, temp3;
    fp2_init(&temp);
    fp2_init(&alpha);
    fp2_init(&temp2);
    fp2_init(&temp3);

    fp2 i;
    fp2_init(&i);
    fp2_set_ui(&i, 0, 1);

    mpz_t q, three;
    mpz_init(q);
    mpz_init(three);

    mpz_set_ui(three, 3);

    mpz_set(q, prime_z);
    fp_sub(q, q, three);
    mpz_div_ui(q, q, 4);

    fp2_scalarexp(&temp, A, q);

    //fp2_printf(&temp);

    fp2_mul(&alpha, &temp, A);
    fp2_mul(&alpha, &temp, &alpha);

    //fp2_printf(&alpha);

    fp2_scalarexp(&temp2, &alpha, prime_z);
    fp2_mul(&temp2, &temp2, &alpha);

    //fp2_printf(&temp2);

    // if(fp2_cmp_ui(&temp2, 430, 0)){
    //     printf("no sqrt\n");
    // }else{
    fp2_mul(&temp3, &temp, A);
    if(fp2_cmp_ui(&alpha, 430, 0)){
        fp2_mul(ANS, &i, &temp3);
    }else{
        mpz_set(q, prime_z);

        fp2 one;
        fp2_init(&one);
        fp2_set_ui(&one, 1, 0);

        mpz_t ichi;
        mpz_init(ichi);
        mpz_set_ui(ichi, 1);

        fp_sub(q, q, ichi);
        mpz_div_ui(q, q, 2);

        fp2_add(&temp, &alpha, &one);
        fp2_scalarexp(&temp2, &temp, q);

        fp2_mul(ANS, &temp2, &temp3);
    }
    // }
}