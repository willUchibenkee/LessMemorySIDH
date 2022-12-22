#include "create.h"
#include "define.h"
#include "fp.h"
#include "fp2.h"
#include "mpn.h"
#include <gmp.h>

void create_prt(){
  //c=22,HW=6 ハミングウェイトが６
  //mpz_set_str(X_z,"efffffffffffffe00000000000000000",16);
  mpz_set_str(prime_z,"0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",16);
  mpz_set_str(ap,"1000000000000000000000000000000000000000000000000000000",16);
  mpz_set_str(bp,"2341f271773446cfc5fd681c520567bc65c783158aea3fdc1767ae3",16);
  if(!mpz_probab_prime_p(prime_z,30))printf("Inputed p*(prime_z) is not a prime");

  //mpz_set_str(order_z,"e0ffffffffffffc400000000000003ff10000000000000200000000000000001",16);
  mpz_set_str(trace_z,"0",10);
  const unsigned char* xai = reinterpret_cast<const unsigned char *>("efffffffffffffe00000000000000000");
  mpn_set_str(&X,xai,sizeof(char)*34,16); //ui(&X,1,319014718988379808906617884108577046528);
  mpn_set_mpz(prime,prime_z);
  mpn_mul_n(prime2,prime,prime,FPLIMB);
  mpn_copyd(&prime672[10],prime,FPLIMB);
  mpn_lshift(prime672,prime672,FPLIMB2,31);
  gmp_printf("%Nx\n Size %d\n\n",prime672,FPLIMB2,mpn_sizeinbase(prime672,FPLIMB2,2));
  mpn_copyd(&prime705[11],prime,FPLIMB);
  mpn_lshift(prime705,prime705,FPLIMB2,1);
  gmp_printf("%Nx\n Size %d\n\n",prime705,FPLIMB2,mpn_sizeinbase(prime705,FPLIMB2,2));

  //gmp_printf("X     (%4dbit length) = %Zd\n",(int)mpz_sizeinbase(X_z,2),X_z);
  gmp_printf("prime (%4dbit length) = %Zd\n",(int)mpz_sizeinbase(prime_z,2),prime_z);
  //gmp_printf("order (%4dbit length) = %Zd\n",(int)mpz_sizeinbase(order_z,2),order_z);
  gmp_printf("trace (%4dbit length) = %Zd\n",(int)mpz_sizeinbase(trace_z,2),trace_z);
  //printf("X     (HW :%2ld)(binary) = ",mpz_popcount(X_z));
  //mpz_out_str(stdout,2,X_z);printf("\n");
  printf("trace (HW :%2ld)(binary) = ",mpz_popcount(trace_z));
  mpz_out_str(stdout,2,trace_z);printf("\n");
  fp_set_ui(&base_c,1);
  fp_set_neg(&base_c, &base_c);
  fp_inv(&base_c_inv,&base_c);
  fp_set_ui(&base_d,4);
  fp_set_neg(&base_d, &base_d);
  fp_inv(&base_d_inv,&base_d);

  //isogeny
  // ka, kb
  mpz_set_str(ka_z,"0003537A4C",16);
  mpn_set_mpz(ka, ka_z);
  mpz_set_str(kb_z,"000FFF6A4B",16);
  mpn_set_mpz(kb, kb_z);

  // p = 2^ea*3^eb - 1 eaとeb
  mpz_set_str(ea_z,"000000D8",16);
  mpn_set_mpz(ea, ea_z);
  mpz_set_str(eb_z,"00000089",16);
  mpn_set_mpz(eb, eb_z);

  //point set
  mpz_set_str(Pax0_z,"00003CCFC5E1F050030363E6920A0F7A4C6C71E63DE63A0E6475AF621995705F7C84500CB2BB61E950E19EAB8661D25C4A50ED279646CB48",16);
  mpn_set_mpz(Pax0, Pax0_z);
  mpz_set_str(Pax1_z,"0001AD1C1CAE7840EDDA6D8A924520F60E573D3B9DFAC6D189941CB22326D284A8816CC4249410FE80D68047D823C97D705246F869E3EA50",16);
  mpn_set_mpz(Pax1, Pax1_z);

  mpz_set_str(Qax0_z,"0000C7461738340EFCF09CE388F666EB38F7F3AFD42DC0B664D9F461F31AA2EDC6B4AB71BD42F4D7C058E13F64B237EF7DDD2ABC0DEB0C6C",16);
  mpn_set_mpz(Qax0, Qax0_z);
  mpz_set_str(Qax1_z,"000025DE37157F50D75D320DD0682AB4A67E471586FBC2D31AA32E6957FA2B2614C4CD40A1E27283EAAF4272AE517847197432E2D61C85F5",16);
  mpn_set_mpz(Qax1, Qax1_z);

  mpz_set_str(Pbx0_z,"00008664865EA7D816F03B31E223C26D406A2C6CD0C3D667466056AAE85895EC37368BFC009DFAFCB3D97E639F65E9E45F46573B0637B7A9",16);
  mpn_set_mpz(Pbx0, Pbx0_z);
  mpz_set_str(Pbx1_z,"00000000",16);
  mpn_set_mpz(Pbx1, Pbx1_z);
  
  mpz_set_str(Qbx0_z,"00012E84D7652558E694BF84C1FBDAAF99B83B4266C32EC65B10457BCAF94C63EB063681E8B1E7398C0B241C19B9665FDB9E1406DA3D3846",16);
  mpn_set_mpz(Qbx0, Qbx0_z);
  mpz_set_str(Qbx1_z,"00000000",16);
  mpn_set_mpz(Qbx1, Qbx1_z);

  mpz_set_str(Pay0_z,"0001AB066B84949582E3F66688452B9255E72A017C45B148D719D9A63CDB7BE6F48C812E33B68161D5AB3A0A36906F04A6A6957E6F4FB2E0",16);
  mpn_set_mpz(Pay0, Pay0_z);
  mpz_set_str(Pay1_z,"0000FD87F67EA576CE97FF65BF9F4F7688C4C752DCE9F8BD2B36AD66E04249AAF8337C01E6E4E1A844267BA1A1887B433729E1DD90C7DD2F",16);
  mpn_set_mpz(Pay1, Pay1_z);

  mpz_set_str(Qay0_z,"0001D407B70B01E4AEE172EDF491F4EF32144F03F5E054CEF9FDE5A35EFA3642A11817905ED0D4F193F31124264924A5F64EFE14B6EC97E5",16);
  mpn_set_mpz(Qay0, Qay0_z);
  mpz_set_str(Qay1_z,"0000E7DEC8C32F50A4E735A839DCDB89FE0763A184C525F7B7D0EBC0E84E9D83E9AC53A572A25D19E1464B509D97272AE761657B4765B3D6",16);
  mpn_set_mpz(Qay1, Qay1_z);

  mpz_set_str(Pby0_z,"00006AE515593E73976091978DFBD70BDA0DD6BCAEEBFDD4FB1E748DDD9ED3FDCF679726C67A3B2CC12B39805B32B612E058A4280764443B",16);
  mpn_set_mpz(Pby0, Pby0_z);
  mpz_set_str(Pby1_z,"00000000",16);
  mpn_set_mpz(Pby1, Pby1_z);
  
  mpz_set_str(Qby0_z,"00000000",16);
  mpn_set_mpz(Qby0, Qby0_z);
  mpz_set_str(Qby1_z,"0000EBAAA6C731271673BEECE467FD5ED9CC29AB564BDED7BDEAA86DD1E0FDDF399EDCC9B49C829EF53C7D7A35C3A0745D73C424FB4A5FD2",16);
  mpn_set_mpz(Qby1, Qby1_z);

  efp2_set_mpn2(&Pa, Pax0, Pax1, Pay0, Pay1);
  efp2_set_mpn2(&Qa, Qax0, Qax1, Qay0, Qay1);
  efp2_set_mpn2(&Pb, Pbx0, Pbx1, Pby0, Pby1);
  efp2_set_mpn2(&Qb, Qbx0, Qbx1, Qby0, Qby1);

  gmp_printf("\nmodulo polynomial\n");

  gmp_printf("fp2  = fp[alpha]/(alpha^2 -%Nu)\n",base_c.x0,FPLIMB);
  gmp_printf("fp6 = fp2[beta]/(beta^3 -alpha)\n");

  fp_println("base_c     = ",&base_c);
  fp_println("base_c_inv = ",&base_c_inv);
  printf("---------------------------------\n");
  miller_loop_v = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0};
  finalexp_pow_x = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 1};
  finalexp_pow_x_1 = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 1};
  finalexp_pow_3w = {0, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0,  1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  1, 0, -1, 0,  1, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1};
  finalexp_pow_w =  {0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0,  0, 0, -1, 0,  0, 0, 0, 0, 0, 0, 0, 0,  1};
}

void check_base(){
  fp_t tmp,base_d;
  fp2_t tmp2;
  fp_init(&tmp);
  fp_init(&base_d);
  fp_set_ui(&base_d, 4);
  fp_set_neg(&base_d, &base_d);
  fp2_init(&tmp2);
  mpz_t expo;
  mpz_init(expo);

  //check base_c = QNR
  mpz_sub_ui(expo,prime_z,1);
  mpz_divexact_ui(expo,expo,2);
  fp_pow(&tmp,&base_c,expo);
  if(fp_cmp_one(&tmp)==0) printf("error!!! c^((p-1)/2)==1\n\n");

  // mpz_sub_ui(expo,prime_z,1);
  // mpz_divexact_ui(expo,expo,3);
  // fp_pow(&tmp,&base_c,expo);
  // if(fp_cmp_one(&tmp)==0) printf("error!!! c^(p-1)/3==1\n\n");

  // //check base_c = QNR
  // mpz_sub_ui(expo,prime_z,1);
  // mpz_divexact_ui(expo,expo,2);
  // fp_pow(&tmp,&base_d,expo);
  // if(fp_cmp_one(&tmp)==0) printf("error!!! -4^((p-1)/2)==1\n\n");

  // mpz_sub_ui(expo,prime_z,1);
  // mpz_divexact_ui(expo,expo,3);
  // fp_pow(&tmp,&base_d,expo);
  // if(fp_cmp_one(&tmp)==0) printf("error!!! -4^(p-1)/3==1\n\n");

  // fp2_t base_fp2;
  // fp2_init(&base_fp2);
  // fp2_set_ui_ui(&base_fp2, 0);
  // fp_set_ui(&base_fp2.x1,2);
  // mpz_mul(expo,prime_z,prime_z);
  // mpz_sub_ui(expo,expo,1);
  // mpz_divexact_ui(expo,expo,3);
  // fp2_pow(&base_fp2,&base_fp2,expo);
  // if(fp2_cmp_one(&base_fp2)==0) printf("error!!! c^(p^2-1)/3==1\n\n");

  mpz_clear(expo);
}

void frobenius_precalculation(){
  fp_t tmp;
  fp_t base_d;
  mpz_t expo;
  fp_init(&tmp);
  fp_init(&base_d);
  fp_set_ui(&base_d,4);
  fp_set_neg(&base_d,&base_d);
  mpz_init(expo);

  mpz_sub_ui(expo,prime_z,1);
  mpz_divexact_ui(expo,expo,6);

  fp_pow(&tmp,&base_d,expo);
  fp_set(&frobenius_1_6,&tmp);
  fp_to_montgomery(&frobenius_1_6MR, &frobenius_1_6);
  fp_printf("\n1_6\n",&frobenius_1_6);
  mpz_set_ui(expo,2);
  fp_pow(&frobenius_2_6,&tmp,expo);
  fp_to_montgomery(&frobenius_2_6MR, &frobenius_2_6);
  fp_printf("\n2_6\n",&frobenius_2_6);

  mpz_set_ui(expo,4);
  fp_pow(&frobenius_4_6,&tmp,expo);
  fp_to_montgomery(&frobenius_4_6MR, &frobenius_4_6);
  fp_printf("\n4_6\n",&frobenius_4_6);

  mpz_set_ui(expo,5);
  fp_pow(&frobenius_5_6,&tmp,expo);
  fp_to_montgomery(&frobenius_5_6MR, &frobenius_5_6);
  fp_printf("\n5_6\n",&frobenius_5_6);

  mpz_clear(expo);

}

void curve_search(){
  mpz_t s;
  mpz_init(s);
  mpz_add_ui(s,prime_z,1);
  mpz_sub(s,s,trace_z);

  fp_set_ui(&curve_b,1);
  fp_set_neg(&curve_b,&curve_b);

  mpz_clear(s);

  fp2_set_ui(&Ea,6);
  fp2_set_ui(&Eb,1);

  printf("Elliptic curve search is done\n");
}

void frobenius_trace(mpz_t *trace,unsigned int m){
  mpz_t t_m[33];
  mpz_t t_2,tmp1,tmp2;
  for(int i=0;i<33;i++) mpz_init(t_m[i]);
  mpz_init(t_2);
  mpz_init(tmp1);
  mpz_init(tmp2);

  mpz_set(t_m[0],trace_z);

  mpz_mul(t_2,trace_z,trace_z);
  mpz_mul_ui(tmp1,prime_z,2);
  mpz_sub(t_2,t_2,tmp1);
  mpz_set(t_m[1],t_2);

  for(int i=2;i<m;i++){
    mpz_mul(tmp1,trace_z,t_m[i-1]);
    mpz_mul(tmp2,prime_z,t_m[i-2]);
    mpz_sub(t_m[i],tmp1,tmp2);
  }
  mpz_set(*trace,t_m[m-1]);

  for(int i=0;i<33;i++) mpz_clear(t_m[i]);
  mpz_clear(t_2);
  mpz_clear(tmp1);
  mpz_clear(tmp2);
}

void efpm_order(mpz_t *order,unsigned int m){
  mpz_t trace;
  mpz_init(trace);

  frobenius_trace(&trace,m);
  mpz_pow_ui(*order,prime_z,m);
  mpz_add_ui(*order,*order,1);
  mpz_sub(*order,*order,trace);

  mpz_clear(trace);
}

void create_weil(){
  // efpm_order(&efp_total,1);
  // efpm_order(&efp2_total,2);
  // efpm_order(&efp6_total,6);
  // mpz_t temp;
  // mpz_init(temp);
  mpz_add_ui(efp_total,prime_z,1);        //p+1
  mpz_mul(efp2_total,efp_total,efp_total);//(p+1)^2
  // frobenius_trace(&temp,6);
  // mpz_add(fp6_total_r,efp6_total,temp);
  // mpz_sub_ui(fp6_total_r,fp6_total_r,2);
  // mpz_divexact(fp6_total_r,fp6_total_r,order_z);
  // mpz_set(miller_loop_s,X_z);

  // mpz_sub(hardpart,hardpart,prime_z);
  // mpz_add_ui(hardpart,hardpart,1);
  // mpz_divexact(hardpart,hardpart,order_z);

  // mpz_set_str(hp_3w,"1811507161526425387769904",10);
  
  // mpz_clear(temp);

  // mpz_sub_ui(X_1,X_z,1);

  // mpz_mul(X_2,X_z,X_z);

}

void tmp_init(){
  //mpz_init(X_z);
  mpz_init(prime_z);
  //mpz_init(order_z);
  mpz_init(trace_z);

  mpz_init(efp_total);
  mpz_init(efp2_total);
  // mpz_init(efp6_total);
  // mpz_init(fp6_total_r);

  mpz_init(miller_loop_s);
  mpz_init(X_1_div2);
  mpz_init(X_1);
  mpz_init(X_2);
  mpz_init(X_2_1);
  mpz_init_set_ui(four,4);

  mpz_init(hardpart);
  mpz_init(hp_3w);
  mpz_init_set_ui(four,4);
  mpz_init_set_ui(three,3);

}