//smaallp.c   このプログラムの名前

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gmp.h>
#include"small_Isogeny.c"

#define Pax "f8 64"
#define Pay "c7 130"

#define Qax "18a 1aa"
#define Qay "4f 33"

#define Pbx "113 166"
#define Pby "68 19a"

#define Qbx "b9 14"
#define Qby "ef 119"

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

    Pa.inf = 0;
    Pb.inf = 0;
    Qa.inf = 0;
    Qb.inf = 0;

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
    // Fp2_to_Mont(&bA0, &bA0);


    // Fp2_to_Mont(&Pb.x, &Pb.x);
    // Fp2_to_Mont(&Pb.y, &Pb.y);
    // Fp2_to_Mont(&Qb.x, &Qb.x);
    // Fp2_to_Mont(&Qb.y, &Qb.y);

    Isogeny_gets(&Sa, &Pa, &Qa, &kam, &aA0);
    //Isogeny_gets(&Sb, &Pb, &Qb, &kbm, &bA0);

    //kqa(295,26, 233,389) hex:127,1A    e9,185

    // bin   11 は 1011

    Fp2_from_Mont(&Sa.x);
    Fp2_from_Mont(&Sa.y);
    // Fp2_from_Mont(&Sb.x);
    // Fp2_from_Mont(&Sb.y);

    printf("SaとSb\n");
    Efp2_PrintEC2(&Sa); //271i + 79, 153i + 430

    ec2 U, V, ANS;
    Fp2 ap;

    Fp2_set_str(&U.x, "18a 1aa");
    Fp2_set_str(&U.y, "4f 33");
    Fp2_set_str(&V.x, "3b a7");
    Fp2_set_str(&V.y, "90 6c");
    Fp2_set_str(&ap, "1a7 149");
    U.inf = 0;
    V.inf = 0;
    ANS.inf = 0;

    Fp2_to_Mont(&U.x, &U.x);
    Fp2_to_Mont(&U.y, &U.y);
    Fp2_to_Mont(&V.x, &V.x);
    Fp2_to_Mont(&V.y, &V.y);
    Fp2_to_Mont(&ANS.x, &ANS.x);
    Fp2_to_Mont(&ANS.y, &ANS.y);

    Fp2_to_Mont(&ap, &ap);

    Efp2_mgecA(&ANS, &U, &V, &ap);
    printf("ANS:");
    Fp2_from_Mont(&ANS.x);
    Fp2_from_Mont(&ANS.y);
    Efp2_PrintEC2(&ANS);

    return 0;

}