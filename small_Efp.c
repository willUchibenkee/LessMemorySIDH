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
    
    ec U, v;
    ec *V = &v;

    Fp_set(xcoord(V), xcoord(P));
    Fp_set(ycoord(V), ycoord(P));
    V->inf = P->inf;

    //tempoにinを保存

    Fp_set_str(&one, "91");
    Fp_set_str(&two2, "122");
    Fp_set_str(&three2, "4");
    Fp_set_str(&four, "95");

    if(V->inf == 1){
        R->inf = 1;
        printf("R:infecd\n");
        printf("%d\n", R->inf);
    }else{
        if(Fp_cmp_zero(xcoord(V)) == 1 || Fp_cmp_zero(xcoord(V)) == 1){
            R->inf = 1;
            printf("P:inf\n");
            printf("%d\n", R->inf);

        }else{
            //x座標

            //分子の計算
            // (x**2-1)**2
            // bunshi=px*px%p
            // bunshi=(bunshi-1)%p
            // bunshi=bunshi*bunshi%p
            // print("bunshi:", hex(bunshi))

            Fp_mul(&bunshi, xcoord(V), xcoord(V));
            Fp_sub(&bunshi, &bunshi, &one);
            Fp_mul(&bunshi, &bunshi, &bunshi);
            // printf("bunshi:");
            // Fp_from_Mont(&bunshi);
            // Fp_print(&bunshi);
            // Fp_to_Mont(&bunshi, &bunshi);
            
            //分母の計算(最後にinv)
            Fp_mul(&bumbo, xcoord(V), xcoord(V));
            // Fp_from_Mont(&bumbo);
            // Fp_print(&bumbo);
            // Fp_to_Mont(&bumbo, &bumbo);
            
            Fp_mul(&work, ap, xcoord(V)); 
            // Fp_from_Mont(&work);
            // Fp_print(&work);
            // Fp_to_Mont(&work, &work);
            
            Fp_add(&bumbo, &bumbo, &work);
            // Fp_from_Mont(&bumbo);
            // Fp_print(&bumbo);
            // Fp_to_Mont(&bumbo, &bumbo);
            
            Fp_add(&bumbo, &bumbo, &one);
            // Fp_from_Mont(&bumbo);
            // Fp_print(&bumbo);
            // Fp_to_Mont(&bumbo, &bumbo);
            
            Fp_mul(&bumbo, &bumbo, xcoord(V));
            // Fp_from_Mont(&bumbo);
            // Fp_print(&bumbo);
            // Fp_to_Mont(&bumbo, &bumbo);
            
            Fp_mul(&bumbo, &bumbo, &four);
            // Fp_from_Mont(&bumbo);
            // Fp_print(&bumbo);
            // Fp_to_Mont(&bumbo, &bumbo);
            

            Fp_inv(&bumbo, &bumbo);
            
            //printf("bumbo:");
            // Fp_from_Mont(&bumbo);
            // Fp_print(&bumbo);
            // Fp_to_Mont(&bumbo, &bumbo);
            
            //分子/分母
            Fp_mul(&U.x, &bunshi, &bumbo);
            
            // printf("Ux:");
            // Fp_from_Mont(&U.x);
            // Fp_print(&U.x);
            // Fp_to_Mont(&U.x, &U.x);
            
            //y座標
            //かたまり１
            //分子の計算
            Fp_mul(&work, xcoord(V), &two2);
            Fp_add(&work, &work, xcoord(V));
            Fp_add(&work, &work, ap);
            Fp_mul(&work2, xcoord(V), xcoord(V));
            Fp_mul(&work2, &work2, &three2);
            Fp_mul(&work3, xcoord(V), ap);
            Fp_mul(&work3, &work3, &two2);
            Fp_add(&work2, &work2, &work3);
            Fp_add(&work2, &work2, &one);
            Fp_mul(&bunshi, &work, &work2);

            // printf("bunshi:");
            // Fp_from_Mont(&bunshi);
            // Fp_print(&bunshi);
            // Fp_to_Mont(&bunshi, &bunshi);
            
            //分母の計算(最後にinv)
            Fp_mul(&bumbo, &two2, ycoord(V));
            Fp_set(&bumbo2, &bumbo);
            Fp_inv(&bumbo, &bumbo);
            
            //分子/分母
            Fp_mul(&katamari, &bunshi, &bumbo);
            // printf("katamari:");
            // Fp_print(&katamari);
            
            //かたまり２
            //分子の計算
            //Fp_sqr3(&bunshi2, &work2);
            Fp_mul(&bunshi2, &work2, &work2);
            Fp_mul(&bunshi2, &bunshi2, &work2);
            // printf("bunshi2:");
            // Fp_print(&bunshi2);
            
            //分母の計算(最後にinv)
            //Fp_sqr3(&bumbo2, &bumbo2);
            Fp_mul(&work, &bumbo2, &bumbo2);
            Fp_mul(&bumbo2, &work, &bumbo2);
            Fp_inv(&bumbo2, &bumbo2);
   
            //分子/分母
            Fp_mul(&katamari2, &bunshi2, &bumbo2);
            Fp_sub(&U.y, &katamari, &katamari2);
            Fp_sub(&U.y, &U.y, ycoord(V));
            // printf("U.y:");
            // Fp_print(&U.y);
            
            Fp_set(&R->x, &U.x);
            Fp_set(&R->y, &U.y);
            
        }
    }
    
}

void Efp_mgecA(ec *R, ec *P, ec *Q, Fp *ap){
    Fp bumbo, bunshi, bumbo2, bunshi2;
    Fp xsa, ysa, work, work2, katamari, katamari2, temp, temp2;
    Fp two;

    Fp rmd;
    
    Fp_set_str(&two, "122");

    ec u, v;
    ec *U = &u;
    ec *V = &v;
    Fp_set(xcoord(U), xcoord(P));
    Fp_set(xcoord(V), xcoord(Q));
    Fp_set(ycoord(U), ycoord(P));
    Fp_set(ycoord(V), ycoord(Q));
    U->inf = P->inf;
    V->inf = Q->inf;
    //printf("copy\n");

    if(U->inf == 1){
        if(V->inf == 1){
            R->inf = 1;
        }else{
            //printf("Rinf1 reset\n");
            Fp_set(xcoord(R), xcoord(V));
            Fp_set(ycoord(R), ycoord(V));
            R->inf = 0;
            //printf("Rinf1 reset\n");
         }
    }else{
        if(Q->inf == 1){
            //printf("Rinf1 reset\n");
            Fp_set(xcoord(R), xcoord(U));
            Fp_set(ycoord(R), ycoord(U));
            R->inf = 0;
            //printf("Rinf3 reset\n");
        }else{
            if(Fp_cmp(xcoord(V), xcoord(U)) == 0 || Fp_cmp(ycoord(V), ycoord(U)) == 0){
                if(Fp_cmp(xcoord(V), xcoord(U)) == 0 && Fp_cmp(ycoord(V), ycoord(U)) == 0){
                    Efp_mgecD(R, P, ap);
                }else{
                    R->inf = 1;
                    //printf("R:infeca\n");
                    //printf("%d\n", R->inf);
                }
            }else{
                Fp_sub(&xsa, xcoord(V), xcoord(U));
                Fp_sub(&ysa, ycoord(V), ycoord(U));

                //x座標
                //分子の計算
//              #eca x: λ**2 − (xP + xQ) − A
                Fp_inv(&rmd, &xsa);
                Fp_mul(&rmd, &rmd, &ysa);

                // printf("rmd:");
                // Fp_print(&rmd);
                // ramda=(uy-py)%p
                // waru=(ux-px)%p
                // wari=pow(waru, -1, p)
                // rmd=ramda*wari%p

                // print("ramda:", hex(rmd))

                // rx=((rmd*rmd)%p -((px+ux)%p) - a)%p
                Fp_mul(xcoord(R), &rmd, &rmd);
                Fp_sub(xcoord(R), xcoord(R), xcoord(U));
                Fp_sub(xcoord(R), xcoord(R), xcoord(V));
                Fp_sub(xcoord(R), xcoord(R), ap);

                // printf("Rx:");
                // Fp_print(xcoord(R));
                // Fp_mul(&work, xcoord(V), ycoord(U));
                // Fp_mul(&work2, ycoord(V), xcoord(U));
                // Fp_sub(&bunshi, &work, &work2); 
                // Fp_mul(&bunshi, &bunshi, &bunshi);
                
                // //分母の計算(最後にinv)
                // Fp_mul(&work, &xsa, &xsa);
                // Fp_mul(&bumbo, &work, xcoord(U));
                // Fp_mul(&bumbo, &bumbo, ycoord(U));
                // Fp_inv(&bumbo, &bumbo);

                // //分子/分母
                // Fp_mul(&temp2, &bumbo, &bunshi);

                //y座標
                //かたまり１
                //分子の計算
                Fp_mul(&bunshi, xcoord(U), &two);
                Fp_add(&bunshi, &bunshi, xcoord(V));
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
                Fp_sub(ycoord(R), &temp, ycoord(U));
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

            printf("bin:%c\n", binary[k]);
            if(binary[k] == '1'){
                //printf("eca\n");
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

void Efp_mgecT(ec *R, ec *P, Fp *A){
    Fp temp, temp2;
    Fp three, four, six, nihachi, hex;

    ec u;
    ec *U = &u;
    Fp_set(xcoord(U), xcoord(P));
    Fp_set(ycoord(U), ycoord(P));
    U->inf = P->inf;

    Fp_set_str(&three, "4");
    Fp_set_str(&four, "95");
    Fp_set_str(&six, "8");
    Fp_set_str(&nihachi, "b5");
    Fp_set_str(&hex, "a5");
    //x 分子 (x**4 − 4Ax − 6x**2 − 3)**2*x
    Fp_mul(xcoord(R), xcoord(U), xcoord(U));
    Fp_mul(xcoord(R), xcoord(R), xcoord(U));
    Fp_mul(xcoord(R), xcoord(R), xcoord(U));

    Fp_mul(&temp, A, &four);
    Fp_mul(&temp, &temp, xcoord(U));

    Fp_sub(xcoord(R), xcoord(R), &temp);

    Fp_mul(&temp, &six, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));

    Fp_sub(xcoord(R), xcoord(R), &temp);

    Fp_sub(xcoord(R), xcoord(R), &three);

    Fp_mul(xcoord(R), xcoord(R), xcoord(R));

    Fp_mul(xcoord(R), xcoord(R), xcoord(U));

    //分母 (4Ax**3 + 3x**4 + 6x**2 − 1)**2
    Fp_mul(&temp, &four, A);
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));

    Fp_mul(&temp2, &three, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));

    Fp_add(&temp, &temp, &temp2);

    Fp_mul(&temp2, &six, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));

    Fp_add(&temp, &temp, &temp2);

    Fp_sub(&temp, &temp, one);

    Fp_mul(&temp, &temp, &temp);

    Fp_inv(&temp, &temp);

    Fp_mul(xcoord(R), xcoord(R), &temp);

    // y  分子 (x**4 − 4Ax − 6x**2 − 3)(x**8 + 4Ax**7 + 28x**6 + 28Ax**5 + (16A**2 + 6)x**4 + 28Ax**3 + 28x**2 + 4Ax + 1)
    Fp_mul(ycoord(R), xcoord(U), xcoord(U));
    Fp_mul(ycoord(R), ycoord(R), xcoord(U));
    Fp_mul(ycoord(R), ycoord(R), xcoord(U));
    // printf("x**4:");
    // Fp_from_Mont(ycoord(R));
    // Fp_print(ycoord(R));
    // Fp_to_Mont(ycoord(R), ycoord(R));

    Fp_mul(&temp, &four, A);
    Fp_mul(&temp, &temp, xcoord(U));
    // printf("4ax:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_sub(ycoord(R), ycoord(R), &temp);
    printf("hiki:");
    // Fp_from_Mont(ycoord(R));
    // Fp_print(ycoord(R));
    // Fp_to_Mont(ycoord(R), ycoord(R));

    Fp_mul(&temp, &six, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));

    Fp_sub(ycoord(R), ycoord(R), &temp);

    Fp_sub(ycoord(R), ycoord(R), &three);

    printf("zenhan:");
    Fp_from_Mont(ycoord(R));
    Fp_print(ycoord(R));
    Fp_to_Mont(ycoord(R), ycoord(R));
    //13

    //////////////////////////////////////////////////////////////////////

    Fp_mul(&temp, xcoord(U), xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    // printf("x8:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &four, A);
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    // printf("4Ax7:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);

    // printf("tasu:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &nihachi, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    // printf("28x6:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);
    // printf("tasu2:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &nihachi, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, A);
    // printf("28Ax5:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);
    // printf("tasu3:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &hex, A);
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_mul(&temp2, &temp2, A);
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp2, &temp2, &six);
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_mul(&temp2, &temp2, xcoord(U));
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_mul(&temp2, &temp2, xcoord(U));
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_mul(&temp2, &temp2, xcoord(U));
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_mul(&temp2, &temp2, xcoord(U));
    // printf("(16A**2+6)x4:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);
    // printf("tasu4:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &nihachi, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, A);
    // printf("x3:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);
    // printf("tasu5:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &nihachi, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    // printf("x3:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);
    // printf("tasu6:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &four, A);
    Fp_mul(&temp2, &temp2, xcoord(U));
    // printf("x:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);
    // printf("tasu7:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_add(&temp, &temp, one);

    // printf("kouhan:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);
    //18a

    Fp_mul(ycoord(R), ycoord(R), &temp);
    // printf("bunshi:");
    // Fp_from_Mont(ycoord(R));
    // Fp_print(ycoord(R));
    // Fp_to_Mont(ycoord(R), ycoord(R));
    //9f

    //分母 (4Ax**3 + 3x**4 + 6x**2 − 1)**3
    Fp_mul(&temp, &four, A);
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    Fp_mul(&temp, &temp, xcoord(U));
    // printf("x3:");
    // Fp_from_Mont(&temp);
    // Fp_print(&temp);
    // Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &three, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    // printf("x4:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);

    Fp_mul(&temp2, &six, xcoord(U));
    Fp_mul(&temp2, &temp2, xcoord(U));
    // printf("x2:");
    // Fp_from_Mont(&temp2);
    // Fp_print(&temp2);
    // Fp_to_Mont(&temp2, &temp2);

    Fp_add(&temp, &temp, &temp2);

    Fp_sub(&temp, &temp, one);
    printf("katamari:");
    Fp_from_Mont(&temp);
    Fp_print(&temp);
    Fp_to_Mont(&temp, &temp);

    Fp_mul(&temp2, &temp, &temp);
    Fp_mul(&temp2, &temp2, &temp);
    printf("ans:");
    Fp_from_Mont(&temp2);
    Fp_print(&temp2);
    Fp_to_Mont(&temp2, &temp2);

    Fp_inv(&temp2, &temp2);
    //188

    //////////////////////////////////////////////////////////////

    Fp_mul(ycoord(R), ycoord(R), &temp2);

    //////////////////////////////////////////////////////////////

    Fp_mul(ycoord(R), ycoord(R), ycoord(U));
    
}