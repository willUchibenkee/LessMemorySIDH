// efp2.h(Montgomery)

#include "my_pairing.h"
#include <stdio.h>
#include"Fp2.c"
#include <string.h>

#define Aval "6 0" //sidh_specから

Fp2 A;

void Efp2_set_A(){
    Fp2_set_str(&A, Aval);
}

//点の出力
int PrintEC2(ec2 *op){
    if( op->inf == 1 )printf("!Inf!\n");
    else {
        Fp2_print(&op->x);
        Fp2_print(&op->y);
    }
}

int Efp2_checkans(ec2 *P, Fp2 *ap){
    Fp2 wx, wy, uhen, sahen, work;
    Fp2_set(&wx, &P->x);
    Fp2_set(&wy, &P->y);

    Fp2_to_Mont(&wx, &wx);
    Fp2_to_Mont(&wy, &wy);
    //Fp2_to_Mont(ap, ap);

    Fp2_mul(&sahen, &wy, &wy);

    Fp2_mul(&uhen, &wx, &wx);
    Fp2_mul(&uhen, &uhen, &wx);
    Fp2_mul(&work, &wx, &wx);
    Fp2_mul(&work, &work, ap);
    Fp2_add(&uhen, &uhen, &work);
    Fp2_add(&uhen, &uhen, &wx);

    Fp2_from_Mont(&uhen);
    Fp2_from_Mont(&sahen);
    //Fp2_from_Mont(ap);
    
    if(Fp2_cmp(&uhen, &sahen) == 0){
        return 0;
    }else{
        return 1;
    }
}

void Efp2_mgecD(ec2 *R, ec2 *P, Fp2 *ap){
    Fp2 bumbo, bunshi, bumbo2, bunshi2, katamari, katamari2, work, work2, work3;
    Fp2 one, four, two2, three2;
    
    ec2 U;

    Fp2_to_Mont(&P->x, &P->x);
    Fp2_to_Mont(&P->y, &P->y);

    Fp2_set_str(&one, "1 0");
    Fp2_set_str(&four, "4 0");
    Fp2_set_str(&two2, "2 0");
    Fp2_set_str(&three2, "3 0");

    if(P->inf == 1){
        R->inf = 1;
    }else{
        if(Fp2_cmp_zero(&P->x) == 0 || Fp2_cmp_zero(&P->y) == 0){
            P->inf = 1;
        }else{
            //x座標

            //分子の計算
            Fp2_mul(&bunshi, &P->x, &P->x);
            Fp2_sub(&bunshi, &bunshi, &one);
            Fp2_mul(&bunshi, &bunshi, &bunshi);
            
            //分母の計算(最後にinv)
            Fp2_mul(&bumbo, &P->x, &P->x);
            Fp2_mul(&work, ap, &P->x); 
            Fp2_add(&bumbo, &bumbo, &work);
            Fp2_add(&bumbo, &bumbo, &one);
            Fp2_mul(&bumbo, &bumbo, &P->x);
            Fp2_mul(&bumbo, &bumbo, &four);
            Fp2_inv(&bumbo, &bumbo);
            
            //分子/分母
            Fp2_mul(&U.x, &bunshi, &bumbo);
            
            //y座標
            //かたまり１
            //分子の計算
            Fp2_mul(&work, &P->x, &two2);
            Fp2_add(&work, &work, &P->x);
            Fp2_add(&work, &work, ap);
            Fp2_mul(&work2, &P->x, &P->x);
            Fp2_mul(&work2, &work2, &three2);
            Fp2_mul(&work3, &P->x, ap);
            Fp2_mul(&work3, &work3, &two2);
            Fp2_add(&work2, &work2, &work3);
            Fp2_add(&work2, &work2, &one);
            Fp2_mul(&bunshi, &work, &work2);
            
            //分母の計算(最後にinv)
            Fp2_mul(&bumbo, &two2, &P->y);
            Fp2_set(&bumbo2, &bumbo);
            Fp2_inv(&bumbo, &bumbo);
            
            //分子/分母
            Fp2_mul(&katamari, &bunshi, &bumbo);
            
            //かたまり２
            //分子の計算
            //Fp2_sqr3(&bunshi2, &work2);
            Fp2_mul(&bunshi2, &work2, &work2);
            Fp2_mul(&bunshi2, &bunshi2, &work2);
            
            //分母の計算(最後にinv)
            //Fp2_sqr3(&bumbo2, &bumbo2);
            Fp2_mul(&work, &bumbo2, &bumbo2);
            Fp2_mul(&bumbo2, &work, &bumbo2);
            Fp2_inv(&bumbo2, &bumbo2);
   
            //分子/分母
            Fp2_mul(&katamari2, &bunshi2, &bumbo2);
            Fp2_sub(&U.y, &katamari, &katamari2);
            Fp2_sub(&U.y, &U.y, &P->y);

            Fp2_from_Mont(&U.x);
            Fp2_from_Mont(&U.y);
            
            Fp2_set(&R->x, &U.x);
            Fp2_set(&R->y, &U.y);
            
        }
    }
    
}

void Efp2_mgecA(ec2 *R, ec2 *P, ec2 *Q, Fp2 *ap){
    Fp2 bumbo, bunshi, bumbo2, bunshi2;
    Fp2 xsa, ysa, work, work2, katamari, katamari2, temp, temp2;
    Fp2 two;

    Fp2_to_Mont(&P->x, &P->x);
    Fp2_to_Mont(&P->y, &P->y);
    Fp2_to_Mont(&Q->x, &Q->x);
    Fp2_to_Mont(&Q->y, &Q->y);
    
    Fp2_set_str(&two, "2 0");

    if(P->inf == 1){
        if(Q->inf == 1){
            R->inf = 1;
        }else{
            Fp2_set(&R->x, &Q->x);
            Fp2_set(&R->y, &Q->y);
            R->inf = 0;
         }
    }else{
        if(Q->inf == 1){
            Fp2_set(&R->x, &P->x);
            Fp2_set(&R->y, &P->y);
            R->inf = 0;
        }else{
            if(Fp2_cmp(&P->x, &Q->x) == 0 || Fp2_cmp(&P->y, &Q->y) == 0){
                if(Fp2_cmp(&P->x, &Q->x) == 0 && Fp2_cmp(&P->y, &Q->y) == 0){
                    Efp2_mgecD(R, P, ap);
                }else{
                    R->inf = 1;
                }
            }else{
                Fp2_sub(&xsa, &Q->x, &P->x);
                Fp2_sub(&ysa, &Q->y, &P->y);

                //x座標
                //分子の計算
                Fp2_mul(&work, &Q->x, &P->y);
                Fp2_mul(&work2, &Q->y, &P->x);
                Fp2_sub(&bunshi, &work, &work2); 
                Fp2_mul(&bunshi, &bunshi, &bunshi);
                
                //分母の計算(最後にinv)
                Fp2_mul(&work, &xsa, &xsa);
                Fp2_mul(&bumbo, &work, &P->x);
                Fp2_mul(&bumbo, &bumbo, &Q->x);
                Fp2_inv(&bumbo, &bumbo);

                //分子/分母
                Fp2_mul(&temp2, &bumbo, &bunshi);

                //y座標
                //かたまり１
                //分子の計算
                Fp2_mul(&bunshi, &P->x, &two);
                Fp2_add(&bunshi, &bunshi, &Q->x);
                Fp2_add(&bunshi, &bunshi, ap);
                Fp2_mul(&bunshi, &bunshi, &ysa);               

                //分母の計算(最後にinv)
                Fp2_inv(&bumbo, &xsa);

                //分子/分母
                Fp2_mul(&katamari, &bumbo, &bunshi);

                //かたまり２
                //分子の計算
                Fp2_sqr3(&bunshi2, &ysa);

                //分母の計算(最後にinv)
                //Fp2_sqr3(&bumbo2, &xsa);
                Fp2_mul(&bumbo2, &xsa, &xsa);
                Fp2_mul(&bumbo2, &bumbo2, &xsa);
                Fp2_inv(&bumbo2, &bumbo2);


                //分子/分母
                Fp2_mul(&katamari2, &bumbo2, &bunshi2);
                Fp2_sub(&temp, &katamari, &katamari2);
                Fp2_sub(&R->y, &temp, &P->y);
                Fp2_set(&R->x, &temp2);

                Fp2_from_Mont(&R->x);
                Fp2_from_Mont(&R->y);
            }
        }
    }   
}

void Efp2_to2(char *binary, Fp *in){
    int i = 0;
    // value[14] 32bit*14 448bit
    //2**32=4294967296 max
    for(int k = 0; k < MOD_WORDS; k++){
        while(in->value[k] != '\0'){
            binary[i] = in->value[k] % 2;
            in->value[k] = in->value[k] / 2;
            i++;
        }
    }
    
}

void Efp2_mgecSCM(ec2 *R, ec2 *P, Fp *n, Fp2 *ap){
    ec2 S,T;
    S.inf = 1;
    T.inf = 0;

    // n(16進数)を2進数に変換してbinary[]に入れる
    int length = 0;
    length = WORD * MOD_WORDS;
    char binary[length + 1];
    Efp2_to2(binary, n);
    //

    Fp2_set(&T.x, &P->x);
    Fp2_set(&T.y, &P->y);
    T.inf = P->inf;

    if(Fp_cmp_one(n)){
        Fp2_set(&R->x, &P->x);
        Fp2_set(&R->y, &P->y);
    }else{
        for(int k = length-1; k >= 0; k--){
            if(binary[k] == '1'){
                Efp2_mgecA(&S, &S, &T, ap);
            }
            Efp2_mgecD(&T, &T, ap);
        }
        Fp2_set(&R->x, &S.x);
        Fp2_set(&R->y, &S.y);
        R->inf = S.inf;
    }
}

