// small_Efp.c(Montgomery)

#include "small_pairing.h"
#include <stdio.h>
#include"small_Fp2.c"
#include <string.h>

#define Aval "1a7 149" //sidh_specから

Fp2 A;

void Efp2_set_A(){
    Fp2_set_str(&A, Aval);
}

//点の出力
int Efp2_PrintEC2(ec2 *op){
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
    
    ec2 U, v;
    ec2 *V = &v;

    Fp2_set(xcoord(V), xcoord(P));
    Fp2_set(ycoord(V), ycoord(P));
    V->inf = P->inf;

    //tempoにinを保存

    Fp2_set_str(&one, "91 0");
    Fp2_set_str(&two2, "122 0");
    Fp2_set_str(&three2, "4 0");
    Fp2_set_str(&four, "95 0");

    //Fp2_print(ap);

    if(V->inf == 1){
        R->inf = 1;
        printf("P:inf ecd\n");
        //printf("%d\n", R->inf);
    }else{
        if(Fp2_cmp_zero(xcoord(V)) == 1 || Fp2_cmp_zero(xcoord(V)) == 1){
            //P->inf = 1;
            R->inf = 1;
            printf("P:x or y 0\n");
            //printf("%d\n", R->inf);

        }else{
            //x座標

            //分子の計算
            // (x**2-1)**2
            // bunshi=px*px%p
            // bunshi=(bunshi-1)%p
            // bunshi=bunshi*bunshi%p
            // print("bunshi:", hex(bunshi))

            Fp2_mul(&bunshi, xcoord(V), xcoord(V));
            Fp2_sub(&bunshi, &bunshi, &one);
            Fp2_mul(&bunshi, &bunshi, &bunshi);
            // printf("bunshi:");
            // Fp2_from_Mont(&bunshi);
            // Fp2_print(&bunshi);
            // Fp2_to_Mont(&bunshi, &bunshi);
            
            //分母の計算(最後にinv)
            Fp2_mul(&bumbo, xcoord(V), xcoord(V));
            // Fp2_from_Mont(&bumbo);
            // Fp2_print(&bumbo);
            // Fp2_to_Mont(&bumbo, &bumbo);
            
            Fp2_mul(&work, ap, xcoord(V)); 
            // Fp2_from_Mont(ap);
            // Fp2_from_Mont(xcoord(V));
            // Fp2_print(ap); //149 1a7
            // Fp2_print(xcoord(V)); //f8 64
            // Fp2_from_Mont(&work);
            // printf("//////////////////////////////////////////////\n");
            // Fp2_print(&work);
            // Fp2_to_Mont(&work, &work);
            // printf("//////////////////////////////////////////////\n");
            
            Fp2_add(&bumbo, &bumbo, &work);
            // Fp2_from_Mont(&bumbo);
            // Fp2_print(&bumbo);
            // Fp2_to_Mont(&bumbo, &bumbo);
            
            Fp2_add(&bumbo, &bumbo, &one);
            // Fp2_from_Mont(&bumbo);
            // Fp2_print(&bumbo);
            // Fp2_to_Mont(&bumbo, &bumbo);
            
            Fp2_mul(&bumbo, &bumbo, xcoord(V));
            // Fp2_from_Mont(&bumbo);
            // Fp2_print(&bumbo);
            // Fp2_to_Mont(&bumbo, &bumbo);  
            
            Fp2_mul(&bumbo, &bumbo, &four);
            // Fp2_from_Mont(&bumbo);
            // Fp2_print(&bumbo);
            // Fp2_to_Mont(&bumbo, &bumbo);
            

            Fp2_inv(&bumbo, &bumbo);
            
            //printf("bumbo:");
            // Fp2_from_Mont(&bumbo);
            // Fp2_print(&bumbo);
            // Fp2_to_Mont(&bumbo, &bumbo);
            
            //分子/分母
            Fp2_mul(&U.x, &bunshi, &bumbo);
            
            //printf("Ux:");
            // Fp2_from_Mont(&U.x);
            // Fp2_print(&U.x);
            // Fp2_to_Mont(&U.x, &U.x);
            
            //y座標
            //かたまり１
            //分子の計算
            Fp2_mul(&work, xcoord(V), &two2);
            Fp2_add(&work, &work, xcoord(V));
            Fp2_add(&work, &work, ap);
            Fp2_mul(&work2, xcoord(V), xcoord(V));
            Fp2_mul(&work2, &work2, &three2);
            Fp2_mul(&work3, xcoord(V), ap);
            Fp2_mul(&work3, &work3, &two2);
            Fp2_add(&work2, &work2, &work3);
            Fp2_add(&work2, &work2, &one);
            Fp2_mul(&bunshi, &work, &work2);


            
            //分母の計算(最後にinv)
            Fp2_mul(&bumbo, &two2, ycoord(V));

            Fp2_set(&bumbo2, &bumbo);
            Fp2_inv(&bumbo, &bumbo);

            // printf("inv 2y:");
            // Fp2_from_Mont(&bumbo);
            // Fp2_print(&bumbo);
            // Fp2_to_Mont(&bumbo, &bumbo);

            // printf("bunshi:");
            // Fp2_from_Mont(&bunshi);
            // Fp2_print(&bunshi);
            // Fp2_to_Mont(&bunshi, &bunshi);
            
            //分子/分母
            Fp2_mul(&katamari, &bunshi, &bumbo);
            // printf("katamari:");
            // Fp2_from_Mont(&katamari);
            // Fp2_print(&katamari);
            // Fp2_to_Mont(&katamari, &katamari);
            
            //かたまり２
            //分子の計算
            //Fp2_sqr3(&bunshi2, &work2);
            Fp2_mul(&bunshi2, &work2, &work2);
            Fp2_mul(&bunshi2, &bunshi2, &work2);

            //Fp2_from_Mont(&bunshi2);
            // printf("bunshi2:");
            // Fp2_print(&bunshi2);
            // Fp2_to_Mont(&bunshi2, &bunshi2);
            
            //分母の計算(最後にinv)
            //Fp2_sqr3(&bumbo2, &bumbo2);
            Fp2_mul(&work, &bumbo2, &bumbo2);
            Fp2_mul(&bumbo2, &work, &bumbo2);
            Fp2_inv(&bumbo2, &bumbo2);
   
            //分子/分母
            Fp2_mul(&katamari2, &bunshi2, &bumbo2);
            Fp2_sub(&U.y, &katamari, &katamari2);
            Fp2_sub(&U.y, &U.y, ycoord(V));

            // printf("U.y:");
            // Fp2_from_Mont(&U.y);
            // Fp2_print(&U.y);
            // Fp2_to_Mont(&U.y, &U.y);
            
            Fp2_set(&R->x, &U.x);
            Fp2_set(&R->y, &U.y);
            
        }
    }
    
}

void Efp2_mgecA(ec2 *R, ec2 *P, ec2 *Q, Fp2 *ap){
    Fp2 bumbo, bunshi, bumbo2, bunshi2;
    Fp2 xsa, ysa, work, work2, katamari, katamari2, temp, temp2;
    Fp2 two;

    Fp2 rmd;
    
    Fp2_set_str(&two, "122 0");

    // ec2 u, v;
    // ec2 *U = &u;
    // ec2 *V = &v;
    // Fp2_set(xcoord(U), xcoord(P));
    // Fp2_set(xcoord(V), xcoord(Q));
    // Fp2_set(ycoord(U), ycoord(P));
    // Fp2_set(ycoord(V), ycoord(Q));
    // U->inf = P->inf;
    // V->inf = Q->inf;
    //printf("copy\n");

    if(P->inf == 1){
        if(Q->inf == 1){
            R->inf = 1;
            printf("P,Q inf\n");
        }else{
            Fp2_set(xcoord(R), xcoord(Q));
            Fp2_set(ycoord(R), ycoord(Q));
            R->inf = 0;
            printf("Rinf1 reset: Q=R\n");
         }
    }else{
        if(Q->inf == 1){
            //printf("Rinf1 reset\n");
            Fp2_set(xcoord(R), xcoord(P));
            Fp2_set(ycoord(R), ycoord(P));
            R->inf = 0;
            printf("Rinf3 reset: P=R\n");
        }else{
            if(Fp2_cmp(xcoord(Q), xcoord(P)) == 0 || Fp2_cmp(ycoord(Q), ycoord(P)) == 0){
                if(Fp2_cmp(xcoord(Q), xcoord(P)) == 0 && Fp2_cmp(ycoord(Q), ycoord(P)) == 0){
                    Efp2_mgecD(R, P, ap);
                }else{
                    R->inf = 1;
                    //printf("R:infeca\n");
                    //printf("%d\n", R->inf);
                }
            }else{
                Fp2_sub(&xsa, xcoord(Q), xcoord(P));
                Fp2_sub(&ysa, ycoord(Q), ycoord(P));

                //x座標
                //分子の計算
//              #eca x: λ**2 − (xP + xQ) − A
                Fp2_inv(&rmd, &xsa);
                Fp2_mul(&rmd, &rmd, &ysa);

                // printf("rmd:");
                // Fp2_print(&rmd);
                // ramda=(uy-py)%p
                // waru=(ux-px)%p
                // wari=pow(waru, -1, p)
                // rmd=ramda*wari%p

                // print("ramda:", hex(rmd))

                // rx=((rmd*rmd)%p -((px+ux)%p) - a)%p
                Fp2_mul(xcoord(R), &rmd, &rmd);
                Fp2_sub(xcoord(R), xcoord(R), xcoord(P));
                Fp2_sub(xcoord(R), xcoord(R), xcoord(Q));
                Fp2_sub(xcoord(R), xcoord(R), ap);

                // printf("Rx:");
                // Fp2_print(xcoord(R));
                // Fp2_mul(&work, xcoord(V), ycoord(U));
                // Fp2_mul(&work2, ycoord(V), xcoord(U));
                // Fp2_sub(&bunshi, &work, &work2); 
                // Fp2_mul(&bunshi, &bunshi, &bunshi);
                
                // //分母の計算(最後にinv)
                // Fp2_mul(&work, &xsa, &xsa);
                // Fp2_mul(&bumbo, &work, xcoord(U));
                // Fp2_mul(&bumbo, &bumbo, ycoord(U));
                // Fp2_inv(&bumbo, &bumbo);

                // //分子/分母
                // Fp2_mul(&temp2, &bumbo, &bunshi);

                //y座標
                //かたまり１
                //分子の計算
                Fp2_mul(&bunshi, xcoord(P), &two);
                Fp2_add(&bunshi, &bunshi, xcoord(Q));
                Fp2_add(&bunshi, &bunshi, ap);
                Fp2_mul(&bunshi, &bunshi, &ysa);               

                //分母の計算(最後にinv)
                Fp2_inv(&bumbo, &xsa);

                //分子/分母
                Fp2_mul(&katamari, &bumbo, &bunshi);

                //かたまり２
                //分子の計算
                //Fp2_sqr3(&bunshi2, &ysa);
                Fp2_mul(&bunshi2, &ysa, &ysa);
                Fp2_mul(&bunshi2, &bunshi2, &ysa);

                //分母の計算(最後にinv)
                //Fp2_sqr3(&bumbo2, &xsa);
                Fp2_mul(&bumbo2, &xsa, &xsa);
                Fp2_mul(&bumbo2, &bumbo2, &xsa);
                Fp2_inv(&bumbo2, &bumbo2);


                //分子/分母
                Fp2_mul(&katamari2, &bumbo2, &bunshi2);
                Fp2_sub(&temp, &katamari, &katamari2);
                Fp2_sub(ycoord(R), &temp, ycoord(P));
            }
        }
    }   
}

void Efp2_to2(int *length, char *binary, Fp *in){
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

void Efp2_mgecSCM(ec2 *R, ec2 *P, Fp *n, Fp2 *ap){
    ec2 S,T;
    S.inf = 1;

    // n(16進数)を2進数に変換してbinary[]に入れる
    int length = 0;
    length = WORD * MOD_WORDS;
    char binary[length + 1];
    Efp2_to2(&length, binary, n);

    Fp2_set(&T.x, &P->x);
    Fp2_set(&T.y, &P->y);
    T.inf = P->inf;

    if(Fp_cmp_one(n)){
        Fp2_set(&R->x, &P->x);
        Fp2_set(&R->y, &P->y);
        R->inf = P->inf;
    }else{
        for(int k = length-1; k >= 0; k--){

            printf("k:%d\n", k);
            if(binary[k] == '1'){

                printf("eca\n");
                Efp2_mgecA(&S, &S, &T, ap);

                if(S.inf == 1){
                    printf("S: inf\n");
                }else{
                    printf("S:");
                    Efp2_PrintEC2(&S);
                }

            }
            Efp2_mgecD(&T, &T, ap);
            
            if(T.inf == 1){
                printf("T: inf\n");
            }else{
                printf("T:");
                Efp2_PrintEC2(&T);
            }

        }

        Fp2_set(&R->x, &S.x);
        Fp2_set(&R->y, &S.y);
        R->inf = S.inf;

    }
}

void Efp2_mgecT(ec2 *R, ec2 *P, Fp2 *A){
    Fp2 temp, temp2;
    Fp2 three, four, six, nihachi, hex, one2;

    ec2 u;
    ec2 *U = &u;
    Fp2_set(xcoord(U), xcoord(P));
    Fp2_set(ycoord(U), ycoord(P));
    U->inf = P->inf;

    Fp2_set_str(&one2, "91 0");
    Fp2_set_str(&three, "4 0");
    Fp2_set_str(&four, "95 0");
    Fp2_set_str(&six, "8 0");
    Fp2_set_str(&nihachi, "b5 0");
    Fp2_set_str(&hex, "a5 0");
    //x 分子 (x**4 − 4Ax − 6x**2 − 3)**2*x
    Fp2_mul(xcoord(R), xcoord(U), xcoord(U));
    Fp2_mul(xcoord(R), xcoord(R), xcoord(U));
    Fp2_mul(xcoord(R), xcoord(R), xcoord(U));

    Fp2_mul(&temp, A, &four);
    Fp2_mul(&temp, &temp, xcoord(U));

    Fp2_sub(xcoord(R), xcoord(R), &temp);

    Fp2_mul(&temp, &six, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));

    Fp2_sub(xcoord(R), xcoord(R), &temp);

    Fp2_sub(xcoord(R), xcoord(R), &three);

    Fp2_mul(xcoord(R), xcoord(R), xcoord(R));

    Fp2_mul(xcoord(R), xcoord(R), xcoord(U));

    //分母 (4Ax**3 + 3x**4 + 6x**2 − 1)**2
    Fp2_mul(&temp, &four, A);
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));

    Fp2_mul(&temp2, &three, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));

    Fp2_add(&temp, &temp, &temp2);

    Fp2_mul(&temp2, &six, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));

    Fp2_add(&temp, &temp, &temp2);

    Fp2_sub(&temp, &temp, &one2);

    Fp2_mul(&temp, &temp, &temp);

    Fp2_inv(&temp, &temp);

    Fp2_mul(xcoord(R), xcoord(R), &temp);

    // y  分子 (x**4 − 4Ax − 6x**2 − 3)(x**8 + 4Ax**7 + 28x**6 + 28Ax**5 + (16A**2 + 6)x**4 + 28Ax**3 + 28x**2 + 4Ax + 1)
    Fp2_mul(ycoord(R), xcoord(U), xcoord(U));
    Fp2_mul(ycoord(R), ycoord(R), xcoord(U));
    Fp2_mul(ycoord(R), ycoord(R), xcoord(U));
    // printf("x**4:");
    // Fp2_from_Mont(ycoord(R));
    // Fp2_print(ycoord(R));
    // Fp2_to_Mont(ycoord(R), ycoord(R));

    Fp2_mul(&temp, &four, A);
    Fp2_mul(&temp, &temp, xcoord(U));
    // printf("4ax:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_sub(ycoord(R), ycoord(R), &temp);
    //printf("hiki:");
    // Fp2_from_Mont(ycoord(R));
    // Fp2_print(ycoord(R));
    // Fp2_to_Mont(ycoord(R), ycoord(R));

    Fp2_mul(&temp, &six, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));

    Fp2_sub(ycoord(R), ycoord(R), &temp);

    Fp2_sub(ycoord(R), ycoord(R), &three);

    // printf("zenhan:");
    // Fp2_from_Mont(ycoord(R));
    // Fp2_print(ycoord(R));
    // Fp2_to_Mont(ycoord(R), ycoord(R));
    //13

    //////////////////////////////////////////////////////////////////////

    Fp2_mul(&temp, xcoord(U), xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    // printf("x8:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &four, A);
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    // printf("4Ax7:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);

    // printf("tasu:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &nihachi, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    // printf("28x6:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);
    // printf("tasu2:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &nihachi, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, A);
    // printf("28Ax5:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);
    // printf("tasu3:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &hex, A);
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_mul(&temp2, &temp2, A);
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp2, &temp2, &six);
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_mul(&temp2, &temp2, xcoord(U));
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_mul(&temp2, &temp2, xcoord(U));
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_mul(&temp2, &temp2, xcoord(U));
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_mul(&temp2, &temp2, xcoord(U));
    // printf("(16A**2+6)x4:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);
    // printf("tasu4:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &nihachi, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, A);
    // printf("x3:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);
    // printf("tasu5:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &nihachi, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    // printf("x3:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);
    // printf("tasu6:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &four, A);
    Fp2_mul(&temp2, &temp2, xcoord(U));
    // printf("x:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);
    // printf("tasu7:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_add(&temp, &temp, &one2);

    // printf("kouhan:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);
    //18a

    Fp2_mul(ycoord(R), ycoord(R), &temp);
    // printf("bunshi:");
    // Fp2_from_Mont(ycoord(R));
    // Fp2_print(ycoord(R));
    // Fp2_to_Mont(ycoord(R), ycoord(R));
    //9f

    //分母 (4Ax**3 + 3x**4 + 6x**2 − 1)**3
    Fp2_mul(&temp, &four, A);
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    Fp2_mul(&temp, &temp, xcoord(U));
    // printf("x3:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &three, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    // printf("x4:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);

    Fp2_mul(&temp2, &six, xcoord(U));
    Fp2_mul(&temp2, &temp2, xcoord(U));
    // printf("x2:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_add(&temp, &temp, &temp2);

    Fp2_sub(&temp, &temp, &one2);
    // printf("katamari:");
    // Fp2_from_Mont(&temp);
    // Fp2_print(&temp);
    // Fp2_to_Mont(&temp, &temp);

    Fp2_mul(&temp2, &temp, &temp);
    Fp2_mul(&temp2, &temp2, &temp);
    // printf("ans:");
    // Fp2_from_Mont(&temp2);
    // Fp2_print(&temp2);
    // Fp2_to_Mont(&temp2, &temp2);

    Fp2_inv(&temp2, &temp2);
    //188

    //////////////////////////////////////////////////////////////

    Fp2_mul(ycoord(R), ycoord(R), &temp2);

    //////////////////////////////////////////////////////////////

    Fp2_mul(ycoord(R), ycoord(R), ycoord(U));
    
}