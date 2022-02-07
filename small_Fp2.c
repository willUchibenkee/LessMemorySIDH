#include "small_pairing.h"
#include <stdio.h>
#include "small_Fp1.c"

// #define MICRO_CODE 

Fp reg_inv;

void Fp2_set_str(Fp2 *a, char* str){
    char *p, tmp[MOD_WORDS * WORD / 2 + 4];

    strcpy(tmp, str);
    p = tmp;
    
    while ((*p) != '\0') {
        if ((*p) == ' ') {
            break;
        }
        p++;
    }
    *p = '\0';

    Fp_set_str(elem0(a), tmp);
    Fp_set_str(elem1(a), ++p);
}

void Fp2_get_str(char* str, Fp2 *a){
    char str1[MOD_WORDS * WORD / 4 + 4], str2[MOD_WORDS * WORD / 4 + 4];

    Fp_get_str(str1, elem0(a));
    Fp_get_str(str2, elem1(a));

    sprintf(str, "%s %s", str1, str2);
}

void Fp2_print(Fp2 *a){
    char buf[MOD_WORDS * WORD / 2 + 4];
    Fp2_get_str(buf, a);
    printf("%s\n", buf);
}

void Fp2_add(Fp2 *c, Fp2 *a, Fp2 *b){
    Fp_add(&c->element[0], &a->element[0], &b->element[0]);
    Fp_add(&c->element[1], &a->element[1], &b->element[1]);
}

void Fp2_add1(Fp2 *c, Fp2 *a){
    Fp_add(&c->element[0], &a->element[0], one);
}

void Fp2_sub(Fp2 *c, Fp2 *a, Fp2 *b){
    Fp_sub(&c->element[0], &a->element[0], &b->element[0]);
    Fp_sub(&c->element[1], &a->element[1], &b->element[1]);
}

//karatuba法での計算
void Fp2_mul(Fp2 *c, Fp2 *a, Fp2 *b){
    Fp t[2];
    
    Fp_add(&t[0], elem0(a), elem1(a));    //T0
    Fp_from_Mont(&t[0]);
    printf("t[0] ");
    Fp_print(&t[0]);
    Fp_to_Mont(&t[0], &t[0]);

    Fp_add(&t[1], elem0(b), elem1(b));    //T1
    printf("t[1] ");
    Fp_from_Mont(&t[1]);
    Fp_print(&t[1]);
    Fp_to_Mont(&t[1], &t[1]);

    Fp_mul(&t[0], &t[0], &t[1]);   //T0=(a0+a1)*(b0+b1)
    Fp_from_Mont(&t[0]);
    printf("t[0] ");
    Fp_print(&t[0]);
    Fp_to_Mont(&t[0], &t[0]);

    Fp_mul(&t[1], elem0(a), elem0(b));    //T0
    printf("t[1] ");
    Fp_from_Mont(&t[1]);
    Fp_print(&t[1]);
    Fp_to_Mont(&t[1], &t[1]);

    Fp_mul(elem1(c), elem1(a), elem1(b));    //T1
    printf("c1 ");
    Fp_from_Mont(elem1(c));
    Fp_print(elem1(c));
    Fp_to_Mont(elem1(c), elem1(c));

    Fp_sub(elem0(c), &t[1], elem1(c));   //T4
    printf("c0 ");
    Fp_from_Mont(elem0(c));
    Fp_print(elem0(c));
    Fp_to_Mont(elem0(c), elem0(c));

    Fp_add(&t[1], elem1(c), &t[1]);    //T3
    printf("t[1] ");
    Fp_from_Mont(&t[1]);
    Fp_print(&t[1]);
    Fp_to_Mont(&t[1], &t[1]);

    Fp_sub(elem1(c), &t[0], &t[1]);   //T3
    printf("c1 ");
    Fp_from_Mont(elem1(c));
    Fp_print(elem1(c));
    Fp_to_Mont(elem1(c), elem1(c));
}

void Fp2_mul_acc(Fp2 *c, Fp2 *a, Fp2 *b){
    Fp t[3];

    Fp_add(&t[0], elem0(a), elem1(a));    //t0
    Fp_add(&t[1], elem0(b), elem1(b));    //t1
    Fp_mul(&t[2], &t[0], &t[1]);   //T2
 
    Fp_mul(&t[0], elem0(a), elem0(b));    //T0
    Fp_mul(&t[1], elem1(a), elem1(b));    //T1
    Fp_sub(&t[2], &t[2], &t[0]);   //T3
    Fp_sub(&t[2], &t[2], &t[1]);   //T3
    Fp_sub(&t[0], &t[0], &t[1]);   //T4
    Fp_add(elem1(c), elem1(c), &t[2]);
    Fp_add(elem0(c), elem0(c), &t[0]);
}

//２乗計算（karatuba法）c0=a0^2-b0^2,c1=2a1*a0
void Fp2_sqr2(Fp2 *c, Fp2 *a){
    Fp t[3];

    Fp_add(&t[0], elem1(a), elem1(a));    //t0
    Fp_add(&t[1], elem0(a), elem1(a));    //t1
    Fp_sub(&t[2], elem0(a), elem1(a));    //t2
    Fp_mul(elem1(c), &t[0], elem0(a));  //t0
    Fp_mul(elem0(c), &t[1], &t[2]);   //t1
}

//3乗計算（karatuba法）c0=a0^2-b0^2,c1=2a1*a0
void Fp2_sqr3(Fp2 *c, Fp2 *a){
    Fp2_sqr2(c, a);
    Fp2_mul(c, c, a);
}

int Fp2_pow_c3(Fp2 *z,Fp2 *a){
	char *c3="1101000000001000100011110101000111001011111111110011010011010010010110001101110100111101101100100001101001011101011001101011101100100011101110100101110000100111100111000010100010010101111110110011100110000110100101010000011110110101100001111011000100100000111101010101111111111111111101011000101010011111111111111111110111001111111101111111111111111111111111111111110101010101010";
	Fp2 t;
    Fp2_set(&t,a);
    // Fp_print(&t);
    //Left-to-right binary
    for(int i = 1; i < 379; i++){
        Fp2_mul(&t, &t, &t);
        if(*(c3 + i) == '1') {
            Fp2_mul(&t, &t, a);
            // printf("はいったよ");
        }
    }
   Fp2_set(z,&t);
}


void Fp2_div2(Fp2 *c, Fp2 *a){
    Fp_div2(elem0(c), elem0(a));
    Fp_div2(elem1(c), elem1(a));
}
//-aを計算(加算の逆元）
void Fp2_neg(Fp2 *c, Fp2 *a){
    Fp_neg(elem0(c), elem0(a));
    Fp_neg(elem1(c), elem1(a));
}
//1-uをかけたということ
void Fp2_mul_ix(Fp2 *c, Fp2 *a){
    Fp t;
    Fp_add(&t, elem0(a), elem1(a));
    Fp_sub(elem1(c), elem1(a), elem0(a));
    Fp_set(elem0(c), &t);
}

//1/2(1-u)でやる！！！！！！！！！！！できた。
  void Fp2_mul_line(Fp2* c,Fp2* a){
     Fp t1, t2;
     Fp_add(&t1, elem0(a), elem1(a));
     Fp_div2(&t1,&t1);  //a+b
     Fp_sub(&t2, elem1(a), elem0(a));
     Fp_div2(elem1(c), &t2); //b-a
     Fp_set(elem0(c), &t1);
}
     
//1+uを掛けたということ
void Fp2_mul_xi(Fp2 *c, Fp2 *a){
    Fp t;
    Fp_sub(&t, elem0(a), elem1(a));
    Fp_add(elem1(c), elem0(a), elem1(a));
    Fp_set(elem0(c), &t);
}

void Fp2_mul_fp(Fp2 *c, Fp2 *a, Fp *b){
    Fp_mul(elem0(c), elem0(a), b);
    Fp_mul(elem1(c), elem1(a), b);
}

void Fp2_set(Fp2 *c, Fp2 *a){
    Fp_set(elem0(c), elem0(a));
    Fp_set(elem1(c), elem1(a));
}

//Fpを拡大退場の点としてみる。
void Fp2_set_fp(Fp2 *c, Fp *a){
    Fp_set(elem0(c), a);
    Fp_set_str(elem1(c), "0");
}

//フロビエンス写像用
void Fp2_frob_p(Fp2 *c, Fp2 *a){
    Fp_set(elem0(c), elem0(a));
    Fp_neg(elem1(c), elem1(a));
}

//a0-a1*uをもとめる
void Fp2_conj(Fp2 *c, Fp2 *a){
    Fp_set(elem0(c), elem0(a));
    Fp_neg(elem1(c), elem1(a));
}

//拡大体の逆元結果的にモンゴメリどめいんに乗らない可能性がある。
void Fp2_inv(Fp2 *c, Fp2 *a){
    Fp T0, T1;

    Fp_mul(&T0, elem0(a), elem0(a));        //1
    Fp_mul(&T1, elem1(a), elem1(a));        //2
    Fp_add(&T0, &T0, &T1);                  //3
    Fp_inv(&T0, &T0);                       //4
    Fp_mul(elem0(c), elem0(a), &T0);        //5
    Fp_mul(elem1(c), elem1(a), &T0);        //6
    Fp_neg(elem1(c), elem1(c));             //7
    
}

// (a0*a0+a1*a1)^(-1)を求める
void Fp2_inv_pre(Fp2 *a){
    Fp T0, T1;

    Fp_mul(&T0, elem0(a), elem0(a));        //1
    Fp_mul(&T1, elem1(a), elem1(a));        //2
    Fp_add(&T0, &T0, &T1);                  //3
    Fp_inv(&reg_inv, &T0);                  //4
}

//後半の処理を行う（前半部分はそれより前に求める）
void Fp2_inv_post(Fp2 *c, Fp2 *a){

    Fp_mul(elem0(c), elem0(a), &reg_inv);        //5
    Fp_mul(elem1(c), elem1(a), &reg_inv);        //6
    Fp_neg(elem1(c), elem1(c));             //7(-c１をc１に代入)
}

//モントメリドメイン乗の演算なのでを元に戻している
void Fp2_to_Mont(Fp2 *c, Fp2 *a){
    Fp_mul(elem0(c), elem0(a), Rsq);
    Fp_mul(elem1(c), elem1(a), Rsq);
}

void Fp2_from_Mont(Fp2 *a ){
    Fp first;
    Fp_set_str(&first, "1");
    Fp_mul(elem0(a), elem0(a), &first);
    Fp_mul(elem1(a), elem1(a),&first);
}

//等しいかどうかを調べる
int Fp2_equal(Fp2 *c,Fp2 *a){

    if(!( Fp_cmp(elem0(c),elem0(a))) && !( Fp_cmp(elem1(c),elem1(a)))){
       return 1;
    }else{
        return 0;
    }
}

//ひとしかったら0、それ以外は-1
int Fp2_cmp(Fp2 *a,Fp2 *b){
    if(Fp_cmp(elem0(a),elem0(b))==0 && Fp_cmp(elem1(a),elem1(b))==0){
        return 0;
    }else{
        return -1;
    }
}

int Fp2_cmp_zero(Fp2* a){
    Fp2 b;
    
    Fp2_set_str(&b, "0 0");
    if(Fp2_cmp(a,&b)==0){
        return 1;
    }else{
        return 0;
    }
}

int Fp2_cmp_one_mont(Fp2 *a){
    Fp2 b;
    Fp2_set_str(&b,"15f65ec3fa80e4935c071a97a256ec6d77ce5853705257455f48985753c758baebf4000bc40c0002760900000002fffd 0");
    if(Fp2_cmp(a,&b)==0){
        return 1;
   }else{
        return 0;
    }
}



//-aを求める
void _Fp_neg(Fp *c, Fp *a){
    Fp_sub(c, p, a);
}

//Fp2_legendre()
int Fp2_legendre(Fp2 *a){
	char *legendre_num="11010000000010001000111101010001110010111111111100110100110100100101100011011101001111011011001000011010010111010110011010111011001000111011101001011100001001111001110000101000100101011111101100111001100001101001010100000111101101011000011110110001001000001111010101011111111111111111010110001010100111111111111111111101110011111111011111111111111111111111111111111101010101010101";
	Fp2 t;
    Fp2_set(&t,a);
    // Fp_print(&t);
    //Left-to-right binary
    for(int i = 1; i < 380; i++){
        Fp2_mul(&t, &t, &t);
        if(*(legendre_num + i) == '1') {
            Fp2_mul(&t, &t, a);
            // printf("はいったよ");
        }
    }
    // Fp_from_Mont(&t);
    // Fp_print(&t);
    if(Fp2_cmp_one_mont(&t)==1){
      return 1;
    }else{
      return -1;
    }
}

// Fp2_sqrt()

void Fp2_sqrt(Fp2 *ANS,Fp2 *a){
  Fp2 c1,c2,c3,c4,c5;
  Fp2 z,t,c,b;

  Fp2_set_str(&c4,"161f998c5b49581b0849183769bd9b3dfad48bf9246cec972babb6cfe688d67b0893a1b4df74c0c185cc870e65ffbab2 0");
  Fp2_set_str(&c1,"1");
  Fp2_set_str(&c2,"d0088f51cbff34d258dd3db21a5d66bb23ba5c279c2895fb39869507b587b120f55ffff58a9ffffdcff7fffffffd555 0");
  Fp2_set_str(&c3,"680447a8e5ff9a692c6e9ed90d2eb35d91dd2e13ce144afd9cc34a83dac3d8907aaffffac54ffffee7fbfffffffeaaa 0");
  Fp2_set_str(&c5,"ef145240bdb3a8cc6f71b9a8e6cdf38670d0588614e9c73d15af739036c8ae69a622f2441999f9ef718bc78ccffcd52 0");

  Fp2_pow_c3(&z,a);
  // Fp_mul(&t,&z,a);
  // Fp_mul(&t,&z,&t);
  Fp2_mul(&z,&z,a);
  Fp2_set(ANS,&z);
}