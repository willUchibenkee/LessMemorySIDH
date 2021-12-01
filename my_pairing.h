// my_pairing.h From ANSIIRU's github

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//#define NULL (void *)0 //ここでエラーが出ているが関係ないと思う
#define TEST
#define WORD (sizeof(unsigned int) * CHAR_BIT)  //CHAR BIT=8なのでword=32,sizeofはメモリのByte数を返す
#define HHALF_MASK UINT_MAX << (WORD / 2)   //UINT_MAX=4294967295を16bit左にシフトf
#define LHALF_MASK UINT_MAX >> (WORD / 2)   // 16bit右にシフト
#define HWORD_BIT ((unsigned int) 1 << (WORD / 2))  //1を１６左にシフト
#define Mprime 0xFFFCFFFD  //モンゴメリ乗算の求める法を32bitとしている(Nprimeの下位３２ビット）254bitの場合nprime=0x365373ccba60808c92022379c45b843c6e371ba81104f6c808435e50d79435e5
#define NOELIPS            //ELIPSを使うか使わないか


#define MOD_WORDS 14    //BLS12-381のためこれだけ必要？32*14=448bit
#define MOD_WORDS2 24 
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

//３次元へと射影しているプロジェクティブ座標系
typedef struct EC_Fp{
    Fp x;
    Fp y;
    Fp z;
    int infinity;
}EC_Fp;

typedef struct EC_Fp2{
    Fp2 x;
    Fp2 y;
    Fp2 z;
    int infinity;
}EC_Fp2;

//アフィン座標系

typedef struct EC_Fp_A{
    Fp x;
    Fp y;
    int infinity;
}EC_Fp_A;

typedef struct EC_Fp2_A{
    Fp2 x;
    Fp2 y;
    int infinity;
}EC_Fp2_A;


//extern union T *pt;
extern Fp *p;
extern Fp *one;
extern Fp *Rsq;

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


void EC_Fp_set_str(EC_Fp *P, char* str);
void EC_Fp_get_str(char* str, EC_Fp *P);
void EC_Fp_print(EC_Fp *T);
void EC_Fp_A_print(EC_Fp_A *T);
void EC_Fp2_print(EC_Fp2 *T);
void EC_Fp2_point_set(EC_Fp2 *Q, EC_Fp2 *P);
void EC_Fp2_set_str(EC_Fp2 *P, char* str);
void EC_Fp2_get_str(char* str, EC_Fp2 *P);
void EC_Fp_set(EC_Fp *P, EC_Fp *Q);
void EC_Fp2_set(EC_Fp2 *P, EC_Fp2 *Q);
void EC_Fp2_affine_set(EC_Fp2 *P, EC_Fp2 *Q);
void EC_Fp2_neg(EC_Fp2 *P);

void EC_Fp2_twist_frob_p(EC_Fp2 *Q, EC_Fp2 *P);
void EC_Fp2_to_Mont(EC_Fp2 *Q, EC_Fp2 *P);
void EC_Fp_to_Mont(EC_Fp *Q, EC_Fp *P);
void EC_Fp_gen_BN254_Y(EC_Fp *Q, EC_Fp *P);
int EC_Fp_check_on_curve(EC_Fp *T);
void EC_Fp2_check_on_curve(EC_Fp2 *T);
void EC_Fp_A_set(EC_Fp_A *P, EC_Fp_A *Q);
void EC_Fp2_A_set(EC_Fp2_A *P, EC_Fp2_A *Q);
void EC_Fp2_A_print(EC_Fp2_A *T);
void EC_Fp_A_print(EC_Fp_A *T);
void EC_Fp2_A_to_Mont(EC_Fp2_A *Q, EC_Fp2_A *P);
void EC_Fp_A_to_Mont(EC_Fp_A *Q, EC_Fp_A *P);
void EC_Fp_A_set_str(EC_Fp_A *P, char* str);
void EC_Fp2_A_set_str(EC_Fp2_A *P, char* str);

void EC_Fp2_A_point_set(EC_Fp2_A *Q, EC_Fp2_A *P);
void EC_Fp_gen_random_BLS381_Mont(EC_Fp *P);
void rand_value(char *str, int len);

void EC_Fp_make_affine(EC_Fp *T);
void EC_Fp2_make_affine(EC_Fp2 *T);
void EC_Fp_addition_only_proj(EC_Fp *R, EC_Fp *T,EC_Fp *Q);
void EC_Fp_doubling_only_proj(EC_Fp *T2, EC_Fp *T);
void G1_SCM(EC_Fp* ans, char *s, EC_Fp* P);
void G2_SCM(EC_Fp2* ans, char *s, EC_Fp2* P);
void check_A_onE(Fp2 *x,Fp2*y);
void SCM_Fp_check_proj(EC_Fp* P);
void EC_Fp_P_to_A(EC_Fp_A* A, EC_Fp* B);
void EC_Fp2_P_to_A(EC_Fp2_A* A ,EC_Fp2 *B);


void Map_to_Point(EC_Fp *c,char *a);