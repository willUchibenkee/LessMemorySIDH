#define TTT_INSTANCE_HERE
#include "efp2.h"
#include "mcl.h"
#include <cstdio>

#include "define.h"
#include "./time.h"
#include "scalar.h"
#include "mpn.h"
#include "fp.h"

#include "fp2.h"
#include "field_test.h"
#include "test_efp.h"
#include "create.h"
#include "isogeny.h"
#include "test_isogeny.h"

int main(){

  #ifdef mcl
  const char *pStr = "0x0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
  mcl_init(pStr);
  #endif
  gmp_randinit_default(state);
  gmp_randseed_ui(state,(unsigned long int)time(NULL));

  tmp_init();
  create_prt();
  // check_base();
  // pre_montgomery();
  // frobenius_precalculation();
  curve_search();
  create_weil();
  
  printf("*********************************************************************************************\n\n");
  
  //各関数の動作確認、コスト計算、時間計測など
  // test_fp_montgomery(CHECK_PAIRING_TIME_LOOP);
  // test_field(0, CHECK_PAIRING_TIME_LOOP, CHECK_PAIRING_TIME_LOOP, CHECK_PAIRING_TIME_LOOP);
  // test_fp(CHECK_PAIRING_TIME_LOOP);

  // test_fp2(CHECK_PAIRING_TIME_LOOP);
  // test_fp6(CHECK_PAIRING_TIME_LOOP);

  // check_fp_with_montgomery();
  // check_fp2_with_montgomery();
  // check_fp6_with_montgomery();
  check_fp();
  check_fp2();

  // BENCH_fp2_fp6_mul_lazy_montgomery(CHECK_PAIRING_TIME_LOOP);
  // BENCH_miller_jac_lazy_montgomery(CHECK_PAIRING_TIME_LOOP);
  // BENCH_miller_proj_lazy_montgomery(CHECK_PAIRING_TIME_LOOP);
  // BENCH_finalexp_lazy_montgomery(CHECK_PAIRING_TIME_LOOP);
  // BENCH_Pairing_jac_lazy_montgomery(CHECK_PAIRING_TIME_LOOP);
  // BENCH_Pairing_proj_lazy_montgomery(CHECK_PAIRING_TIME_LOOP);
  // BENCH_Pairing_proj_lazy_montgomery_static(CHECK_PAIRING_TIME_LOOP);

  check_efp();
  check_efp2();
  // check_efp6();
  // check_g1_g2();

  //SCM_func_check();//未完成
  // check_pairing_2NAF();
  // check_pairing_2NAF_costello();
  // check_pairing_static();
  // check_pairing_jac_count_2NAF_lazy_montgomery();
  // check_pairing_proj_count_2NAF_lazy_montgomery();
  // check_pairing_count_2NAF();
  // check_pairing_time_2NAF();

  // check_count_finalexp_pow_2NAF();
  printf("*********************************************************************************************\n\n");

  //play ground

  // efp_t P,P1,P2;
  // efp_init(&P);
  // efp_init(&P1);
  // efp_init(&P2);


  // efp_rational_point(&P);
  // efp_println("P = ",&P);
  // efp_checkOnCurve(&P,&Ea.x0,&Eb.x0);
  // printf("---------------------------------\n");
  
  // efp_eca(&P1, &P, &P,&Ea.x0,&Eb.x0);
  // efp_println("P1 = ",&P1);
  // efp_checkOnCurve(&P1,&Ea.x0,&Eb.x0);
  // efp_ecd(&P2, &P,&Ea.x0, &Eb.x0);
  // efp_println("P2 = ",&P2);
  // efp_checkOnCurve(&P2,&Ea.x0,&Eb.x0);

  keygen();

  return 0;
}
