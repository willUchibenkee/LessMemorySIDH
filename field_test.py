#field_test.py
import fp
import fp2
import random
import configparser

config = configparser.ConfigParser()

config.read("define.ini")

prime_z = config["BASE"]["p"]
prime_min = config["BASE"]["pminus"]

print('fpのテスト')

for count in range(int(prime_z)):

    #乱数生成
    A = random.randint(0, int(prime_min))
    B = random.randint(0, int(prime_min))

    print('A:%d' % A)
    print('B:%d' % B)

    #各関数の確認
    ADD = fp.fp_add(A, B)
    SUB = fp.fp_sub(A, B)
    MUL = fp.fp_mul(A, B)
    INV = fp.fp_inv(B)

    print('ADD:%d' % ADD)
    print('SUB:%d' % SUB)
    print('MUL:%d' % MUL)
    print('INV:%d' % INV)
    
    #INVの詳細な確認
    if fp.fp_mul(INV, B) == 1:
        print('OK.')
    else:
        print(fp.fp_mul(INV, B))
        input()
        

    #AとBが変わってないことの確認
    print('A:%d' % A)
    print('B:%d' % B)
    
    print('=============')
    
print('fp2のテスト')

for i in range(int(prime_z)):
    
    #乱数生成
    C = [random.randint(0, int(prime_min)), random.randint(0, int(prime_min))]
    D = [random.randint(0, int(prime_min)), random.randint(0, int(prime_min))]
    
    print('C:%d + %di' % (C[0], C[1]))
    print('D:%d + %di' % (D[0], D[1]))

    #各関数の確認
    ADD2 = fp2.fp2_add(C, D)
    SUB2 = fp2.fp2_sub(C, D)
    MUL2 = fp2.fp2_mul(C, D)
    INV2 = fp2.fp2_inv(C)

    print('ADD2:%d + %di' % (ADD2[0], ADD2[1]))
    print('SUB2:%d + %di' % (SUB2[0], SUB2[1]))
    print('MUL2:%d + %di' % (MUL2[0], MUL2[1]))
    print('INV2:%d + %di' % (INV2[0], INV2[1]))
    
    #INVの詳細な確認
    if fp2.fp2_mul(INV2, C) == [1, 0]:
        print('OK.')
    else:
        print(fp2.fp2_mul(INV2, C))
        input()
        

    #AとBが変わってないことの確認
    print('C:%d + %di' % (C[0], C[1]))
    print('D:%d + %di' % (D[0], D[1]))
    
    print('=============')
    