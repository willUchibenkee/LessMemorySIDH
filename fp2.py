#fp2.py
import define

# class fp2_t:
#     def __init__(self, x0, x1):
#         self.x0 = x0
#         self.x1 = x1

#     def info(self):
#         print("_________________________")
#         print(f"x0:{self.x0}\nx1:{self.x1}")

#     def mod(self):
#         if self.x0 >= 0 and self.x1 >= 0:
#             return self.x0 % define.prime_z, self.x1 % define.prime_z
#         elif self.x0 >= 0 and self.x1 < 0:
#             return self.x0 % define.prime_z, self.x1 + define.prime_z
#         elif self.x0 < 0 and self.x1 >= 0:
#             return self.x0 + define.prime_z, self.x1 % define.prime_z
#         else:
#             return self.x0 + define.prime_z, self.x1 + define.prime_z

# #add
#     def __add__(self, other):
#         if type(other) == fp2_t: 
#             ans = fp2_t(0, 0)
#             ans.x0 = self.x0 + other.x0
#             ans.x1 = self.x1 + other.x1
#             return ans.mod()
#             raise TypeError()

#     def neg(self):
#         gyaku = fp2_t(0, 0)
#         gyaku.x0 = -self.x0
#         gyaku.x1 = -self.x1
#         return gyaku.mod()

# #sub
#     def __sub__(self, other):
#         if type(other) == fp2_t: 
#             ans = fp2_t(0, 0)
#             ans = self + other.neg()
#             return ans.mod()
#             raise TypeError()

# #mul
#     def __mul__(self, other):
#         if type(other) == fp2_t: 
#             ans = fp2_t(0, 0)
#             ans.x0 = self.x0 * other.x0 - self.x1 * other.x1
#             ans.x0 = self.x0 * other.x1 + self.x1 * other.x0
#             return ans.mod()
#             raise TypeError()

# #inv     フェルマーの小定理 a**(p-1) = 1 mod p　から　a**(p-2) = 1/a
#     def inv(self):
#         ans = fp2_t(0, 0)
#         ans.x0 = self.x0 ** (prime_z - 2)
#         return ans.mod()

def fp2_print(a, bi):
    print(f'{a} + {bi}i')

def fp2_add(a, bi, c, di):
    ans = (a + c) % define.prime_z
    ansi = (bi + di) % define.prime_z
    return ans, ansi

def fp2_neg(a, bi):
    ans = -a
    ansi = -bi
    ans = ans + define.prime_z
    ansi = ansi + define.prime_z
    return ans, ansi

def fp2_sub(a, bi, c, di):
    neg, negi = fp2_neg(c, di)
    ans, ansi = fp2_add(a, bi, neg, negi)
    return ans, ansi

def fp2_mul(a, bi, c, di):
    ans = a * c - bi * di
    if ans < 0:
        while ans < 0:
            ans = ans + define.prime_z
    else:
        #print('%')
        ans = ans % define.prime_z

    ansi = (a * di + bi * c) % define.prime_z
    #input()
    return ans, ansi

def fp2_inv(a, bi):
    ans = 1
    ansi = 0
    for count in range(define.prime_z - 2):
        ans, ansi = fp2_mul(ans, ansi, a, bi)
        print(f'count = {count}')
        fp2_print(ans, ansi)
        #input()
    return ans, ansi
