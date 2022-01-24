//isogenytest.c   このプログラムの名前

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gmp.h>
#include"Isogeny.c"

#define Pax "00003CCFC5E1F050030363E6920A0F7A4C6C71E63DE63A0E6475AF621995705F7C84500CB2BB61E950E19EAB8661D25C4A50ED279646CB48 0001AD1C1CAE7840EDDA6D8A924520F60E573D3B9DFAC6D189941CB22326D284A8816CC4249410FE80D68047D823C97D705246F869E3EA50"
#define Pay "0001AB066B84949582E3F66688452B9255E72A017C45B148D719D9A63CDB7BE6F48C812E33B68161D5AB3A0A36906F04A6A6957E6F4FB2E0 0000FD87F67EA576CE97FF65BF9F4F7688C4C752DCE9F8BD2B36AD66E04249AAF8337C01E6E4E1A844267BA1A1887B433729E1DD90C7DD2F"

#define Qax "0000C7461738340EFCF09CE388F666EB38F7F3AFD42DC0B664D9F461F31AA2EDC6B4AB71BD42F4D7C058E13F64B237EF7DDD2ABC0DEB0C6C 000025DE37157F50D75D320DD0682AB4A67E471586FBC2D31AA32E6957FA2B2614C4CD40A1E27283EAAF4272AE517847197432E2D61C85F5"
#define Qay "0001D407B70B01E4AEE172EDF491F4EF32144F03F5E054CEF9FDE5A35EFA3642A11817905ED0D4F193F31124264924A5F64EFE14B6EC97E5 0000E7DEC8C32F50A4E735A839DCDB89FE0763A184C525F7B7D0EBC0E84E9D83E9AC53A572A25D19E1464B509D97272AE761657B4765B3D6"

#define Pbx "00008664865EA7D816F03B31E223C26D406A2C6CD0C3D667466056AAE85895EC37368BFC009DFAFCB3D97E639F65E9E45F46573B0637B7A9 00000000"
#define Pby "00006AE515593E73976091978DFBD70BDA0DD6BCAEEBFDD4FB1E748DDD9ED3FDCF679726C67A3B2CC12B39805B32B612E058A4280764443B 00000000"

#define Qbx "00012E84D7652558E694BF84C1FBDAAF99B83B4266C32EC65B10457BCAF94C63EB063681E8B1E7398C0B241C19B9665FDB9E1406DA3D3846 00000000"
#define Qby "00000000 0000EBAAA6C731271673BEECE467FD5ED9CC29AB564BDED7BDEAA86DD1E0FDDF399EDCC9B49C829EF53C7D7A35C3A0745D73C424FB4A5FD2"

int main(void){
    //define
    ec2 Pa, Qa, Ra, Sa;

    ec2 Pb, Qb, Rb, Sb;
    
    Fp2_set_str(&Pa.x, Pax);
    Fp2_set_str(&Pa.y, Pay);

    Fp2_set_str(&Pb.x, Pbx);
    Fp2_set_str(&Pb.y, Pby);

    Fp2_set_str(&Qa.x, Qax);
    Fp2_set_str(&Qa.x, Qay);

    Fp2_set_str(&Qb.x, Qbx);
    Fp2_set_str(&Qb.x, Qby);

    int kam, kbm;
    kam = ka;
    kbm = kb;

    int lat, lbt;
    lat = la;
    lbt = lb;

    isogeny_set_e();
    int py;
    ea = ea / lat;
    py =  (int)pow((double)lat, (double)ea);

    int q;
    int i = 0;

    Isogeny_set_a0();
    Fp2 newa;

    Fp2 alpha;
    Fp_set_p();
    Fp_set_Rsq();
    Fp_set_one();

    //公開鍵生成
    printf("公開鍵生成\n");
    
    //AliceGen

    //test(alice)
    Isogeny_gets(&Sa, &Pa, &Qa, kam, &Aa0);
    Isogeny_gets(&Sb, &Pb, &Qb, kbm, &Ba0);

    while(py != 0){
        Efp2_mgecSCM(&Ra, &Sa, py, &Aa0);

        Isogeny_changea(&newa, &Ra.x);

        Isogeny_nextp(&Pb, &Pb, &Ra.x, lat);
        Isogeny_nextp(&Qb, &Qb, &Ra.x, lat);
        Isogeny_nextp(&Sa, &Sa, &Ra.x, lat);
        Fp2_set(&Aa0, &newa);
        
        py = py / lat;

    }

    //gmp_printf("PKA = (aA, PB, QB) = ((%Zd + %Zd i), (%Zd + %Zd i), (%Zd + %Zd i))\n", Aa0.x0, Aa0.x1, Pbp->x.x0, Pbp->x.x1, Qbp->x.x0, Qbp->x.x1);
    printf("PKA:aA:");
    Fp2_print(&Aa0);
    printf("Pb:");
    Fp2_print(&Pb);
    printf("Qb:");
    Fp2_print(&Qb);
    Fp2 aa;
    Fp2_set(&aa, &Aa0);

    printf("//////////////////////////////////////\n");

    BobGen

    //test(bob)
    //mpz_divexact(eb, eb, lbt);
    //mpz_pow_ui(py, lbt, mpz_get_ui(eb));
    //gmp_printf("py = %Zd\n", py);
    

    while(mpz_cmp_ui(py, 0) != 0){
        
        Fp2_set(&Rb.x, &Sb.x);
        q = py;
        i = 0;
        while(mpz_cmp_ui(q, 1) != 0){
            mpz_tdiv_q_ui(q, q, 3);
            i++;
        }
        for(int j = 0; j < i; j++){
            isogeny_mgec3(&Rb, &Rb, &Ba0);
            //printf("a\n");
        }


        isogeny_changeb(&newa, &Rb.x, &Ba0);
        //fp2_printf(aip);

        isogeny_nextp(&Pa, &Pa, &Rb.x, lbt);
        isogeny_nextp(&Qa, &Qa, &Rb.x, lbt);
        isogeny_nextp(&Sb, &Sb, &Rb.x, lbt);
        Fp2_set(&Ba0, &newa);
        

        //fp2_printf(ap);
        //mpz_divexact(py, py, lbt);

    }

    //gmp_printf("PKB = (aB, PA, QA) = ((%Zd + %Zd i), (%Zd + %Zd i), (%Zd + %Zd i))\n", ba0.x0, ba0.x1, Pap->x.x0, Pap->x.x1, Qap->x.x0, Qap->x.x1);
    printf("PKB:aB");
    Fp2_print(&Ba0);
    Fp2_print(&Pa);
    Fp2_print(&Qa);

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

    isogeny_set_e();
    
    //alice
    printf("aliceの操作\n");
    isogeny_gets(&Sa, &Pa, &Qa, kam, &Ba0);
    //mpz_divexact(ea, ea, lat);
    //mpz_pow_ui(py, lat, mpz_get_ui(ea));
    while(mpz_cmp_ui(py, 0) != 0){
        Fp2_mgecSCM(&Ra, &Sa, py, &Ba0);
        //fp2_printf(&Rap->x);

        isogeny_changea(&newa, &Ra.x);
        Fp2_printf(&newa);

        isogeny_nextp(&Sa, &Sa, &Ra.x, lat);
        Fp2_set(&Ba0, &newa);
        
        //mpz_divexact(py, py, lat);

    }

    //BobGet

    //bob
    printf("bobの操作\n");
    PrintEC2(Pbp);
    //PrintEC2(Qbp);
    Fp2_neg(&Qbp->y, &Qbp->y);
    PrintEC2(Qbp);
    isogeny_gets(&Sb, &Pb, &Qb, kbm, &aa);
    //mpz_divexact(eb, eb, lbt);
    //mpz_pow_ui(py, lbt, mpz_get_ui(eb));

    while(mpz_cmp_ui(py, 0) != 0){
        
        Fp2_set(&Rb.x, &Sb.x);
        q = py;
        i = 0;
        // while(mpz_cmp_ui(q, 1) != 0){
        //     //mpz_tdiv_q_ui(q, q, 3);
        //     i++;
        // }
        for(int j = 0; j < i; j++){
            isogeny_mgec3(&Rb, &Rb, &aa);
            //printf("a\n");
        }


        isogeny_changeb(aip, &Rb.x, aap);
        //fp2_printf(aip);

        isogeny_nextp(&Sb, &Sb, &Rb.x, lbt);
        Fp2_set(&aa, &newa);

        Fp2_print(&aa);
        //mpz_divexact(py, py, lbt);
        
    }

    return 0;
}