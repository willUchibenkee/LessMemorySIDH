// gety.c

#include<stdio.h>
#include<stdlib.h>
#include"efp2.h"
#include<gmp.h>

#define a0x0 423
#define a0x1 329
#define ka 11
#define kb 2
#define eA 4
#define eB 3
#define la 2
#define lb 3

void isogeny_gety(fp2 *y, fp2 *x, fp2 *A);

int main(void){
    ec2 P;
    fp2 newa;

    mpz_init(prime_z);
    mpz_set_ui(prime_z, p);

    // fp2_init(&ans.x);
    // fp2_init(&ans.y);

    fp2_init(&P.x);
    fp2_init(&P.y);

    fp2_init(&newa);

    mpz_init(P.inf);
    //mpz_init(ans.inf);

    fp2_set_ui(&P.x, 85, 118);
    //fp2_set_ui(&P.y, 104, 410);

    //118i+85 118i+85, 274i+150

    fp2_set_ui(&newa, 132, 275);
    //275i + 132

    isogeny_gety(&P.y, &P.x, &newa);

    fp2_neg(&P.y, &P.y);

    printf("P:");
    PrintEC2(&P);

    return 0;
}

void isogeny_gety(fp2 *y, fp2 *x, fp2 *A){
    // y**2=x**3+Ax**2+x
    fp2 temp, temp2;

    fp2_init(&temp);
    fp2_init(&temp2);

    mpz_t three;
    mpz_init(three);
    mpz_set_ui(three, 3);

    fp2_scalarexp(&temp, x, three);

    fp2_mul(&temp2, A, x);
    fp2_mul(&temp2, &temp2, x);

    fp2_add(&temp, &temp, &temp2);

    fp2_add(&temp, &temp, x);

    if(fp2_legendre(&temp) == 1){
        printf("temp:");

        fp2_printf(&temp);

        fp2_sqrt(y, &temp);
    }else{
        printf("no y\n");
    }
}