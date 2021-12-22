#include <stdio.h>
#include <time.h>
#include "my_pairing.h"
//#include "./tepla/ec.h"
#include <assert.h>
// #include <gmp.h>
// #include <sys/time.h>

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
#define ec_field(p)   (p->ec->field)
#define curve(p)   (p->ec)

//#define xcoord(p)   (p->x)
//#define ycoord(p)   (p->y)
//#define zcoord(p)   (p->z)


Fp prim;
Fp *p = &prim;
Fp _R2;
Fp *Rsq = &_R2;  //メンバー変数であることを示すために_r2とかとかしてる
Fp _one;
Fp *one = &_one;

#ifdef NOELIPS
//r*r(r=2^384)
 char *_r2 = "11988fe592cae3aa9a793e85b519952d67eb88a9939d83c08de5476c4c95b6d50a76e6a609d104f1f4df1f341c341746";
//73eda753299d7d483339d80809a1d80553bda402fffe5bfeffffffff00000001
 char *_r = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"; //モンゴメリ用
//           10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

 char *_p = "1a0111ea397fe69a4b1ba7b6434bacd764774b84f38512bf6730d2a0f6b0f6241eabfffeb153ffffb9feffffffffaaab"; //有限体F ｐの位数
// const char *_p = "2523648240000001ba344d80000000086121000000000013a700000000000013";    //bn254用

#else
//r*r(r=2^384)
 char *_r2 = "11988fe592cae3aa9a793e85b519952d67eb88a9939d83c08de5476c4c95b6d50a76e6a609d104f1f4df1f341c341746";
//            25A89BCDD12A69E16A61C7686D9AABCD92BF2DDE347E175CC6AF8D6C7C0BAB27973F8311688DACEC7367768798C228E55B65DCD69B30
//73eda753299d7d483339d80809a1d80553bda402fffe5bfeffffffff00000001
 char *_r = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"; //モンゴメリ用

const char *_p = 
  "4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787";
// 0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF

#endif


char tmp1[390], tmp2[390], tmp3[390], tmp4[390];


// double gettime() {
//    double t;
//    struct timeval tv;
//    gettimeofday(&tv, NULL);  // マイクロ秒単位で現在時刻を取得
//    t = (double)tv.tv_sec + (double)tv.tv_usec*1.0e-6;
//    return t;
// }

int main(void){
	double Tstart, Tend;
    Fp a, d,b1, c;
    Fp_set_str(&prim, _p);
    Fp_set_str(Rsq, _r2);
    Fp_set_str(one, "1");
//     Fp_set_str(one, "11988fe592cae3aa9a793e85b519952d67eb88a9939d83c08de5476c4c95b6d50a76e6a609d104f1f4df1f341c341746"); //Montgomery form "1 r*r
    
    #ifdef NOELIPS
    //よくわからないのでM C Lから持ってきた。
    Fp_set_str(&a, "fbbbe993d6edd17b8dfdcabfb1b87e927529f6e33ad3008b78bcadfeb91807e63968f556ae9f30bc9db598ce927605a");
     Fp_set_str(&d, "22539289b65be12425ef10e58b15437751a3f1d6b6710146dccb062935fa99be07dafadacd298979a16777cbe0833a");
     
    Fp_set_str(&b1, "4cd21d3d9bd636c4c111bbc2a0f822f34d955b71414db79d74db3001fcd4555b7f247828800c320d3ec8cb3135b1cd");
    Fp_print(p);

    #else
    char *a0str="2421588360005927984607856650380948874740347566614262338385959549516967104664009371572249529022451282564934338568282";
	char *a1str="46186706686475189562087790132757250644815001532431236646679947280047093693191486656342636317975455934633041310157";
	
    mpn_set_char(prime,6,_p);		//位数をセット
    Fp_set_str(&a,a0str);
    Fp_set_str(&b1,a1str);
     
    
  
    #endif
    Fp_print(&a);
    Fp_print(&b1);
   
//     printf("\n \
// ###########################################################\n \
// ###########################################################\n \
//                  テストスタート        \n 
// ###########################################################\n \
//     \n");
    
     clock_t begin = clock();
     for(int i=0;i<10000000;i++){
         Fp_mul(&c,&a,&b1);
      }
	  clock_t end = clock();
	 printf( "Fp_mult: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC );
	 Fp_print(&c);
	 
// 	  begin = clock();
// 	   for(int i=0;i<100;i++){
//          Fp_sub(&c,&a,&b);
//       }
//     end = clock();
//     printf( "Fp_sub: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC );
// 	Fp_print(&c);
// 	
// Fp_to_Mont(&a,&a);
// Fp_to_Mont(&b,&b);
// 	printf( "Fp_mul\n");
// 	Tstart = gettime();
// 	   for(int i=0;i<10000;i++){
//          Fp_mul(&c,&a,&b);
//       }
//  	Tend = gettime();
//  	printf("経過時間： %lf[sec]\n", Tend-Tstart);
//  	printf("c=\n");
//   	Fp_print(&c);

//    	Fp_mul(&c,&c,one);
//    	 	Fp_print(&c);
//    	Fp_inv(&c,&a);
//    	printf("逆元の値は：\n");
//    	Fp_print(&c);
// 
//     Fp_mul(&c,&c,&a);
//    	printf("単位元の値：\n");
//    	Fp_print(&c);
//    	
//    	Fp_mul(&c,&c,&a);
//    	printf("aの値に戻った！！！！！：\n");
//    	Fp_print(&c);
// 	 
	 
	  
	 
// 	 printf( "Fp_div\n");
// 	begin = clock();
// 	   for(int i=0;i<100;i++){
//          Fp_div2(&c,&a);
//       }
//     end = clock();
//     printf( "Fp_div: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC );
// 	  Fp_print(&c);
// 	  
// 	  
// 	  printf( "Fp_inv\n");
// 	  begin = clock();
// // 	   for(int i=0;i<100;i++){
//          Fp_inv(&c,&a);
// //       }
//     end = clock();
//     printf( "Fp_inv: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC );
// 　 Fp_print(&c);
// 	unsigned int num=WORD;
// 　printf("%d\n",num);
// 	num=UINT_MAX;
// 	printf("%u\n",num);
// 	printf("%x\n",num);
// 	printf("%x\n",LHALF_MASK);
// 	printf("%x\n",HWORD_BIT);
	    return 0;
}