#fp.py
import define

class fp_t:
    def __init__(self, x0):
        self.x0 = x0

    def info(self):
        print("_________________________")
        print(f'x0:{self.x0}')

# def print_fp(x: fp_t):
#     print("x0:{x.x0}")

    #mod
    def mod(self):
        if self.x0 >= 0:
            return self.x0 % define.prime_z
        else:
            return self.x0 + define.prime_z

    #add
    def __add__(self, other):
        if type(other) == fp_t: 
            ans = fp_t(0)
            ans.x0 = self.x0 + other.x0
            return ans.mod()
            raise TypeError()

    def neg(self):
        gyaku = fp_t(0)
        gyaku.x0 = -self.x0
        return gyaku.mod()

    #sub
    def __sub__(self, other):
        if type(other) == fp_t: 
            ans = fp_t(0)
            ans = self + other.neg()
            return ans.mod()
            raise TypeError()

    #mul
    def __mul__(self, other):
        if type(other) == fp_t: 
            ans = fp_t(0)
            ans.x0 = self.x0 * other.x0
            return ans.mod()
            raise TypeError()

    #inv     フェルマーの小定理 a**(p-1) = 1 mod p　から　a**(p-2) = 1/a
    def inv(self):
        ans = fp_t(0)
        ans.x0 = self.x0 ** (prime_z - 2)
        return ans.mod()