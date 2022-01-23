// Fp2_test.c

#define TTT_INSTANCE_HERE
#include "Fp2.c"

#define ec_field(p)   (p->ec->field)
#define rep(x) (*((mpz_t *)x->data))
#define rep0(x) (((Element *)x->data)[0])
#define rep1(x) (((Element *)x->data)[1])
#define rep2(x) (((Element *)x->data)[2])

#define field(x) (x->field)
//#define ec_field(p)   (p->ec->field)
#define curve(p)   (p->ec)

#define TIMES 1,000,000

int main(void){

    Fp2 a, b, c, d, e, f;

    char *av = "342FEA1234276473547196471545164736736DACCCCFFFFFF726476736467367436726863BBBBBBBB762372637156747125475 45DFCA482558321FFFF222B1372562853CCCCCAAAAA726372554726846FFFFF8786767365932657236756435463546";
    char *bv = "8375836287896897823645215636276241453adacad4d3caea4ce3c121fd56fdef4357a3867d43daed653ad5e7 d6ae4dae45aecd65cda6e5436735893b3647bbbbbcdbc6dcb6dbc6cbd6b6dbe6bde76389";

    printf("Fp2 test starts.\n");
    Fp_set_one();
    Fp_set_Rsq();

    Fp_set_r();
    Fp_set_p();

    // Fp_print(one);
    // Fp_print(Rsq);

    Fp2 onefp2;
    Fp2_set_fp(&onefp2, one);

    Fp2_set_str(&a, av);
    Fp2_set_str(&b, bv);

    Fp2_add(&c, &a, &b);
    printf("A+B:0x");
    Fp2_print(&c);

    Fp2_sub(&d, &a, &b);
    printf("A-B:0x");
    Fp2_print(&d);

    Fp2_to_Mont(&a, &a);
    Fp2_to_Mont(&b, &b);
    Fp2_mul(&e, &a, &b);
    Fp2_from_Mont(&e);
    printf("AB:0x");
    Fp2_print(&e);

    Fp2_inv(&f, &a);
    Fp2_mul(&f, &f, &a);
    Fp2_from_Mont(&f);
    printf("A*(1/A):0x");
    Fp2_print(&f);

    printf("test complete.\n");

    return 0;

    /*
    A: 0x342fea1234276473547196471545164736736daccccffffff726476736467367436726863bbbbbbbb762372637156747125475 0x45dfca482558321ffff222b1372562853cccccaaaaa726372554726846fffff8786767365932657236756435463546
    B: 0x8375836287896897823645215636276241453adacad4d3caea4ce3c121fd56fdef4357a3867d43daed653ad5e7 0xd6ae4dae45aecd65cda6e5436735893b3647bbbbbcdbc6dcb6dbc6cbd6b6dbe6bde76389
    A+B: 0x342fea123427e7e8d7d41dd07ddc987d7b94c3e2f43241453201123c0a115db42728488392b9aaff0f05bda37af054ac4d2a5c 0x45dfca482558321ffff22387e57310caeb9a3278518c699e5addad9e8ebbbbb5542e43ed34f93148ed514af32d98cf
    A-B: 0x342fea123426e0fdd10f0ebdacad9410f1521776a56dbebabc4b7c92627b891a5fa60488e4bdcc785fbeb0a8f33a79e1d77e8e 0x45dfca482558321ffff221da88d7b43f8dff66dd03c1e2cfefcb3731ff44443b9ca08a7f7d6b999b7f997d775ed1bd
    AR: 0x1517319b123e675863d39defa841f943deb8296c0723e8af006f690f9d8f00408bbe7b8d3fbcb186395c1c7aa85cbeaa26c7708b38ca2 0x22ff3ab8a6fb4dd0e2de339502e8c9b20ea0d0549e4fa4e3b442e5cf709a5ed0ccf78856d34c684d62e7b256114735b271bd676c2524
    BR: 0x16d93712df9d85d30e3b0824f909aa00a4683998131afa2522af7904b6b7b842e1f3e0c32567067821781ec0bd3851a6867747cda5ad2 0x22d3de05e8a8dd65974a2210409fb6dfdb6bfbb794f1f195ba7e37e27b511172029d3afbea11442577e92ab6d7845abfc9b609f97659e
    ABR: 0x125c7b58a20de1e258b2b0b2815457837c585ce71e5f673704d797950bec6c367702787f5daa3314b32f088af6c8c48800701d4b2247f 0x119f2d03fa00129b8b6fc3fe9635aaf1c53ee64d5df13e6f3f15c244686d934df1094467d5ebaa7434fdde016bb47d961426cb38cd0cd
    AB: 0x1ec82041cfd487145e200ffdb6728de35c4477d70c9c705abe6149be42433a63e9788ef20ef610966921b6b553fdb1d283ec9f50d0d3c 0x1623a0c2b1798806c6eb954cac848da72dbad35bcee84e6d085830e3248382a0454e5d4cd81df06caca937edc03fcfc42c74c4e3c50e0
    */
    /*
    A+B:0x342fea123427e7e8d7d41dd07ddc987d7b94c3e2f43241453201123c0a115db42728488392b9aaff0f05bda37af054ac4d2a5c 45dfca482558321ffff22387e57310caeb9a3278518c699e5addad9e8ebbbbb5542e43ed34f93148ed514af32d98cf
    A-B:0x342fea123426e0fdd10f0ebdacad9410f1521776a56dbebabc4b7c92627b891a5fa60488e4bdcc785fbeb0a8f33a79e1d77e8e 45dfca482558321ffff221da88d7b43f8dff66dd03c1e2cfefcb3731ff44443b9ca08a7f7d6b999b7f997d775ed1bd
    AB:0x1ec82041cfd487145e200ffdb6728de35c4477d70c9c705abe6149be42433a63e9788ef20ef610966921b6b553fdb1d283ec9f50d0d3c 1623a0c2b1798806c6eb954cac848da72dbad35bcee84e6d085830e3248382a0454e5d4cd81df06caca937edc03fcfc42c74c4e3c50e0
    A*(1/A):0x1 0
    */
}