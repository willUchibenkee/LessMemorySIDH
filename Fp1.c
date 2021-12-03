// Fp1.c From ANSIIRU's github

#include "my_pairing.h"
#include <time.h> 
#include <stdio.h>

//extern union T *pt;


#define rval "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"

unsigned int hextoui(char * str, int len){
    unsigned int i, val = 0;
    char c;

    for(i = 0; i < len; i++){
        c = *(str - i - 1);
        if(c < 0x40){
            val += (c - 0x30) << (4 * i);
        }else{
            val += ((c & 0x0f) + 9) << (4 * i);
        }
    }
    return val;
}

#ifdef NOELIPS
//Fpの元を1つ作成する。
void Fp_set_str(Fp *a, unsigned char* str){
    unsigned int i;
    // unsigned int c[3];
    unsigned int len = strlen(str); //ここでは９６くらい
    printf("len :%d\n",WORD );
    // if (len > WORD * MOD_WORDS / 4 + 2) exit(1); //  384bitより長かったらエラー

    for(i = 0; i < MOD_WORDS; i++) a->value[i] = 0;
    
    printf("len :%d\n",len / 8);
    //文字数字を配列に代入
    for(i = 0; i < len / 8; i++){
        a->value[i] = hextoui((str + len - (i * 8)), 8);
    }

    if (len & 0x07){
        a->value[i] = hextoui((str + len - (i * 8)), len & 0x7);
    }
}
#else

#endif

void Fp_set_R(void){
    Fp_set_str(r, rval);
}

void Fp_set_N(void){
    Fp_set_str(N, Nval);
}

void Fp_set_p(void){
    Fp_set_str(p, pval);
}

void Fp_set_one(void){
    Fp_set_str(one, oneval);
}

void Fp_set_Rsq(void){
    Fp_set_str(Rsq, rsqval);
}

#ifdef NOELIPS
void Fp_get_str(char* str, Fp *a){
    char buf[WORD / 4 + 1];
    int i, j;
    str[MOD_WORDS * WORD / 4] = '\0';

    for(i = 0; i < MOD_WORDS; i++){
        snprintf(buf, WORD / 4 + 1, "%08x", a->value[i]);   //問題なし
        memcpy(str + (WORD / 4) * (MOD_WORDS - i - 1), buf, WORD / 4);
    }

    for(i = 0; i <= MOD_WORDS * WORD / 4; i++){
        if(str[i] != '0') break;
    }

    for(j = 0; i <= MOD_WORDS * WORD / 4; i++, j++){
        str[j] = str[i];
    }

    if(str[0] == '\0') {
        str[0] = '0';
        str[1] = '\0';
        }
}
#endif


#ifdef NOELIPS
//素体上での加算（bit長が長い多倍長可算になる）FPは多倍長の数の入った配列cが出力用
void Fp_add(Fp *c, Fp *a, Fp *b){
    unsigned int carry = 0;
    unsigned int r = 0;

    for(int i = 0; i < MOD_WORDS; i++){
        r = val(a)[i] + carry;  //#define val(p) (p->value)
        carry = (r < carry); //r<carryの時１を返す（桁上がりの時の１）
        r += val(b)[i];
        carry += (r < val(b)[i]); //けた溢れを起こしてｒがｂより小さくなっているということ。
        val(c)[i] = r;
    }

//素体の標数より大きくなったり桁溢れを起こした場合（mod p(F pの位数））を行う
    if(carry || Fp_cmp(c, p) >= 0) Fp_sub(c, c, p);     //ｃがp（有限体の位数）より大きくなった時modをとる。
}

//素体上での減算c=a-b
void Fp_sub(Fp *c, Fp *a, Fp *b){
    unsigned int carry = 0;
    unsigned int r = 0;

    if(Fp_cmp(a, b) >= 0){
        for(int i = 0; i < MOD_WORDS; i++){
            r = val(b)[i] + carry; //ｒは引く数これに１を足すことで桁上がりを表現
            carry = (r < carry); //???????
            carry += (val(a)[i] < r);  //ai-biにおいてbiがaiより大きいと桁溢れが起きる。
            val(c)[i] = val(a)[i] - r;
        }
    }else{
        Fp_sub(c, b, a);      //逆を行う（引き算がマイナスになってしまう）
        Fp_sub(c, p, c);    //位数からｃを引くことでmodを求める。
    }
}
#else 

#endif

#ifdef NOELIPS
//32bit*32bitの掛け算を行うプログラム？
void dword_mul(unsigned int *w1, unsigned int *w0, unsigned int u, unsigned int v){
    unsigned int  __x0, __x1, __x2, __x3, __ul, __vl, __uh, __vh;
    unsigned int __u = (u), __v = (v);
        
    __ul = __u & LHALF_MASK;   // andをとる下位１６桁を取り出している。
    __uh = __u >> (WORD / 2);   //３２桁中上位１６桁を取り出す。（桁溢れ予防のため）
    __vl = __v & LHALF_MASK;
    __vh = __v >> (WORD / 2);   //16bitで分割して掛け算を行う。
    __x0 = (unsigned int) __ul * __vl;
    __x1 = (unsigned int) __ul * __vh;
    __x2 = (unsigned int) __uh * __vl;
    __x3 = (unsigned int) __uh * __vh;

    __x1 += __x0 >> (WORD / 2);/* this can't give carry */
    __x1 += __x2;		/* but this indeed can */
    if (__x1 < __x2)		/* did we get it?（桁溢れが起こった場合 */
        __x3 += HWORD_BIT;	/* yes, add it in the proper pos. */

    *(w1) = __x3 + (__x1 >> (WORD / 2));    //x3とx１の上位１６桁
    *(w0) = (__x1 << (WORD / 2)) + (__x0 & LHALF_MASK); //x1の下位１６桁とx0の回１６桁
    /*つまり、32bit*32bitを行い最終的にw１に上位３２ビットをw２に下位３２ビットを格納している。*/
}

void mul_1(unsigned int *rp, unsigned int *up, unsigned int vl){
    unsigned int ul, cl, hpl, lpl;

    cl = 0;
    for(int i = MOD_WORDS - 1; i >= 0; i--){
        ul = *up++; //upの次のアドレスへ移動
        dword_mul(&hpl, &lpl, ul, vl);
        
        lpl += cl;
        cl = (lpl < cl) + hpl;
        
        *rp++ = lpl;
    }

    *rp = cl;
}
//ここでa,bはモンゴメリドメインに乗っている必要あり。求めるのはa*b*R^-1
//R=2**448 mod p
void MR(Fp *c, Fp *a, Fp *b){
    unsigned int q = 0, S = 0;
    unsigned int reg1[MOD_WORDS + 1];
    unsigned int reg2[MOD_WORDS + 1];
    unsigned int reg3[MOD_WORDS];
    unsigned int carry = 0;
    unsigned int r = 0;
     
    for(int i = 0; i < MOD_WORDS; i++) reg3[i] = 0;
    
    for(int i = 0; i < MOD_WORDS; i++){
        dword_mul(&reg1[1], &reg1[0], val(a)[i], val(b)[0]);

        q = (unsigned int)((S + reg1[0]) * Mprime);
        mul_1(reg1, val(b), val(a)[i]);
        mul_1(reg2, val(p), q); 

        for(int j = 0; j < MOD_WORDS + 1; j++){
            r = reg1[j] + carry;
            carry = (r < carry);
            r += reg2[j];
            carry += (r < reg2[j]);
            reg1[j] = r;
        }
        //if(carry || Fp_cmp(c, p) >= 0) Fp_sub(c, c, p);
        carry = 0;
        r = 0;
        for(int j = 0; j < MOD_WORDS; j++){
            r = reg1[j] + carry;
            carry = (r < carry);   
            r += reg3[j];
            carry += (r < reg3[j]);
            if(j != 0) reg3[j - 1] = r;
        }
        
        reg3[MOD_WORDS - 1] = reg1[MOD_WORDS] + carry;
        if(carry || Fp_cmp(c, p) >= 0) Fp_sub(c, c, p);
        S = reg3[0];
    }

    for(int i = 0; i < MOD_WORDS; i++) {
        val(c)[i] = reg3[i];
    }
    if(carry || Fp_cmp(c, p) >= 0) {
        Fp_sub(c, c, p);
    }
}

//多倍長(multiple precision)計算演算掛け算？モンゴメリ乗算を行う結果はa*b*r（modp)とモンゴメリの結果が帰ってくる
void Fp_mul(Fp *c, Fp *a, Fp *b){
    //Fp aa, bb;

    MR(c, a, b);
    
//     MR(&c, a, R2);
    // MR(&bb, b, R2);
    // MR(c, &aa, &bb);
//     MR(c, c, R2);  //モンゴメリリダクションをもう一度行い元に戻す。r^2をかける
}
#else

#endif

#ifdef NOELIPS
//多倍長の除算(a/2）を求める演算を行う　（x/yの時、ｘ＊（yの逆元）となる）
void Fp_div2(Fp *c, Fp *a){
    unsigned int carry = 0;
    unsigned int r = 0;

    if(val(a)[0] & 0x01){
        for(int i = 0; i < MOD_WORDS; i++){
            r = val(a)[i] + carry;
            carry = (r < carry);
            r += val(p)[i];
            carry += (r < val(p)[i]);
            val(c)[i] = r;
        }
        for(int i = 0; i < MOD_WORDS - 1; i++){
            val(c)[i] = (val(c)[i] >> 1) | ((val(c)[i + 1] & 0x01) << (WORD - 1));
        }
        val(c)[MOD_WORDS - 1] = (val(c)[MOD_WORDS - 1] >> 1) | (carry << (WORD - 1));
    }else{//２で割り切れる場合は右にシフト
        for(int i = 0; i < MOD_WORDS - 1; i++){
            val(c)[i] = (val(a)[i] >> 1) | ((val(a)[i + 1] & 0x01) << (WORD - 1));
        }
        val(c)[MOD_WORDS - 1] = (val(a)[MOD_WORDS - 1] >> 1);
    }
}

int Fp_cmp(Fp *a, Fp *b){

    for(int i = MOD_WORDS - 1; i >= 0; i--){
        if(val(a)[i] > val(b)[i]) return 1;
        else if(val(a)[i] < val(b)[i]) return -1; 
    }
    return 0;
}

int Fp_cmp_zero(Fp *a){
    Fp b;
    Fp_set_str(&b,"0");
    if(Fp_cmp(a,&b)==0){
        return 1;
   }else{
        return 0;
    }
}

int Fp_cmp_one_mont(Fp *a){
    Fp b;
    Fp_set_str(&b,"15f65ec3fa80e4935c071a97a256ec6d77ce5853705257455f48985753c758baebf4000bc40c0002760900000002fffd");
    if(Fp_cmp(a,&b)==0){
        return 1;
   }else{
        return 0;
    }
}

int Fp_cmp_one(Fp *a){
    Fp b;
    Fp_set_str(&b,"1");
    if(Fp_cmp(a,&b)==0){
        return 1;
   }else{
        return 0;
    }
}

#else

#endif

#ifdef NOELIPS
//Fｐをプリントする
void Fp_print(Fp *a){
    char buf[97];   //一応９７文字分用意する。
    Fp_get_str(buf, a);
    printf("%s\n", buf);
}
#else

#endif


//-aを求める
void Fp_neg(Fp *c, Fp *a){
    Fp_sub(c, p, a);
}


#ifdef NOELIPS
//cにaをコピー
void Fp_set(Fp *c, Fp *a){
    memcpy(val(c), val(a), MOD_WORDS * WORD / 8);
}
#else


#endif

#ifdef NOELIPS
//逆元を求める演算を行う( フェルマーの小定理）(累乗を軽くするアルゴリズム））
void Fp_inv(Fp *c, Fp *a){
// 位数ｐから２を引いた数
    char *pMinus2 = "110100000000100010001111010100011100101111111111001101001101001001011000110111010011110110110010000110100101110101100110101110110010001110111010010111000010011110011100001010001001010111111011001110011000011010010101000001111011010110000111101100010010000011110101010111111111111111110101100010101001111111111111111111011100111111110111111111111111111111111111111111010101010101001";
    Fp t;
    
    Fp_set(&t, a);
    //Left-to-right binary
    for(int i = 1; i < 381; i++){
        Fp_mul(&t, &t, &t);
        if(*(pMinus2 + i) == '1') {
            Fp_mul(&t, &t, a);
//             printf("入ったよ！！%d\n",i);
        }
    }
    Fp_set(c, &t);
}
#else

#endif

//モンゴメリドメイン上へ
void Fp_to_Mont(Fp *a , Fp *b){
    Fp_mul(a,b,Rsq);
}

// //モンゴメリドメイン上から普通の値へ
void Fp_from_Mont(Fp *a ){
    Fp first;
    Fp_set_str(&first, "1");
    Fp_mul(a,a,&first);
}


int Fp_legendre(Fp *a){
	char *legendre_num="11010000000010001000111101010001110010111111111100110100110100100101100011011101001111011011001000011010010111010110011010111011001000111011101001011100001001111001110000101000100101011111101100111001100001101001010100000111101101011000011110110001001000001111010101011111111111111111010110001010100111111111111111111101110011111111011111111111111111111111111111111101010101010101";
	Fp t;
    Fp_set(&t,a);
    // Fp_print(&t);
    //Left-to-right binary
    for(int i = 1; i < 380; i++){
        Fp_mul(&t, &t, &t);
        if(*(legendre_num + i) == '1') {
            Fp_mul(&t, &t, a);
            // printf("はいったよ");
        }
    }
    // Fp_from_Mont(&t);
    // Fp_print(&t);
    if(Fp_cmp_one_mont(&t)==1){
      return 1;
    }else{
      return -1;
    }
}


/*
Constants:
1. c1, the largest integer such that 2^c1 divides q - 1.
2. c2 = (q - 1) / (2^c1)        # Integer arithmetic
3. c3 = (c2 - 1) / 2            # Integer arithmetic
4. c4, a non-square value in F
5. c5 = c4^c2 in F
*/

void Fp_sqrt(Fp *ANS,Fp *a){
  Fp c1,c2,c3,c4,c5;
  Fp z,t,c,b;

  Fp_set_str(&c4,"161f998c5b49581b0849183769bd9b3dfad48bf9246cec972babb6cfe688d67b0893a1b4df74c0c185cc870e65ffbab2");
  Fp_set_str(&c1,"1");
  Fp_set_str(&c2,"d0088f51cbff34d258dd3db21a5d66bb23ba5c279c2895fb39869507b587b120f55ffff58a9ffffdcff7fffffffd555");
  Fp_set_str(&c3,"680447a8e5ff9a692c6e9ed90d2eb35d91dd2e13ce144afd9cc34a83dac3d8907aaffffac54ffffee7fbfffffffeaaa");
  Fp_set_str(&c5,"ef145240bdb3a8cc6f71b9a8e6cdf38670d0588614e9c73d15af739036c8ae69a622f2441999f9ef718bc78ccffcd52");

  Fp_pow_c3(&z,a);
  // Fp_mul(&t,&z,a);
  // Fp_mul(&t,&z,&t);
  Fp_mul(&z,&z,a);
  Fp_set(ANS,&z);
}

int Fp_pow_c3(Fp *z,Fp *a){
	char *c3="1101000000001000100011110101000111001011111111110011010011010010010110001101110100111101101100100001101001011101011001101011101100100011101110100101110000100111100111000010100010010101111110110011100110000110100101010000011110110101100001111011000100100000111101010101111111111111111101011000101010011111111111111111110111001111111101111111111111111111111111111111110101010101010";
	Fp t;
    Fp_set(&t,a);
    // Fp_print(&t);
    //Left-to-right binary
    for(int i = 1; i < 379; i++){
        Fp_mul(&t, &t, &t);
        if(*(c3 + i) == '1') {
            Fp_mul(&t, &t, a);
            // printf("はいったよ");
        }
    }
   Fp_set(z,&t);
}