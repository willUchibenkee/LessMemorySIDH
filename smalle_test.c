//smalle_test.c

#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include"small_Efp2.c"

#define Px "64 f8"
//Pax0 00003CCFC5E1F050030363E6920A0F7A4C6C71E63DE63A0E6475AF621995705F7C84500CB2BB61E950E19EAB8661D25C4A50ED279646CB48
//Pax1 0001AD1C1CAE7840EDDA6D8A924520F60E573D3B9DFAC6D189941CB22326D284A8816CC4249410FE80D68047D823C97D705246F869E3EA50
#define Py "130 c7"
//Pay0 0001AB066B84949582E3F66688452B9255E72A017C45B148D719D9A63CDB7BE6F48C812E33B68161D5AB3A0A36906F04A6A6957E6F4FB2E0
//Pay1 0000FD87F67EA576CE97FF65BF9F4F7688C4C752DCE9F8BD2B36AD66E04249AAF8337C01E6E4E1A844267BA1A1887B433729E1DD90C7DD2F
//0x64
//0xf8
//0x130
//0xc7

int main(void){
    //定義とかもろもろ
        ec2 a, b, ans, ecd;
        int pp, p1;
        Fp nbai;
        Fp2 uhen, sahen;
        Fp2 at, bt, work;

        Fp_set_str(&nbai, "1b0");
        Efp2_set_A();
        Fp_set_p();
        Fp_set_one();
        Fp_set_Rsq();
        Fp_set_r();
        Fp2_set_str(&a.x, Px);
        Fp2_set_str(&a.y, Py);

        Fp2_set_str(&b.x, Px);
        Fp2_set_str(&b.y, Py);
 
        //Fp_add(&nbai, Rsq, &ichi);
        printf("A: X Y\n");
        PrintEC2(&a);

        Fp2_to_Mont(&b.x, &b.x);
        Fp2_to_Mont(&b.y, &b.y);
        Fp2_to_Mont(&at, &at);
        Efp2_mgecD(&ecd, &b, &at);
        Fp2_from_Mont(&b.x);
        Fp2_from_Mont(&b.y);
        Fp2_from_Mont(&at);

        PrintEC2(&ecd);
        //printf("p**2+1:\n");
        //Fp_print(&nbai);
        // if(Efp2_checkans(&a,&at) == 0){
        //     printf("rp ok\n");
        // }else{
        //     printf("rp ng\n");
        // }

        Fp2_to_Mont(&a.x, &a.x);
        Fp2_to_Mont(&a.y, &a.y);
        Fp2_to_Mont(&at, &at);
        Efp2_mgecSCM(&ans, &a, &nbai, &at);
        Fp2_from_Mont(&a.x);
        Fp2_from_Mont(&a.y);
        Fp2_from_Mont(&at);
        
        //printf("inf:%d\n",ans.inf);
        if(ans.inf == 1){
            printf("ans = inf\n");
        }else{
            PrintEC2(&ans);
        }

        return 0;
}