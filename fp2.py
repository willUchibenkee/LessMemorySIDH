#fp2.py
import define
import fp

class fp2_t:
    def __init__(self, x0, x1):
        self.x0 = x0
        self.x1 = x1
    def info(self):
        print("_________________________")
        print(f'x0:{self.x0}')
        print(f'x1:{self.x1}')
# def print_fp(x: fp_t):
#     print("x0:{x.x0}")
    def __repr__(self):
        print(self.x0)
        print(self.x1)
    def __str__(self):
        return str(self.x0) + "_" + str(self.x1)
    #mod
    def mod(self):
        if self.x0 >= 0 and self.x1 >= 0:
            #print("パターン１")
            return fp2_t(self.x0 % define.prime_z, self.x1 % define.prime_z)
        elif self.x0 >= 0 and self.x1 < 0:
            #print("パターン2")
            while self.x1 < 0:
                self.x1 = self.x1 + define.prime_z
            return fp2_t(self.x0 % define.prime_z, self.x1)
        elif self.x0 < 0 and self.x1 >= 0:
            #print("パターン3")
            while self.x0 < 0:
                self.x0 = self.x0 + define.prime_z
            return fp2_t(self.x0, self.x1 % define.prime_z)
        else:
            #print("パターン4")
            while self.x0 < 0:
                self.x0 = self.x0 + define.prime_z
                #print(define.prime_z)
                # print(self.x0)
                # input()
            while self.x1 < 0:
                self.x1 = self.x1 + define.prime_z
                # print(self.x1)
                # input()
            return fp2_t(self.x0, self.x1)
    #add
    def __add__(self, other):
        if type(other) == fp2_t: 
            ans = fp2_t(0, 0)
            ans.x0 = self.x0 + other.x0
            ans.x1 = self.x1 + other.x1
            return ans.mod()
            raise TypeError()
    def neg(self):
        gyaku = fp2_t(0, 0)
        gyaku.x0 = -self.x0
        gyaku.x1 = -self.x1
        return gyaku.mod()
    #sub
    def __sub__(self, other):
        if type(other) == fp2_t: 
            ans = fp2_t(0, 0)
            ans = self + other.neg()
            return ans.mod()
            raise TypeError()
    #mul
    def __mul__(self, other):
        if type(other) == fp2_t: 
            ans = fp2_t(0, 0)
            ans.x0 = self.x0 * other.x0 - self.x1 * other.x1
            ans.x1 = self.x0 * other.x1 + self.x1 * other.x0
            return ans.mod()
            raise TypeError()
    #inv     フェルマーの小定理 a**(p-1) = 1 mod p　から　a**(p-2) = 1/a
    def inv(self):
        ans = fp2_t(1, 0)
        for count in range(define.prime_z - 2):
            ans = ans * self
            print(ans)
            #ans.mod()
            input()
        return ans.mod()