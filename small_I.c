//Small_I.c   このプログラムの名前

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gmp.h>
#include"small_Isogeny.c"

#define Pax "64 f8"
#define Pay "130 c7"

#define Qax "1aa 18a"
#define Qay "33 4f"

#define Pbx "166 113"
#define Pby "19a 68"

#define Qbx "14 b9"
#define Qby "119 ef"

int main(void){
    //define
    ec2 Pa, Qa, Ra, Sa;

    ec2 Pb, Qb, Rb, Sb;
    
    Fp2_set_str(&Pa.x, Pax);
    Fp2_set_str(&Pa.y, Pay);

    Fp2_set_str(&Pb.x, Pbx);
    Fp2_set_str(&Pb.y, Pby);

    Fp2_set_str(&Qa.x, Qax);
    Fp2_set_str(&Qa.y, Qay);

    Fp2_set_str(&Qb.x, Qbx);
    Fp2_set_str(&Qb.y, Qby);

    Fp kam, kbm;
    // kam = ka;
    // kbm = kb;
    Fp_set_str(&kam, ka);
    Fp_set_str(&kbm, kb);

    int lat, lbt;
    lat = la;
    lbt = lb;

    Isogeny_set_e();
    // Fp py;
    // Fp_set(&py, &ea);
    // printf("py=");
    // Fp_print(&py);
    //py=21
    int py = ea;
    //ea = ea / lat;
    // Fp_mul(&py, &lat, &lat);
    // Fp ichi;
    // Fp_set_str(&ichi, "1");
    // for(Fp_set_str(&count, "1"); Fp_cmp(&count, &ea) =! 0; Fp_add(&count, &count, &ichi)){
    //     Fp_mul(&py, )
    // }
    // py =  (int)pow((double)lat, (double)ea);

    int q;
    int i = 0;
    //Fp_set_str(&i, "0");

    Isogeny_set_a0();
    Fp2 newa;

    Fp2 alpha;
    Fp_set_p();
    Fp_set_Rsq();
    Fp_set_one();

    //公開鍵生成
    printf("公開鍵生成\n");
    
    //AliceGen
    //Fp_print(&ichi);

    //test(alice)
    printf("A0\n");
    Fp2_print(&aA0);
    printf("Pa\n");
    PrintEC2(&Pa);
    printf("Pb\n");
    PrintEC2(&Pb);
    printf("Qa\n");
    PrintEC2(&Qa);
    printf("Qb\n");
    PrintEC2(&Qb);

    printf("ka\n");
    Fp_print(&kam);
    printf("kb\n");
    Fp_print(&kbm);

    Fp2_to_Mont(&Pa.x, &Pa.x);
    Fp2_to_Mont(&Pa.y, &Pa.y);
    Fp2_to_Mont(&Qa.x, &Qa.x);
    Fp2_to_Mont(&Qa.y, &Qa.y);

    Fp2_to_Mont(&aA0, &aA0);
    Fp2_to_Mont(&bA0, &bA0);


    Fp2_to_Mont(&Pb.x, &Pb.x);
    Fp2_to_Mont(&Pb.y, &Pb.y);
    Fp2_to_Mont(&Qb.x, &Qb.x);
    Fp2_to_Mont(&Qb.y, &Qb.y);

    Isogeny_gets(&Sa, &Pa, &Qa, &kam, &aA0);
    Isogeny_gets(&Sb, &Pb, &Qb, &kbm, &bA0);

    Fp2_from_Mont(&Sa.x);
    Fp2_from_Mont(&Sa.y);
    Fp2_from_Mont(&Sb.x);
    Fp2_from_Mont(&Sb.y);

    printf("SaとSb\n");
    PrintEC2(&Sa); //271i + 79, 153i + 430
    PrintEC2(&Sb); //122i + 309, 291i + 374
//     //Sa
//   0x10f 0x4f
//   0x99 0x1ae
//      Sb
// 0x7a 0x135
// 0x123 0x176
//     //

    while(py > 0){
        //Efp2_mgecSCM(&Ra, &Sa, &py, &aA0);
        for(int j =0 ; j < py; j++){
            if(j == 0){
                Efp2_mgecD(&Ra, &Sa, &aA0);
            }else{
                Efp2_mgecD(&Ra, &Ra, &aA0);
            }
            //Efp2_mgecD(&Ra, &Sa, &aA0);
        }

        Isogeny_changea(&newa, &Ra.x);

        Isogeny_nextp(&Pb, &Pb, &Ra.x, lat);
        Isogeny_nextp(&Qb, &Qb, &Ra.x, lat);
        Isogeny_nextp(&Sa, &Sa, &Ra.x, lat);
        Fp2_set(&aA0, &newa);
        
        //py = py / lat;
        py = py - 1;
        //Fp_sub(&py, &py, &ichi);
        //printf("py = %d\n", py);
        i++;
    }
    printf("ループ回数:%d\n", i);

    //gmp_printf("PKA = (aA, PB, QB) = ((%Zd + %Zd i), (%Zd + %Zd i), (%Zd + %Zd i))\n", Aa0.x0, Aa0.x1, Pbp->x.x0, Pbp->x.x1, Qbp->x.x0, Qbp->x.x1);
    printf("PKA:aA:");
    Fp2_print(&aA0);
    printf("Pb:");
    PrintEC2(&Pb);
    printf("Qb:");
    PrintEC2(&Qb);
    Fp2 aa;
    Fp2_set(&aa, &aA0);

    //(423i + 179,(142i + 183, 119i + 360),(220i + 314, 289i + 10)).
    //aA: 0x1a7 0xb3
    //Pb: 0x8e 0xb7
    //0x77 0x168
    //Qb: 0xdc 0x13a
    //0x121 0xa

    printf("//////////////////////////////////////\n");

    //BobGen

    //test(bob)
    //mpz_divexact(eb, eb, lbt);
    //mpz_pow_ui(py, lbt, mpz_get_ui(eb));
    //gmp_printf("py = %Zd\n", py);
    //Fp_set(&py, &eb);
    py = eb;

    while(py > 0){
        
        Fp2_set(&Rb.x, &Sb.x);
        //Fp_set(&q, &py);
        q = py;
        //i = 0;
        //Fp_set_str(&i, "0");
        // while(mpz_cmp_ui(q, 1) != 0){
        //     mpz_tdiv_q_ui(q, q, 3);
        //     i++;
        // 
        for(i = 0; i < q; i++){
            Isogeny_mgec3(&Rb, &Rb, &bA0);
            //printf("a\n");
        }

        Isogeny_changeb(&newa, &Rb.x, &bA0);
        //fp2_printf(aip);

        Isogeny_nextp(&Pa, &Pa, &Rb.x, lbt);
        Isogeny_nextp(&Qa, &Qa, &Rb.x, lbt);
        Isogeny_nextp(&Sb, &Sb, &Rb.x, lbt);
        Fp2_set(&bA0, &newa);
        

        //fp2_printf(ap);
        //mpz_divexact(py, py, lbt);
        //Fp_sub(&py, &py, &ichi);
        py = py - 1;
        //printf("py = %d\n", py);
    }

    //gmp_printf("PKB = (aB, PA, QA) = ((%Zd + %Zd i), (%Zd + %Zd i), (%Zd + %Zd i))\n", ba0.x0, ba0.x1, Pap->x.x0, Pap->x.x1, Qap->x.x0, Qap->x.x1);
    printf("PKB:aB");
    Fp2_print(&bA0);
    PrintEC2(&Pa);
    PrintEC2(&Qa);

    //鍵共有
    printf("ここから鍵共有です\n");
    // while(fp2_checkans(Pap, &ba0) != 0){
    //     mpz_urandomm(Pap->y.x0, state, mp); 
    //     mpz_urandomm(Pap->y.x1, state, mp);
    // }
    // while(fp2_checkans(Qap, &ba0) != 0){
    //     mpz_urandomm(Qap->y.x0, state, mp); 
    //     mpz_urandomm(Qap->y.x1, state, mp);
    // }
    // while(fp2_checkans(Pbp, &aa) != 0){
    //     mpz_urandomm(Pbp->y.x0, state, mp); 
    //     mpz_urandomm(Pbp->y.x1, state, mp);
    // }
    // while(fp2_checkans(Qbp, &aa) != 0){
    //     mpz_urandomm(Qbp->y.x0, state, mp); 
    //     mpz_urandomm(Qbp->y.x1, state, mp);
    // }

    //AliceGet

    Isogeny_set_e();
    
    //alice
    printf("aliceの操作\n");
    Isogeny_gets(&Sa, &Pa, &Qa, &kam, &bA0);
    //mpz_divexact(ea, ea, lat);
    //mpz_pow_ui(py, lat, mpz_get_ui(ea));
    while(py > 0){
        for(int k = 0; k < py; k++){
            Efp2_mgecD(&Ra, &Sa, &bA0);
        }
        //fp2_printf(&Rap->x);

        Isogeny_changea(&newa, &Ra.x);
        Fp2_print(&newa);

        Isogeny_nextp(&Sa, &Sa, &Ra.x, lat);
        Fp2_set(&bA0, &newa);
        
        //mpz_divexact(py, py, lat);
        py = py - 1;

    }

    //BobGet

    //bob
    printf("bobの操作\n");
    PrintEC2(&Pb);
    //PrintEC2(Qbp);
    Fp2_neg(&Qb.y, &Qb.y);
    PrintEC2(&Qb);
    Isogeny_gets(&Sb, &Pb, &Qb, &kbm, &aa);
    //mpz_divexact(eb, eb, lbt);
    //mpz_pow_ui(py, lbt, mpz_get_ui(eb));
    Fp2 ai;

    while(py > 0){
        
        Fp2_set(&Rb.x, &Sb.x);
        //q = py;
        //Fp_set(&q, &py);
        q = py;
        //i = 0;
        // while(mpz_cmp_ui(q, 1) != 0){
        //     //mpz_tdiv_q_ui(q, q, 3);
        //     i++;
        // }
        for(i = 0; i < q; i++){
            Isogeny_mgec3(&Rb, &Rb, &aa);
            //printf("a\n");
        }


        Isogeny_changeb(&ai, &Rb.x, &aa);
        //fp2_printf(aip);

        Isogeny_nextp(&Sb, &Sb, &Rb.x, lbt);
        Fp2_set(&aa, &newa);

        Fp2_print(&aa);
        //mpz_divexact(py, py, lbt);
        py = py - 1;
        
    }

    return 0;
}