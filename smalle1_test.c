//smalle1_test.c

#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include"small_Efp.c"

#define Px "12"
//Pax0 00003CCFC5E1F050030363E6920A0F7A4C6C71E63DE63A0E6475AF621995705F7C84500CB2BB61E950E19EAB8661D25C4A50ED279646CB48
//Pax1 0001AD1C1CAE7840EDDA6D8A924520F60E573D3B9DFAC6D189941CB22326D284A8816CC4249410FE80D68047D823C97D705246F869E3EA50
#define Py "6"
//Pay0 0001AB066B84949582E3F66688452B9255E72A017C45B148D719D9A63CDB7BE6F48C812E33B68161D5AB3A0A36906F04A6A6957E6F4FB2E0
//Pay1 0000FD87F67EA576CE97FF65BF9F4F7688C4C752DCE9F8BD2B36AD66E04249AAF8337C01E6E4E1A844267BA1A1887B433729E1DD90C7DD2F
//0x64
//0xf8
//0x130
//0xc7

int main(void){
    //定義とかもろもろ
        ec a, b, ans, ecd;
        int pp, p1;
        Fp nbai;
        Fp uhen, sahen;
        Fp work;

        Fp_set_str(&nbai, "1b0");
        Efp_set_A();
        Fp_set_p();
        Fp_set_one();
        Fp_set_Rsq();
        //Fp_set_r();
        Fp_set_str(&a.x, Px);
        Fp_set_str(&a.y, Py);

        Fp_set_str(&b.x, Px);
        Fp_set_str(&b.y, Py);
 
        //Fp_add(&nbai, Rsq, &ichi);
        printf("A: X Y\n");
        Efp_PrintEC(&a);
        printf("a:");
        Fp_print(&A);

        Fp_to_Mont(&b.x, &b.x);
        Fp_to_Mont(&b.y, &b.y);
        Fp_to_Mont(&A, &A);
        // printf("a(mont):");
        // Fp_print(&at);
        Efp_mgecD(&ecd, &b, &A);
        Fp_from_Mont(&b.x);
        Fp_from_Mont(&b.y);
        Fp_from_Mont(&A);

        printf("ecd:");
        Fp_from_Mont(&ecd.x);
        Fp_from_Mont(&ecd.y);
        Efp_PrintEC(&ecd);

        // bunshi: 0x1b
        // bumbo: 0x90 
        // bunshi2: 0x5
        // bumbo2: 0x12
        // U.x: 0x51
        // U.y: 0x6d

        ec c, eca;
        Fp_set_str(&c.x, "51");
        Fp_set_str(&c.y, "6d");

        Fp_to_Mont(&b.x, &b.x);
        Fp_to_Mont(&b.y, &b.y);
        Fp_to_Mont(&c.x, &c.x);
        Fp_to_Mont(&c.y, &c.y);
        Fp_to_Mont(&A, &A);
        Efp_mgecA(&eca, &b, &c, &A);
        Fp_from_Mont(&b.x);
        Fp_from_Mont(&b.y);
        Fp_from_Mont(&A);
        Fp_from_Mont(&c.x);
        Fp_from_Mont(&c.y);

        printf("eca:");
        Fp_from_Mont(&eca.x);
        Fp_from_Mont(&eca.y);
        Efp_PrintEC(&eca);
        // rx: 0x131
        // ry: 0x123

        Fp_to_Mont(&a.x, &a.x);
        Fp_to_Mont(&a.y, &a.y);
        Fp_to_Mont(&A, &A);
        Efp_mgecSCM(&ans, &a, &nbai, &A);
        Fp_from_Mont(&a.x);
        Fp_from_Mont(&a.y);
        Fp_from_Mont(&A);

        ec ect;
        Fp_to_Mont(&a.x, &a.x);
        Fp_to_Mont(&a.y, &a.y);
        Fp_to_Mont(&A, &A);
        Efp_mgecT(&ect, &a, &A);
        Fp_from_Mont(&a.x);
        Fp_from_Mont(&a.y);
        Fp_from_Mont(&A);

        printf("ect:");
        Fp_from_Mont(&ect.x);
        Fp_from_Mont(&ect.y);
        Efp_PrintEC(&ect);
        
        printf("inf:%d\n",ans.inf);
        if(ans.inf == 1){
            printf("ans = inf\n");
        }else{
            Efp_PrintEC(&ans);
        }

        return 0;
}