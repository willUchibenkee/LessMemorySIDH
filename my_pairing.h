// my_pairing.h From ANSIIRU's github
#pragma once

#ifdef TTT_INSTANCE_HERE

    #define TTT_EXTERN

#else

    #define TTT_EXTERN extern

#endif


#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//#define NULL (void *)0 //ここでエラーが出ているが関係ないと思う
#define TEST
#define WORD (sizeof(unsigned int) * CHAR_BIT)  //CHAR BIT=8なのでword=32,sizeofはメモリのByte数を返す
#define HHALF_MASK UINT_MAX << (WORD / 2)   //UINT_MAX=4294967295を16bit左にシフトf
#define LHALF_MASK UINT_MAX >> (WORD / 2)   // 16bit右にシフト
#define HWORD_BIT ((unsigned int) 1 << (WORD / 2))  //1を１６左にシフト
#define Mprime 656013006  //モンゴメリ乗算の求める法を32bitとしている(Nprimeの下位３２ビット)
#define NOELIPS            //ELIPSを使うか使わないか
#define Nval "ae74fb758612c1f667297971c8a48f9536f0ec3d92996a80e3173e315bb9286cd0db0a821a65f92b0804620cd6e1fa9e15a9677f2719a7a3" //乱数
#define pval "0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" // sidh.specより
#define oneval "ECEEA7BD2EDAE93254545F77410CD801A4FB559FACD4B90FF404FC00000000000000000000000000000000000000000000000000742C" // r&p
#define rsqval "25A89BCDD12A69E16A61C7686D9AABCD92BF2DDE347E175CC6AF8D6C7C0BAB27973F8311688DACEC7367768798C228E55B65DCD69B30" // r**2%p
#define rval "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
#define Nprime "9d29b89047d637322e5e278d70dc36164cd2eacf79a690086b803ab9286cd0db0a821a65f92b0804620cd6e1fa9e15a9677f2719f6ce" // N%p

#define MOD_WORDS 14    //BLS12-381のためこれだけ必要？32*14=448bit
#define MOD_WORDS2 28 
#define FAIL_SET_STR 2
#define FAIL_GET_STR 3
#define FAIL_FP_SUB 4
#define FAIL_FP_ADD 5
#define FAIL_FP_MUL 6
#define FAIL_FP_DIV2 7
#define FAIL_FP_SQR 8

#ifdef NOELIPS
 #define val(p) (p->value)
#endif

#define elem0(p) (&p->element[0])
#define elem1(p) (&p->element[1])
#define elem2(p) (&p->element[2])
#define elem3(p) (&p->element[3])
#define elem4(p) (&p->element[4])
#define xcoord(p) (&p->x)
#define ycoord(p) (&p->y)
#define zcoord(p) (&p->z)
#define ecinfinit(p) (p->infinity)


#ifdef NOELIPS
typedef struct Fp{
    unsigned int value[MOD_WORDS];
}Fp;
#else

#endif

//elem0=a,elem1=b (a+bu)
typedef struct Fp2{
    Fp element[2];
}Fp2;

typedef struct ec2
{
    Fp2 x;
    Fp2 y;
    int inf;
    // 楕円曲線の点 無限遠にいったらinfを１に
}ec2;

Fp po;
Fp oneo;
Fp rsqo;
Fp ro;
Fp No;

Fp *p= &po;
Fp *one= &oneo;
Fp *Rsq = &rsqo;
Fp *r= &ro;
Fp *N= &No;

//Fp1.c
void Fp_set_str(Fp *a, unsigned char* str);
void Fp_get_str(char* str, Fp *a);
void Fp_print(Fp *a);
void Fp_add(Fp *c, Fp *a, Fp *b);
void Fp_sub(Fp *c, Fp *a, Fp *b);
void Fp_mul(Fp *c, Fp *a, Fp *b);
void Fp_div2(Fp *c, Fp *a);
void Fp_neg(Fp *c, Fp *a);
void Fp_set(Fp *c, Fp *a);
void Fp_inv(Fp *c, Fp *a);
int Fp_cmp(Fp *a, Fp *b);
int Fp_cmp_zero(Fp *a);
void Fp_to_Mont(Fp *a , Fp *b);
int Fp_legendre(Fp *a);
void Fp_sqrt(Fp *ANS,Fp *a);
int Fp_pow_c3(Fp *z,Fp *a);

//Fp2.c
void Fp2_set_str(Fp2 *a, char* str);
void Fp2_get_str(char* str, Fp2 *a);
void Fp2_print(Fp2 *a);
void Fp2_add(Fp2 *c, Fp2 *a, Fp2 *b);
void Fp2_add1(Fp2 *c, Fp2 *a);
void Fp2_sub(Fp2 *c, Fp2 *a, Fp2 *b);
void Fp2_mul(Fp2 *c, Fp2 *a, Fp2 *b);
void Fp2_sqr(Fp2 *c, Fp2 *a);
void Fp2_div2(Fp2 *c, Fp2 *a);
void Fp2_neg(Fp2 *c, Fp2 *a);
void Fp2_mul_ix(Fp2 *c, Fp2 *a);
void Fp2_mul_xi(Fp2 *c, Fp2 *a);
void Fp2_mul_fp(Fp2 *c, Fp2 *a, Fp *b);
void Fp2_set(Fp2 *c, Fp2 *a);
void Fp2_frob_p(Fp2 *c, Fp2 *a);
void Fp2_inv(Fp2 *c, Fp2 *a);
void Fp2_inv_pre(Fp2 *a);
void Fp2_inv_post(Fp2 *c, Fp2 *a);
void Fp2_conj(Fp2 *c, Fp2 *a);
void Fp2_to_Mont(Fp2 *c, Fp2 *a);
int Fp2_equal(Fp2 *c,Fp2 *a);
int Fp2_cmp(Fp2 *a,Fp2 *b);
int Fp2_cmp_zero(Fp2* a);
void Fp2_set_fp(Fp2 *c, Fp *a);
void Fp2_mul_line(Fp2* c,Fp2* a);
void _Fp_neg(Fp *c, Fp *a);
void Fp2_mul_acc(Fp2 *c, Fp2 *a, Fp2 *b);

//efp2.c
