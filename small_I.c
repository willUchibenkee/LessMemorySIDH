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

    int py = ea;

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

    //kqa(295,26, 233,389) hex:127,1A    e9,185
    //kqb(0,359),(233,230) hex:0, 167    e9,e6

    Fp2_from_Mont(&Sa.x);
    Fp2_from_Mont(&Sa.y);
    Fp2_from_Mont(&Sb.x);
    Fp2_from_Mont(&Sb.y);

    printf("SaとSb\n");
    Efp2_PrintEC2(&Sa); //271i + 79, 153i + 430
    Efp2_PrintEC2(&Sb); //122i + 309, 291i + 374
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
    Efp2_PrintEC2(&Pb);
    printf("Qb:");
    Efp2_PrintEC2(&Qb);
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
            Efp2_mgecT(&Rb, &Rb, &bA0);
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
    Efp2_PrintEC2(&Pa);
    Efp2_PrintEC2(&Qa);

    //鍵共有
    printf("ここから鍵共有です\n");

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
    Efp2_PrintEC2(&Pb);
    //Efp2_PrintEC2(Qbp);
    Fp2_neg(&Qb.y, &Qb.y);
    Efp2_PrintEC2(&Qb);
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
            Efp2_mgecT(&Rb, &Rb, &aa);
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

// kQ:(x(a,b),y(c,d))=((295,26),(233,389))
// Sa:(x(a,b),y(c,d))=((79,271),(430,153))
// kQ:(x(a,b),y(c,d))=((0,359),(233,230))
// Sb:(x(a,b),y(c,d))=((309,122),(374,291))
// (37, 18)
// (132, 275)
// (x(a,b),y(c,d))=((85,118),(104,410))
// (x(a,b),y(c,d))=((124,62),(239,281))
// (x(a,b),y(c,d))=((111,36),(430,153))
// (49, 7)
// (76, 273)
// (x(a,b),y(c,d))=((251,274),(104,410))
// (x(a,b),y(c,d))=((94,214),(239,281))
// (x(a,b),y(c,d))=((374,274),(430,153))
// (27, 245)
// (136, 93)
// (x(a,b),y(c,d))=((209,77),(104,410))
// (x(a,b),y(c,d))=((356,339),(239,281))
// (x(a,b),y(c,d))=((150,227),(430,153))
// (150, 227)
// (179, 423)
// (x(a,b),y(c,d))=((183,142),(104,410))
// (x(a,b),y(c,d))=((314,220),(239,281))
// (x(a,b),y(c,d))=((301,49),(430,153))
// //////////////////////////////////////
// (x(a,b),y(c,d))=((309,122),(374,291))
// (423, 329)
// a
// a
// (295, 358)
// (11, 425)
// (x(a,b),y(c,d))=((60,164),(199,304))
// (x(a,b),y(c,d))=((35,60),(79,51))
// (x(a,b),y(c,d))=((332,104),(374,291))
// (x(a,b),y(c,d))=((332,104),(374,291))
// (11, 425)
// a
// (71, 393)
// (387, 389)
// (x(a,b),y(c,d))=((92,420),(199,304))
// (x(a,b),y(c,d))=((255,110),(79,51))
// (x(a,b),y(c,d))=((378,278),(374,291))
// (x(a,b),y(c,d))=((378,278),(374,291))
// (387, 389)
// (378, 278)
// (174, 5)
// (x(a,b),y(c,d))=((294,189),(199,304))
// (x(a,b),y(c,d))=((384,416),(79,51))
// (x(a,b),y(c,d))=((169,119),(374,291))