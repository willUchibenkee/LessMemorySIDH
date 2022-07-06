# isogeny.py
import define
import fp2

class efp2_t:
    def __init__(self, x, y, infinity):
        self.x = fp2.fp2_t(x0, x1)
        self.y = fp2.fp2_t(x0, x1)
        self.infinity = 0
    def info(self):
        print("_________________________")
        print(f'x0:{self.x0}')
        print(f'x1:{self.x1}')
# def print_fp(x: fp_t):
#     print("x0:{x.x0}")
    def __repr__(self):
        print(self.x0)
        print(self.x1)
    def __str__(self):
        return str(self.x0) + "_" + str(self.x1)

# aの更新
def isogeny_changea(oldb: fp2.fp2_t, alpha: fp2.fp2_t):
    one = fp2.fp2_t(1, 0)
    two = fp2.fp2_t(2, 0)

    tmp = fp2.fp2_t(0, 0)

    #//a = 2(1 - 2alpha^2)
    
    tmp = alpha * alpha

    print(f'alpha ** 2 =  {tmp}')
    
    tmp = tmp * two

    print(f'tmp =  {tmp}')
    
    tmp = one - tmp

    print(f'tmp = {tmp}')
    
    nexta = two * tmp

    #//b = oldb * alpha

    #// ここの処理の有無でA. Costello B. SIDHspec 楕円曲線式を切り替える

    nextb = oldb * alpha

    return nexta.mod(), nextb.mod()

# 2-isogeny
def isogeny_nextp(ans: efp2_t, P: efp2_t, alpha:fp2_t, l:int):
    # //同種写像Φを求めます
    # //P...点 alpha...スタート点 l...AliceですかBobですか
    U,V = efp2_t(P.x.x0,P.x.x1,P.y.x0,P.y.x1,0, efp2_t(0,0,0,0,0))

    #//U.infinity =  P->infinity

    temp, temp2, bumbo = fp2.fp2_t(0,0),fp2.fp2_t(0,0), fp2.fp2_t(0,0)

    if l == 2:
        # //alice       
        # //分子

        # //xφ2(P) =xP**2 * x2 − xP/ xP − x2

        temp = U.x * U.x
        temp = temp * alpha
        temp = temp - U.x

        #//fp2_printf("bunshi = ", &temp)

        #//分母
        bumbo = P.x - alpha

        #//fp2_printf("bumbo = ", &bumbo);

        bumbo = bumbo.inv()

        #//fp2_printf("inv bumbo = ", &bumbo)

        #//掛け算
        V.x = temp * bumbo

        #//set
        ans.x = V.x

        #//y 分子 xP**2* alpha − 2*xP*alpha**2 + alpha
        temp = U.x * U.x
        temp = temp * alpha
        temp = temp - U.x

        temp2 = U.x * U.x
        temp2 = temp2 * alpha
        temp2 = temp2 * alpha

        temp = temp - temp2

        temp = temp + alpha

        #//fp2_printf("bunshi =", &temp);

        #//分母　(xP − alpha)**2
        bumbo = U.x - alpha
        bumbo = bumbo * bumbo

        #//fp2_printf("bumbo =", &bumbo);

        bumbo = bumbo.inv()

        #//fp2_printf("inv bumbo =", &bumbo);

        temp = temp * bumbo
        V.y = temp * U.y

        # // c**2 = alpha からcを求めて掛ける
        # //(C), (D)の切り替え
        if fp2_legendre(alpha) == 1:
            fp2_sqrt(&temp, alpha)
            V.y = V.y * temp

        ans.y = V.y

    # # }else{
    # #     //bob

    # #     mpz_t three;
    # #     mpz_init(three);
    # #     mpz_set_ui(three, 3);

    # #     //printf("bob\n");

    # #     fp2_t one, temp3, temp4; 
    # #     fp2_init(&one);
    # #     fp2_set_ui(&one, 1);
    # #     fp2_init(&temp3);
    # #     fp2_init(&temp4);

    # #     //
    # #     fp2_mul(&temp, alpha, &U.x);
    # #     fp2_sub(&temp, &temp, &one);
    # #     fp2_mul(&temp, &temp, &temp);
    # #     fp2_mul(&temp, &temp, &U.x);
    # #     //fp2_printff(tempp);

    # #     //
    # #     fp2_sub(&bumbo, &P->x, alpha);
    # #     fp2_mul(&bumbo, &bumbo, &bumbo);
    # #     fp2_inv(&bumbo, &bumbo);
    # #     //fp2_printff(bumbop);

    # #     //
    # #     fp2_mul(&V.x, &temp, &bumbo);

    # #     //
    # #     fp2_set(&ans->x, &V.x);

    # #     //y 分子 (xP*a − 1)(xP**2*a − 3*xP*a**3 + xP + a)
    # #     // printf("alpha:");
    # #     // fp2_printf_s(alpha);
    # #     // printf("U:");
    # #     // Efp2_PrintEC2_s(&U);

    # #     fp2_mul(&temp, &U.x, alpha);
    # #     fp2_sub(&temp, &temp, &one);

    # #     //////////////////////////////////////

    # #     fp2_mul(&temp2, &U.x, alpha);
    # #     fp2_mul(&temp2, &temp2, &U.x);

    # #     fp2_mul(&temp3, &U.x, alpha);
    # #     fp2_mul(&temp3, &temp3, alpha);
    # #     fp2_mul(&temp3, &temp3, alpha);

    # #     fp2_add(&temp4, &temp3, &temp3);
    # #     fp2_add(&temp4, &temp4, &temp3);

    # #     fp2_sub(&temp2, &temp2, &temp4);

    # #     fp2_add(&temp2, &temp2, &U.x);

    # #     fp2_add(&temp2, &temp2, alpha);

    # #     ///////////////////////////////////////

    # #     fp2_mul(&temp, &temp, &temp2);

    # #     //分母 (xP − x3)3
    # #     fp2_sub(&temp3, &U.x, alpha);
    # #     fp2_mul(&bumbo, &temp3, &temp3);
    # #     fp2_mul(&bumbo, &bumbo, &temp3);

    # #     fp2_inv(&bumbo, &bumbo);

    # #     ///////////////////////////////////////

    # #     fp2_mul(&V.y, &temp, &bumbo);

    # #     fp2_mul(&V.y, &V.y, &U.y);

    # #     fp2_set(&ans->y, &V.y);
