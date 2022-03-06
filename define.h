#pragma once
#ifdef TTT_INSTANCE_HERE
    #define TTT_EXTERN
#else
    #define TTT_EXTERN extern
#endif

#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>

#define ARCBIT 64  //64bit processor
//#define ARCBIT 32 //32bit processor

//#define DEBUG_COST_A
//#define DEBUG_ASSERT
#define CHECK_PAIRING_TIME_LOOP 10000
/**************MP Lib**************/
// #define mcl
#define gmp
/**********************************/
/**************Option**************/
#define X64
/**********************************/

#ifdef  X64
#define FPLIMB_BITS FPLIMB*ARCBIT
#define FPLIMB 7 //
#define FPLIMB2 FPLIMB*2  //??
#endif

#ifdef X32
#define FPLIMB_BITS FPLIMB* ARCBIT
#define FPLIMB 22
#define FPLIMB2 FPLIMB*2  //??
#endif

#define scalar_t mpz_t

#define k6_X_length 128//////37??

#define Pax0 "f8"
#define Pax1 "64"

#define Pay0 "c7"
#define Pay1 "130"

#define Qax0 "18a"
#define Qax1 "1aa"

#define Qay0 "4f"
#define Qay1 "33"

#define Pbx0 "113"
#define Pbx1 "166"

#define Pby0 "68"
#define Pby1 "19a"

#define Qbx0 "b9"
#define Qbx1 "14"

#define Qby0 "ef"
#define Qby1 "119"

// #define Pax0 "48CB469627ED504A5CD26186AB9EE150E961BBB20C50847C5F70951962AF75640E3AE63DE6716C4C7A0F0A92E663030350F0E1C5CF3C00"
// #define Pax1 "50EAE369F84652707DC923D84780D680FE109424C46C81A884D22623B21C9489D1C6FA9D3B3D570EF62045928A6DDAED4078AE1C1CAD01"

// #define Pay0 "00000A00000000000000290000003A00000010000000000000004100000040000000020000000000000000000000000000000000000000"
// #define Pay1 "0000007C000000770000006E0000005D0000003F00000000000000801B1484A57F00003F000000000000000004000000000000B0FFFFFF"

// #define Qax0 "6C0CEB0DBC2ADD7DEF37B2643FE158C0D7F442BD71ABB4C6EDA21AF361F4D964B6C02DD4AFF3F738EB66F688E39CF0FC0E34381746C700"
// #define Qax1 "F5851CD6E2327419477851AE7242AFEA8372E2A140CDC414262BFA57692EA31AD3C2FB8615477EA6B42A68D00D325DD7507F1537DE2500"

// #define Qay0 "000000000000000000000D5DFF83A57F00000100000000000000FB09FF83A57F00000000000000000000FF0F00000000000000C0DC0100"
// #define Qay1 "00000000F0FFFFFFFFFFFF0010000000000000000000000000000001000000000000000000000000000000D0742984A57F0000801B1484"

// #define Pbx ""
// #define Pby ""

// #define Qbx ""
// #define Qby ""

#define ka "B"
#define kb "2"
#define eA "4" //216
#define eB "3" //137
#define la 2
#define lb 3
#define Aval0 "1a7"
#define Aval1 "149"
// #define pya "0x8"
// #define pyb "0x9"
#define Bval0 "1"
#define Bval1 "0"

/*Field*/
typedef struct{
  mp_limb_t x0[FPLIMB];
}fp_t;
typedef struct{
  fp_t x0,x1;
}fp2_t;
// typedef struct{
//   fp2_t x0,x1,x2;
// }fp6_t;

/*dField*/
typedef struct{
  mp_limb_t x0[FPLIMB2];
}fpd_t;
typedef struct{
  fpd_t x0,x1;
}fpd2_t;
typedef struct{
  fpd2_t x0,x1,x2;
}fpd6_t;
//tmp finite field
TTT_EXTERN mp_limb_t buf[FPLIMB];

/*Elliptic Curve*/
typedef struct{
  fp_t x,y;
  int infinity;
}efp_t;
typedef struct{
  fp2_t x,y;
  int infinity;
}efp2_t;
// typedef struct{
//   fp6_t x,y;
//   int infinity;
// }efp6_t;

/*Projectiv Elliptic Curve*/
typedef struct{
  fp_t x,y,z;
  int infinity;
}efp_projective_t;
typedef struct{
  fp2_t x,y,z;
  int infinity;
}efp2_projective_t;
// typedef struct{
//   fp6_t x,y,z;
//   int infinity;
// }efp6_projective_t;

/*Jacobian Elliptic Curve*/
typedef struct{
  fp_t x,y,z;
  int infinity;
}efp_jacobian_t;
typedef struct{
  fp2_t x,y,z;
  int infinity;
}efp2_jacobian_t;
// typedef struct{
//   fp6_t x,y,z;
//   int infinity;
// }efp6_jacobian_t;

TTT_EXTERN gmp_randstate_t state;//for random
TTT_EXTERN int cost_add,cost_add_ui,cost_sub,cost_sub_ui,cost_mul,cost_mul_ui,cost_mul_base,cost_sqr,cost_inv,cost_mod,cost_set_neg;
TTT_EXTERN int cost_add_nonmod, cost_add_nonmod_double, cost_sub_nonmod, cost_sub_nonmod_double, cost_r1shift, cost_mod_nomal;
TTT_EXTERN mpz_t X_z,prime_z,order_z,trace_z;
TTT_EXTERN mp_limb_t X,prime[FPLIMB];
TTT_EXTERN mp_limb_t prime2[FPLIMB2],prime705[FPLIMB2],prime672[FPLIMB2];
TTT_EXTERN fp_t base_c,base_d;//α^7=c, β^2=α となるように逐次拡大で拡大体を構成する
TTT_EXTERN fp_t base_c_inv,base_d_inv,base_d_inv_montgomery;//α^7=c, β^2=α に出てくるcの逆元の計算結果

TTT_EXTERN fp2_t Ea, Eb;
TTT_EXTERN fp_t curve_b;
TTT_EXTERN mpz_t sqrt_power_z;

TTT_EXTERN mpz_t efp_total,efp2_total;//,efp6_total,fp6_total_r;//#efp,#efp5,#efp10,#efp7,#efp14
TTT_EXTERN mpz_t miller_loop_s;
TTT_EXTERN std::vector<int> miller_loop_v, finalexp_pow_x, finalexp_pow_x_1, finalexp_pow_3w,finalexp_pow_w;
TTT_EXTERN mpz_t X_1_div2,X_1,X_2,X_2_1,four;//(kai +1)/2,(kai -1),(kai^2)をあらかじめ求めておく
TTT_EXTERN mpz_t hardpart,hp_3w,three;
//emb6
TTT_EXTERN fp_t frobenius_1_6,frobenius_2_6,frobenius_4_6,frobenius_5_6;//c^((p-1)/10)の計算結果
TTT_EXTERN fp_t frobenius_1_6MR,frobenius_2_6MR,frobenius_4_6MR,frobenius_5_6MR;//c^((p-1)/10)の計算結果


//montgomery
TTT_EXTERN mp_limb_t R[FPLIMB],Ri[FPLIMB],R1[FPLIMB],RR[FPLIMB],Ni[FPLIMB];
TTT_EXTERN int m;
TTT_EXTERN mp_limb_t u[FPLIMB+1];
TTT_EXTERN mp_limb_t N[FPLIMB2],R2[FPLIMB],R3[FPLIMB],RmodP[FPLIMB];
TTT_EXTERN mp_limb_t Ni_neg;  //Ni_neg=-N^(-1)


TTT_EXTERN struct timeval tv_start,tv_end;
TTT_EXTERN float MILLER_ATE_4SPARSE_TIME;
TTT_EXTERN float MILLER_ATE_5SPARSE_TIME;
TTT_EXTERN float MILLER_ATE_6SPARSE_TIME;
TTT_EXTERN float MILLER_ATE_7SPARSE_TIME;
TTT_EXTERN float FINAL_EXP_TIME;

//isogeny
TTT_EXTERN fp2_t A0, B;
TTT_EXTERN fp_t ea, eb;
TTT_EXTERN efp2_t Pa, Qa, Pb, Qb, Sa, Sb, Ra, Rb;

typedef struct {
  int add;
  int add_ui;
  int add_nonmod;
  int add_nonmod_double;
  int sub;
  int sub_ui;
  int sub_nonmod;
  int sub_nonmod_double;
  int mul;
  int set_neg;
  int r1shift;
  int sqr;
  int inv;
  int mod;
  int mod_nomal;
} cost;

#endif
