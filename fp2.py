#fp2.py
import define
import fp
import random

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
        for count in range(define.prime_z**2 - 2):
            ans = ans * self
            #print(ans)
            #ans.mod()
            #input()
        return ans.mod()

    def pow(self, scalar: int):
        #T:tmp S:s
        i,length = 0, 0
        length = bin(scalar)
        binary = str(length)
        tmp = fp2_t(0,0)
        tmp = self
        s = fp2_t(1,0)

        for i in reversed(range(2, len(length))):

            #print(i)
            #print(binary[i])

            if binary[i] == '1':
                s = s * tmp
                #print('S = ST')
            
            #input()
            tmp = tmp * tmp

        return s.mod()

#0なら0, そうでないなら１を返す
    def cmp_one(self):
        if self.x0 == 0:
            if self.x1 == 0:
                return 0
            else:
                return 1
        else:
            return 1

    def legendre(self):
        tmp = fp2_t(0, 0)

        #(p^2 -1)/2 を計算
        expo = define.prime_z**2
        expo = expo - 1
        expo = expo / 2
        print(expo)
        tmp = self.pow(int(expo))

        if tmp.cmp_one() == 0:
            return 1
        else:
            return -1
    
    #sqrt
    def sqrt(self):
        x,y,t,k,n,tmp = fp2_t(0,0), fp2_t(0,0), fp2_t(0,0), fp2_t(0,0), fp2_t(0,0), fp2_t(0,0)
        e,m = 0, 0
        exp,q,z,result = 0, 0, 0, 0

        n.x0 = random.randint(0, define.prime_z-1)
        n.x1 = random.randint(0, define.prime_z-1)

        n.info()

        while n.legendre() != -1 :
            n.x0 = random.randint(0, define.prime_z-1)
            n.x1 = random.randint(0, define.prime_z-1)  #nは乱数
            
        q = define.prime_z**2
        q = q - 1
        result = q**2
        e = 0

        while result == 0:
            q = q / 2
            result = q % 2
            e = e + 1

        y = n**q #ここでバグ
        z = e
        exp = q-1
        exp = exp/2
        x = self.pow(exp)
        tmp = x * x
        k = tmp * self
        x = x * self

        while k.cmp_one()!=0:
            m=1
            exp = 2**m
            tmp = k.pow(exp)

            while tmp.cmp_one()!=0:
                m = m + 1
                exp = 2**m
                tmp = k.pow(exp)

            exp = z - m
            exp = exp - 1
            result = 2**exp.x0
            t = y.pow(result)
            y = t * t
            z = m
            x = x * t
            k = k * y

        ANS = x
        return ANS.mod()