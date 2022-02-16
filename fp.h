// fp.h //

#include<stdio.h>
#include<gmp.h>
#include<sys/time.h>

#define pval "0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"

// unsigned int p = 431;

mpz_t prime_z;

//struct to express an Affine Rational Point on E/Fp

// 補正をかける処理 //
void fp_mod(mpz_t ans, mpz_t in){
    if(mpz_sgn (in) != -1){
        mpz_mod (ans, in, prime_z);
    }else{
        while(mpz_sgn (in) < 0){
            mpz_add (in, in, prime_z);
        }
    }
}

void fp_mul(mpz_t ans, mpz_t in1, mpz_t in2){
    mpz_mul (ans, in1, in2);
    fp_mod(ans, ans);
}

// 〇乗 //
void fp_exp(mpz_t ans, mpz_t tei, mpz_t kata){
    mpz_set_ui(ans, 1);
    mpz_t mod; mpz_init(mod);
    mpz_set(mod, prime_z);
    mpz_powm(ans, tei, kata, mod);
}

// 逆数を求める //
void fp_inv(mpz_t ans, mpz_t in){
    mpz_t pdairi, tempin;
    mpz_init(pdairi);
    mpz_init(tempin);
    mpz_set(tempin, in);
    mpz_set(pdairi, prime_z);
    mpz_sub_ui(pdairi,pdairi,2);
    if(mpz_cmp_ui(tempin, 0) == 0){
        mpz_set_ui(ans, 1);
    }else{
        fp_exp(ans, tempin, pdairi);
        fp_mod(ans, ans);
    }
}

void fp_neg(mpz_t ans, mpz_t in){
    // 符号を反転させる演算 //
    mpz_neg (ans, in);
    fp_mod(ans, ans);
}

void fp_div(mpz_t ans, mpz_t upper, mpz_t lower){
    // 割り算 //
    printf("sub start\n");
    mpz_t inv;
    mpz_init(inv);
    fp_inv(inv, lower);
    fp_mul(ans, inv, upper);
    fp_mod(ans,ans);
    printf("sub end\n");
}

void fp_add(mpz_t ans, mpz_t in1, mpz_t in2){
    // 足し算 //
    mpz_add(ans, in1, in2);

    //gmp_printf("%Zd", ans);

    fp_mod(ans, ans);
}

void fp_sub(mpz_t ans, mpz_t in1, mpz_t in2){
    // 引き算 //
    mpz_t neg; mpz_init(neg);
    fp_neg(neg, in2);
    fp_add(ans, in1, neg);
    fp_mod(ans, ans);
}

void fp_scalarmul(mpz_t ans, mpz_t c, mpz_t d){
    int length = 0;
    length = (int)mpz_sizeinbase(d, 2);
    char binary[length + 1];
    mpz_t s,t;
    mpz_init(s); mpz_init(t);
    mpz_set_ui(s, 0); mpz_set(t, c);

    if(mpz_cmp_ui(d, 0) == 0){
        mpz_set_ui(ans, 0);
    }else{
        mpz_get_str(binary, 2, d);
        for(int k = length-1; k >= 0; k--){
            if(binary[k] == '1'){
                fp_add(s, s, t);
            }
            fp_add(t, t, t);
        }
        mpz_set(ans, s);
    }
}

void fp_scalarsub(mpz_t ans, mpz_t c, mpz_t d){
    int length = 0;
    length = (int)mpz_sizeinbase(d, 2);
    char binary[length + 1];
    mpz_t s,t;
    mpz_init(s); mpz_init(t);
    mpz_set_ui(s, 0); mpz_set(t, c);

    if(mpz_cmp_ui(d, 0) == 0){
        mpz_set_ui(ans, 0);
    }else{
        mpz_get_str(binary, 2, d);
        for(int k = length-1; k >= 0; k--){
            if(binary[k] == '1'){
                fp_sub(s, s, t);
            }
            fp_add(t, t, t);
        }
        mpz_set(ans, s);
    }
}

void fp_scalarexp(mpz_t ans, mpz_t c, mpz_t d){
    int length = 0;
    length = (int)mpz_sizeinbase(d, 2);
    char binary[length + 1];
    mpz_t s,t;
    mpz_init(s); mpz_init(t);
    mpz_set_ui(s, 1); mpz_set(t, c);

    if(mpz_cmp_ui(d, 0) == 0 || mpz_cmp_ui(c, 0) == 0){
        mpz_set_ui(ans, 1);
    }else{
        mpz_get_str(binary, 2, d);
        for(int k = length-1; k >= 0; k--){
            if(binary[k] == '1'){
                fp_mul(s, s, t);
            }
            fp_mul(t, t, t);
        }
        mpz_set(ans, s);
    }
}

void fp_legendre(mpz_t ans, mpz_t in){
    // legendre //
    mpz_t work; mpz_init(work);
    mpz_set(work, prime_z);
    mpz_sub_ui(work,work,1);
    mpz_div_ui(work,work,2);
    fp_scalarexp(ans, in, work);
}

/*void fp_sqrt(mpz_t ans, mpz_t in){
    fp_legendre(ans, in);
    if(mpz_cmp_ui(ans, 1) == 0){
        mpz_sqrt(ans, in);
    }else{
        gmp_printf("in = %Zd は非平方余剰\n", in);
    }
}*/