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
        for count in range(define.prime_z**2 - 2):
            ans = ans * self
            #print(ans)
            #ans.mod()
            #input()
        return ans.mod()

    def pow(self, scalar: int):
  int i,length;
  length=(int)mpz_sizeinbase(scalar,2);
  char binary[length+1];
  mpz_get_str(binary,2,scalar);
  fp2_t tmp;
  fp2_init(&tmp);
  fp2_set(&tmp,A);

  for(i=1;i<length; i++){
    fp2_sqr(&tmp,&tmp);
    if(binary[i]=='1')  fp2_mul(&tmp,A,&tmp);
  }
  fp2_set(ANS,&tmp);
    
    #sqrt
    def fp2_sqrt(self):
        x,y,t,k,n,tmp = fp2.fp2_t(0,0), fp2.fp2_t(0,0), fp2.fp2_t(0,0), fp2.fp2_t(0,0), fp2.fp2_t(0,0), fp2.fp2_t(0,0)
    e,m = 0, 0
    exp,q,z,result = 0, 0, 0, 0

    fp2_set_random(&n,state)
    while fp2_legendre(&n) != -1 :
        n = state  #nは乱数
    q = prime_z**2
    q = q - 1
    result = q**2
    e = 0
    while result == 0:
        q = q / 2
        result = q % 2
        e = e + 1
    y = n**q
    z = e
    exp = q-1
    exp = exp/2
    fp2_pow(&x,A,exp);
    fp2_mul(&tmp,&x,&x);
    fp2_mul(&k,&tmp,A);
    fp2_mul(&x,&x,A);
    while(fp2_cmp_one(&k)!=0){
        m=1;
        mpz_ui_pow_ui(exp,2,m);
        fp2_pow(&tmp,&k,exp);
        while(fp2_cmp_one(&tmp)!=0){
        m++;
        mpz_ui_pow_ui(exp,2,m);
        fp2_pow(&tmp,&k,exp);
        }
        mpz_sub_ui(exp,z,m);
        mpz_sub_ui(exp,exp,1);
        mpz_ui_pow_ui(result,2,mpz_get_ui(exp));
        fp2_pow(&t,&y,result);
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