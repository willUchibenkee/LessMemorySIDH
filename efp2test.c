//efp2test.c(Montgomery)

#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include"efp2.h"

#define Px "0000C7461738340EFCF09CE388F666EB38F7F3AFD42DC0B664D9F461F31AA2EDC6B4AB71BD42F4D7C058E13F64B237EF7DDD2ABC0DEB0C6C 000025DE37157F50D75D320DD0682AB4A67E471586FBC2D31AA32E6957FA2B2614C4CD40A1E27283EAAF4272AE517847197432E2D61C85F5"
#define Py "0001D407B70B01E4AEE172EDF491F4EF32144F03F5E054CEF9FDE5A35EFA3642A11817905ED0D4F193F31124264924A5F64EFE14B6EC97E5 0000E7DEC8C32F50A4E735A839DCDB89FE0763A184C525F7B7D0EBC0E84E9D83E9AC53A572A25D19E1464B509D97272AE761657B4765B3D6"

int main(void){
    //定義とかもろもろ
        ec2 a, ans;
        int pp, p1;
        Fp nbai;
        Fp2 uhen, sahen;
        Fp2 work;
        Efp2_set_A();
        Fp2_set_str(&a.x, Px);
        Fp2_set_str(&a.y, Py);
 
        Fp_add(&nbai, p, one);
        PrintEC2(&a);
        if(Efp2_checkans(&a,&A) == 0){
            printf("rp ok\n");
        }else{
            printf("rp ng\n");
        }

        Efp2_mgecSCM(&ans, &a, &nbai, &A);
        
        if(ans.inf == 1){
            printf("ans = inf\n");
        }else{
            PrintEC2(&ans);
        }

        return 0;
}