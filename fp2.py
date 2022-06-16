#fp2.py
import define
#add
def add(xx0, xx1, yx0, yx1):
    wa0 = xx0 + yx0
    wa1 = xx1 + yx1
    return wa0 % define.prime_z, wa1 % define.prime_z

def neg(xx0, xx1):
    gyakux0 = -xx0
    gyakux1 = -xx1
    return gyaku % define.prime_z

#sub
def sub(x, y):
    sa = x + neg(y)
    return sa % define.prime_z

#mul
def mul(x, y):
    seki = x * y
    return seki % define.prime_z

#inv     フェルマーの小定理 a**(p-1) = 1 mod p　から　a**(p-2) = 1/a
def inv(x):
    gyakusu = x ** (define.prime_z - 2)
    return gyakusu % define.prime_z