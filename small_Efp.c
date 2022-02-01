// small_Efp.c(Montgomery)

#include "small_pairing.h"
#include <stdio.h>
#include"small_Fp1.c"
#include <string.h>

#define Aval "6" //sidh_specから

Fp A;

void Efp_set_A(){
    Fp_set_str(&A, Aval);
}

//点の出力
int Efp_PrintEC(ec *op){
    if( op->inf == 1 )printf("!Inf!\n");
    else {
        Fp_print(&op->x);
        Fp_print(&op->y);
    }
}

int Efp_checkans(ec *P, Fp *ap){
    Fp wx, wy, uhen, sahen, work;
    Fp_set(&wx, &P->x);
    Fp_set(&wy, &P->y);

    Fp_to_Mont(&wx, &wx);
    Fp_to_Mont(&wy, &wy);
    //Fp_to_Mont(ap, ap);

    Fp_mul(&sahen, &wy, &wy);

    Fp_mul(&uhen, &wx, &wx);
    Fp_mul(&uhen, &uhen, &wx);
    Fp_mul(&work, &wx, &wx);
    Fp_mul(&work, &work, ap);
    Fp_add(&uhen, &uhen, &work);
    Fp_add(&uhen, &uhen, &wx);

    Fp_from_Mont(&uhen);
    Fp_from_Mont(&sahen);
    //Fp_from_Mont(ap);
    
    if(Fp_cmp(&uhen, &sahen) == 0){
        return 0;
    }else{
        return 1;
    }
}

void Efp_mgecD(ec *R, ec *P, Fp *ap){
    Fp bumbo, bunshi, bumbo2, bunshi2, katamari, katamari2, work, work2, work3;
    Fp one, four, two2, three2;
    
    ec U;

    //tempoにinを保存

    Fp_set_str(&one, "1 0");
    Fp_set_str(&four, "4 0");
    Fp_set_str(&two2, "2 0");
    Fp_set_str(&three2, "3 0");

    if(P->inf == 1){
        R->inf = 1;
        // printf("R:infecd\n");
        // printf("%d\n", R->inf);
    }else{
        if(Fp_cmp_zero(&P->x) == 0 || Fp_cmp_zero(&P->y) == 0){
            P->inf = 1;
            // printf("P:inf\n");
            // printf("%d\n", R->inf);

        }else{
            //x座標

            //分子の計算
            Fp_mul(&bunshi, &P->x, &P->x);
            Fp_sub(&bunshi, &bunshi, &one);
            Fp_mul(&bunshi, &bunshi, &bunshi);
            // printf("bunshi:");
            // Fp_print(&bunshi);
            
            //分母の計算(最後にinv)
            Fp_mul(&bumbo, &P->x, &P->x);
            Fp_mul(&work, ap, &P->x); 
            Fp_add(&bumbo, &bumbo, &work);
            Fp_add(&bumbo, &bumbo, &one);
            Fp_mul(&bumbo, &bumbo, &P->x);
            Fp_mul(&bumbo, &bumbo, &four);
            // printf("bumbo(反転前):");
            // Fp_print(&bumbo);
            Fp_inv(&bumbo, &bumbo);
            
            //分子/分母
            Fp_mul(&U.x, &bunshi, &bumbo);
            
            //y座標
            //かたまり１
            //分子の計算
            Fp_mul(&work, &P->x, &two2);
            Fp_add(&work, &work, &P->x);
            Fp_add(&work, &work, ap);
            Fp_mul(&work2, &P->x, &P->x);
            Fp_mul(&work2, &work2, &three2);
            Fp_mul(&work3, &P->x, ap);
            Fp_mul(&work3, &work3, &two2);
            Fp_add(&work2, &work2, &work3);
            Fp_add(&work2, &work2, &one);
            Fp_mul(&bunshi, &work, &work2);
            
            //分母の計算(最後にinv)
            Fp_mul(&bumbo, &two2, &P->y);
            Fp_set(&bumbo2, &bumbo);
            Fp_inv(&bumbo, &bumbo);
            
            //分子/分母
            Fp_mul(&katamari, &bunshi, &bumbo);
            
            //かたまり２
            //分子の計算
            //Fp_sqr3(&bunshi2, &work2);
            Fp_mul(&bunshi2, &work2, &work2);
            Fp_mul(&bunshi2, &bunshi2, &work2);
            
            //分母の計算(最後にinv)
            //Fp_sqr3(&bumbo2, &bumbo2);
            Fp_mul(&work, &bumbo2, &bumbo2);
            Fp_mul(&bumbo2, &work, &bumbo2);
            Fp_inv(&bumbo2, &bumbo2);
   
            //分子/分母
            Fp_mul(&katamari2, &bunshi2, &bumbo2);
            Fp_sub(&U.y, &katamari, &katamari2);
            Fp_sub(&U.y, &U.y, &P->y);
            
            Fp_set(&R->x, &U.x);
            Fp_set(&R->y, &U.y);
            
        }
    }
    
}

void Efp_mgecA(ec *R, ec *P, ec *Q, Fp *ap){
    Fp bumbo, bunshi, bumbo2, bunshi2;
    Fp xsa, ysa, work, work2, katamari, katamari2, temp, temp2;
    Fp two;
    
    Fp_set_str(&two, "2 0");

    if(P->inf == 1){
        if(Q->inf == 1){
            R->inf = 1;
        }else{
            Fp_set(&R->x, &Q->x);
            Fp_set(&R->y, &Q->y);
            R->inf = 0;
            //printf("Rinf1 reset\n");
         }
    }else{
        if(Q->inf == 1){
            Fp_set(&R->x, &P->x);
            Fp_set(&R->y, &P->y);
            // R->inf = 0;
            // printf("Rinf3 reset\n");
        }else{
            if(Fp_cmp(&P->x, &Q->x) == 0 || Fp_cmp(&P->y, &Q->y) == 0){
                if(Fp_cmp(&P->x, &Q->x) == 0 && Fp_cmp(&P->y, &Q->y) == 0){
                    Efp_mgecD(R, P, ap);
                }else{
                    R->inf = 1;
                    // printf("R:infeca\n");
                    // printf("%d\n", R->inf);
                }
            }else{
                Fp_sub(&xsa, &Q->x, &P->x);
                Fp_sub(&ysa, &Q->y, &P->y);

                //x座標
                //分子の計算
                Fp_mul(&work, &Q->x, &P->y);
                Fp_mul(&work2, &Q->y, &P->x);
                Fp_sub(&bunshi, &work, &work2); 
                Fp_mul(&bunshi, &bunshi, &bunshi);
                
                //分母の計算(最後にinv)
                Fp_mul(&work, &xsa, &xsa);
                Fp_mul(&bumbo, &work, &P->x);
                Fp_mul(&bumbo, &bumbo, &Q->x);
                Fp_inv(&bumbo, &bumbo);

                //分子/分母
                Fp_mul(&temp2, &bumbo, &bunshi);

                //y座標
                //かたまり１
                //分子の計算
                Fp_mul(&bunshi, &P->x, &two);
                Fp_add(&bunshi, &bunshi, &Q->x);
                Fp_add(&bunshi, &bunshi, ap);
                Fp_mul(&bunshi, &bunshi, &ysa);               

                //分母の計算(最後にinv)
                Fp_inv(&bumbo, &xsa);

                //分子/分母
                Fp_mul(&katamari, &bumbo, &bunshi);

                //かたまり２
                //分子の計算
                //Fp_sqr3(&bunshi2, &ysa);
                Fp_mul(&bunshi2, &ysa, &ysa);
                Fp_mul(&bunshi2, &bunshi2, &ysa);

                //分母の計算(最後にinv)
                //Fp_sqr3(&bumbo2, &xsa);
                Fp_mul(&bumbo2, &xsa, &xsa);
                Fp_mul(&bumbo2, &bumbo2, &xsa);
                Fp_inv(&bumbo2, &bumbo2);


                //分子/分母
                Fp_mul(&katamari2, &bumbo2, &bunshi2);
                Fp_sub(&temp, &katamari, &katamari2);
                Fp_sub(&R->y, &temp, &P->y);
                Fp_set(&R->x, &temp2);
            }
        }
    }   
}

void Efp_to2(int *length, char *binary, Fp *in){
    int i = 0;
    // value[14] 32bit*14 448bit
    //2**32=4294967296 max
    //printf("%u\n", in->value[0]);
    for(int k = 0; k < MOD_WORDS; k++){
        while(in->value[k] != 0){
            binary[i] = (unsigned int)(in->value[k] % 2)+0x30;
            //sprintf(&binary[i], "%u", (unsigned int)(in->value[k] % 2));
            //printf("a %u\n", in->value[k] % 2);
            in->value[k] = in->value[k] / 2;
            //printf("b %c\n", binary[i]);
            i++;   
        }
        //printf("\n");
    }
    // for(int j = i; j >= 0; j--){
    //     printf("%c", binary[j]);
    // }
    *length = i;
    //printf("\n");
    
}

void Efp_mgecSCM(ec *R, ec *P, Fp *n, Fp *ap){
    ec S,T,F;
    S.inf = 1;
    T.inf = 0;

    // n(16進数)を2進数に変換してbinary[]に入れる
    int length = 0;
    length = WORD * MOD_WORDS;
    char binary[length + 1];
    Efp_to2(&length, binary, n);

    Fp_set(&T.x, &P->x);
    Fp_set(&T.y, &P->y);
    T.inf = P->inf;

    if(Fp_cmp_one(n)){
        Fp_set(&R->x, &P->x);
        Fp_set(&R->y, &P->y);
    }else{
        for(int k = length-1; k >= 0; k--){

            //printf("bin:%c\n", binary[k]);
            if(binary[k] == '1'){
                Efp_mgecA(&F, &S, &T, ap);
                Fp_set(&S.x, &F.x);
                Fp_set(&S.y, &F.y);
                //printf("a\n");
                //PrintEC2(&S);
            }
            Efp_mgecD(&F, &T, ap);
            Fp_set(&T.x, &F.x);
            Fp_set(&T.y, &F.y);
            //PrintEC2(&S);
            //printf("b\n");
            // printf("S.inf:%d\n", S.inf);
            // printf("T.inf:%d\n", S.inf);
        }
        //printf("\n");
        Fp_set(&R->x, &S.x);
        Fp_set(&R->y, &S.y);
        R->inf = S.inf;
    }
}