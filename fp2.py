#fp2.py
import fp

import configparser

config = configparser.ConfigParser()

config.read("define.ini")

prime_z = config["BASE"]["p"]
p2min = config["BASE2"]["p2minus"]

def fp2_mod(A):
    if A[0] >= 0:
        ANS0 = A[0] % int(prime_z)
    else:
        ANS0 = A[0]
        while ANS0 < 0:
            ANS0 = ANS0 + int(prime_z)
    if A[1] >= 0:
        ANS1 = A[1] % int(prime_z)
    else:
        ANS1 = A[1]
        while ANS1 < 0:
            ANS1 = ANS1 + int(prime_z)
    
    ANS = [ANS0, ANS1]
    
    return ANS

def fp2_add(A, B):
    ANS = [A[0]+B[0], A[1]+B[1]]
    return fp2_mod(ANS)

def fp2_neg(A):
    ANS = [-A[0], -A[1]]
    return fp2_mod(ANS)

def fp2_sub(A, B):
    return fp2_add(A, fp2_neg(B))

def fp2_mul(A, B):
    ANS = [A[0]*B[0]- A[1]*B[1], A[0]*B[1]+A[1]*B[0]]
    return fp2_mod(ANS)

def fp2_inv(A):
    if A == 0:
        return 0
    else:
        ANS = [1, 0]
        for count in range(int(p2min)):
            ANS = fp2_mul(ANS,A)
        return fp2_mod(ANS)