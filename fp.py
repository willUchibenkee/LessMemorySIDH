#fp.py
import configparser
import random

config = configparser.ConfigParser()

config.read("define.ini")

prime_z = config["BASE"]["p"]
prime_min = config["BASE"]["pminus"]

def fp_mod(A):
    if A >= 0:
        return A % int(prime_z)
    else:
        ANS = A
        while ANS < 0:
            ANS = ANS + int(prime_z)
        return ANS

def fp_add(A, B):
    return fp_mod(A + B)

def fp_neg(A):
    return fp_mod(-A)

def fp_sub(A, B):
    return fp_add(A, fp_neg(B))

def fp_mul(A, B):
    return(fp_mod(A*B))

def fp_pow(A, k):
    if A == 0 :
        return 1
    else:
        ANS = 1
        for count in range(k):
            ANS = fp_mul(ANS,A)
        return fp_mod(ANS)

def fp_inv(A):
    if A == 0:
        return 0
    else:
        ANS = 1
        prime_int = int(prime_z)
        for count in range(prime_int-2):
            ANS = fp_mul(ANS,A)
        return fp_mod(ANS)
    
def  fp_legendre(A):
    #ルジャンドル記号はA**(p-1/2)

    pmin = int(prime_min)
    syo = pmin/2
    legendre = fp_pow(A, syo)

    return legendre

def fp_sqrt(A):
    fp_t x, y, t, k, n, tmp

    unsigned long int e, m

    n = random.randint(0, int(prime_min))

    while fp_legendre(n) != -1:
            n = random.randint(0, int(prime_min))

    result = int(prime_min) % 2
    e = 0
    q = int(prime_min)
    while result == 0:
        q = q / 2
        result = q % 2
        e =+ 1

    y = fp_pow(n, q)
    z = e
    exp = q - 1
    exp = exp / 2
    x = fp_pow(A, exp)
    tmp = fp_mul(x, x)
    k = fp_mul(tmp, A)
    fp_mul(&x, &x, A);
    while (mpn_cmp_ui(k.x0, FPLIMB, 1) != 0) {
    m = 1;
    mpz_ui_pow_ui(exp, 2, m);
    fp_pow(&tmp, &k, exp);
    while (mpn_cmp_ui(tmp.x0, FPLIMB, 1) != 0) {
        m++;
        mpz_ui_pow_ui(exp, 2, m);
        fp_pow(&tmp, &k, exp);
    }
    mpz_sub_ui(exp, z, m);
    mpz_sub_ui(exp, exp, 1);
    mpz_ui_pow_ui(result, 2, mpz_get_ui(exp));
    fp_pow(&t, &y, result);
    fp_mul(&y, &t, &t);
    mpz_set_ui(z, m);
    fp_mul(&x, &x, &t);
    fp_mul(&k, &k, &y);
    }
    fp_set(ANS, &x);
