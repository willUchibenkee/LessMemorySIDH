//isogenytest.c   このプログラムの名前

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gmp.h>
#include"isogeny.h"

#define Paxx0 "00003CCFC5E1F050030363E6920A0F7A4C6C71E63DE63A0E6475AF621995705F7C84500CB2BB61E950E19EAB8661D25C4A50ED279646CB48"
#define Paxx1 "0001AD1C1CAE7840EDDA6D8A924520F60E573D3B9DFAC6D189941CB22326D284A8816CC4249410FE80D68047D823C97D705246F869E3EA50"
#define Payx0 "0001AB066B84949582E3F66688452B9255E72A017C45B148D719D9A63CDB7BE6F48C812E33B68161D5AB3A0A36906F04A6A6957E6F4FB2E0"
#define Payx1 "0000FD87F67EA576CE97FF65BF9F4F7688C4C752DCE9F8BD2B36AD66E04249AAF8337C01E6E4E1A844267BA1A1887B433729E1DD90C7DD2F"

48CB469627ED504A5CD26186AB9EE150E961BBB20C50847C5F70951962AF75640E3AE63DE6716C4C7A0F0A92E663030350F0E1C5CF3C0050EAE369F84652707DC923D84780D680FE109424C46C81A884D22623B21C9489D1C6FA9D3B3D570EF62045928A6DDAED4078AE1C1CAD0100000A00000000000000290000003A000000100000000000000041000000400000000200000000000000000000000000000000000000000000007C000000770000006E0000005D0000003F00000000000000801B1484A57F00003F000000000000000004000000000000B0FFFFFF

#define Qaxx0 "0000C7461738340EFCF09CE388F666EB38F7F3AFD42DC0B664D9F461F31AA2EDC6B4AB71BD42F4D7C058E13F64B237EF7DDD2ABC0DEB0C6C"
#define Qaxx1 "000025DE37157F50D75D320DD0682AB4A67E471586FBC2D31AA32E6957FA2B2614C4CD40A1E27283EAAF4272AE517847197432E2D61C85F5"
#define Qayx0 "0001D407B70B01E4AEE172EDF491F4EF32144F03F5E054CEF9FDE5A35EFA3642A11817905ED0D4F193F31124264924A5F64EFE14B6EC97E5"
#define Qayx1 "0000E7DEC8C32F50A4E735A839DCDB89FE0763A184C525F7B7D0EBC0E84E9D83E9AC53A572A25D19E1464B509D97272AE761657B4765B3D6"

#define Pbxx0 "00008664865EA7D816F03B31E223C26D406A2C6CD0C3D667466056AAE85895EC37368BFC009DFAFCB3D97E639F65E9E45F46573B0637B7A9"
#define Pbxx1 "00000000"
#define Pbyx0 "00006AE515593E73976091978DFBD70BDA0DD6BCAEEBFDD4FB1E748DDD9ED3FDCF679726C67A3B2CC12B39805B32B612E058A4280764443B"
#define Pbyx1 "00000000"

#define Qbxx0 "00012E84D7652558E694BF84C1FBDAAF99B83B4266C32EC65B10457BCAF94C63EB063681E8B1E7398C0B241C19B9665FDB9E1406DA3D3846"
#define Qbxx1 "00000000"
#define Qbyx0 "00000000"
#define Qbyx1 "0000EBAAA6C731271673BEECE467FD5ED9CC29AB564BDED7BDEAA86DD1E0FDDF399EDCC9B49C829EF53C7D7A35C3A0745D73C424FB4A5FD2"

int main(void){
    //define
    printf("define\n");

    mpz_init(prime_z);
    mpz_set_str(prime_z, pval, 16);

    ec2 Pa, Qa, Ra, Sa;
    ec2 *Pap; ec2 *Qap; ec2 *Rap; ec2 *Sap;
    Pap = &Pa; Qap = &Qa; Rap = &Ra; Sap = &Sa;

    fp2_init(&Pap->x); fp2_init(&Pap->y); mpz_init(Pap->inf);
    fp2_init(&Qap->x); fp2_init(&Qap->y); mpz_init(Qap->inf);
    fp2_init(&Rap->x); fp2_init(&Rap->y); mpz_init(Rap->inf);
    fp2_init(&Sap->x); fp2_init(&Sap->y); mpz_init(Sap->inf);

    ec2 Pb, Qb, Rb, Sb;
    ec2 *Pbp; ec2 *Qbp; ec2 *Rbp; ec2 *Sbp;
    Pbp = &Pb; Qbp = &Qb; Rbp = &Rb; Sbp = &Sb;

    fp2_init(&Pbp->x); fp2_init(&Pbp->y); mpz_init(Pbp->inf);
    fp2_init(&Qbp->x); fp2_init(&Qbp->y); mpz_init(Qbp->inf);
    fp2_init(&Rbp->x); fp2_init(&Rbp->y); mpz_init(Rbp->inf);
    fp2_init(&Sbp->x); fp2_init(&Sbp->y); mpz_init(Sbp->inf);

    fp2_set_str(&Pap->x, Paxx0, Paxx1);
    fp2_set_str(&Pap->y, Payx0, Payx1);
    fp2_set_str(&Qap->x, Qaxx0, Qaxx1);
    fp2_set_str(&Qap->y, Qayx0, Qayx1);

    fp2_set_str(&Pbp->x, Pbxx0, Pbxx1);
    fp2_set_str(&Pbp->y, Pbyx0, Pbyx1);
    fp2_set_str(&Qbp->x, Qbxx0, Qbxx1);
    fp2_set_str(&Qbp->y, Qbyx0, Qbyx1);

    ec2 ecneg;
    ec2_init(&ecneg);

    mpz_t kam, kbm;
    mpz_init(kam);
    mpz_init(kbm);
    mpz_set_str(kam, ka, 16);
    mpz_set_str(kbm, kb, 16);

    mpz_t lat, lbt;
    mpz_init(lat); 
    mpz_init(lbt);
    mpz_set_ui(lat, la);
    mpz_set_ui(lbt, lb);

    mpz_t py, eat, one;
    mpz_init(py);
    mpz_init(eat);
    mpz_init(one);

    mpz_set_ui(one, 1);
    //py=la**(eA-1)
    mpz_set_str(eat, eA, 16);
    fp_sub(eat, eat, one);
    fp_scalarexp(py, lat, eat);

    mpz_t q;
    mpz_init(q);
    int i = 0;

    
    //gmp_printf("la = %Zd\n", lat);

    fp2 at, aap; fp2 *ap;
    ap = &at;
    fp2_init(ap);
    fp2_set_ui(ap, a0x0, a0x1);
    fp2 ai; fp2 *aip;
    aip = &ai;
    fp2_init(aip);
    fp2_init(&aap);
    //fp2_printf(ap);

    fp2 alpha; fp2 *alphap;
    alphap = &alpha;
 

    fp2 ja, jb;

    fp2_init(&ja);
    fp2_init(&jb);

    printf("get S\n");

    //test(alice)
    isogeny_gets(Sap, Pap, Qap, kam, ap);
    printf("Sa:");
    PrintEC2(Sap);
    isogeny_gets(Sbp, Pbp, Qbp, kbm, ap);
    printf("Sb:");
    PrintEC2(Sbp);

    printf("alice gen\n");

    while(mpz_cmp_ui(py, 0) != 0){

        fp2_mgecSCM(Rap, Sap, py, ap);



        isogeny_changea(aip, &Rap->x);
        // printf("newa:");
        // fp2_printf(aip);

        isogeny_nextp(Pbp, Pbp, &Rap->x, lat);
        isogeny_nextp(Qbp, Qbp, &Rap->x, lat);
        isogeny_nextp(Sap, Sap, &Rap->x, lat);

        if(mpz_cmp_ui(py, 1) == 0){
            isogeny_gety(&Pbp->y, &Pbp->x, aip);
            //printf("a\n");
            isogeny_gety(&Qbp->y, &Qbp->x, aip);

            isogeny_gety(&Sap->y, &Sap->x, aip);
        }

        fp2_set(ap, aip);
        
        mpz_set_ui(py, mpz_get_ui(py)/la);
        //gmp_printf("py = %Zd\n", py);
        //getchar();
    }

    fp2_set(&aap, ap);

    fp2_neg(&ecneg.y, &Pbp->y);

    // fp2_printf(&Pbp->y);
    // fp2_printf(&ecneg.y);

    if(fp2_cmp_n(&Pbp->y, &ecneg.y) == -1){
        // fp2_printf(&Pbp->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Pbp->y, &ecneg.y);
    }

    fp2_neg(&ecneg.y, &Qbp->y);

    if(fp2_cmp_n(&Qbp->y, &ecneg.y) == -1){
        // fp2_printf(&Qbp->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Qbp->y, &ecneg.y);
    }

    printf("PKa:");
    fp2_printf(&aap);
    printf("Pb:");
    PrintEC2(Pbp);
    printf("Qb:");
    PrintEC2(Qbp);

    printf("//////////////////////////////////////\n");

    //test(bob)
    //py=lb**(eb-1)
    mpz_t ebt;
    mpz_init(ebt);
    mpz_set_str(ebt, eB, 16);
    fp_sub(ebt, ebt, one);
    //mpz_set_ui(py, (int)(pow((double)lb, (double)eB))/lb);
    fp_scalarexp(py, lbt, ebt);
    //gmp_printf("py = %Zd\n", py);

    fp2_set_ui(ap, a0x0, a0x1);
    
    //fp2_printf(ap);
    while(mpz_cmp_ui(py, 0) != 0){

        fp2_set(&Rbp->x, &Sbp->x);
        fp2_set(&Rbp->y, &Sbp->y);
        mpz_set(q,py);
        i = 0;
        while(mpz_cmp_ui(q, 1) != 0){

            mpz_tdiv_q_ui(q, q, 3);
            i++;
        }
        for(int j = 0; j < i; j++){

            isogeny_mgec3(Rbp, Rbp, ap);

        }

        isogeny_changeb(aip, &Rbp->x, ap);

        // printf("newb:");
        // fp2_printf(aip);

        isogeny_nextp(Pap, Pap, &Rbp->x, lbt);
        isogeny_nextp(Qap, Qap, &Rbp->x, lbt);
        isogeny_nextp(Sbp, Sbp, &Rbp->x, lbt);
        fp2_set(ap, aip);

        //fp2_printf(ap);
        mpz_set_ui(py, mpz_get_ui(py)/lb);
        
        //getchar();
    }

    isogeny_gety(&Pap->y, &Pap->x, ap);
    isogeny_gety(&Qap->y, &Qap->x, ap);
    isogeny_gety(&Sbp->y, &Sbp->x, ap);

    fp2_neg(&ecneg.y, &Pap->y);

    if(fp2_cmp_n(&Pap->y, &ecneg.y) == -1){
        // fp2_printf(&Pap->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Pap->y, &ecneg.y);
    }

    fp2_neg(&ecneg.y, &Qap->y);

    if(fp2_cmp_n(&Qap->y, &ecneg.y) == -1){
        // fp2_printf(&Qap->y);
        // fp2_printf(&ecneg.y);

        fp2_set(&Qap->y, &ecneg.y);
    }

    printf("PKb:");
    fp2_printf(ap);
    printf("Pa:");
    PrintEC2(Pap);
    printf("Qa:");
    PrintEC2(Qap);

    //鍵共有
    printf("ここから鍵共有です\n");

    //alice
    printf("aliceの操作\n");
    //isogeny_gets(Sap, Pap, Qap, kam, ap);
    isogeny_gets(Sap, Pap, Qap, kam, ap);

    //mpz_set_ui(py, (int)(pow((double)la, (double)eA))/2);
    fp_scalarexp(py, lat, eat);

    while(mpz_cmp_ui(py, 0) != 0){
        fp2_mgecSCM(Rap, Sap, py, ap);
        //fp2_printf(&Rap->x);

        isogeny_changea(aip, &Rap->x);
        //fp2_printf(aip);

        isogeny_nextp(Sap, Sap, &Rap->x, lat);
        fp2_set(ap, aip);
        
        mpz_set_ui(py, mpz_get_ui(py)/la);
        //gmp_printf("py = %Zd\n", py);
        //getchar();
    }

    isogeny_getj(&ja, ap);

    //bob
    printf("bobの操作\n");

    isogeny_gets(Sbp, Pbp, Qbp, kbm, &aap);

    //mpz_set_ui(py, (int)(pow((double)lb, (double)eB))/lb);
    fp_scalarexp(py, lbt, ebt);

    while(mpz_cmp_ui(py, 0) != 0){
        
        //fp2_mgecSCM(Rbp, Sbp, py, ap);
        //PrintEC2(Sbp);
        //fp2_printf(ap);
        fp2_set(&Rbp->x, &Sbp->x);
        mpz_set(q,py);
        i = 0;
        while(mpz_cmp_ui(q, 1) != 0){
            mpz_tdiv_q_ui(q, q, 3);
            i++;
        }
        for(int j = 0; j < i; j++){
            isogeny_mgec3(Rbp, Rbp, &aap);
            //printf("a\n");
        }

        isogeny_changeb(aip, &Rbp->x, &aap);
        //fp2_printf(aip);

        isogeny_nextp(Sbp, Sbp, &Rbp->x, lbt);
        fp2_set(&aap, aip);

        //fp2_printf(&aap);
        mpz_set_ui(py, mpz_get_ui(py)/lb);
        
        //getchar();
    }

    isogeny_getj(&jb, &aap);

    // printf("jval:");
    // fp2_printf(&jb);

    if(fp2_cmp(&ja, &jb) == 0){
        printf("ja == jb\n");
        fp2_printf(&ja);
    }else{
        printf("ja =! jb\n");
        fp2_printf(&ja);
        fp2_printf(&jb);
    }

    return 0;
}