# field_test.py
import define
import fp

#fpのテストです
a = fp.fp_t(56)
b = fp.fp_t(281)
ans = fp.fp_t(0)

#add 337になるはず
print(f'a + b = {a + b}')

#sub 206のはず
print(f'a - b = {a - b}')

#フェルマーの小定理 A*(A/1) = 1
ans.inv(a)
print("フェルマーの小定理の確認")
ans = fp.mul(a, tmp)
fp.print_fp(ans)

#fp2のテストです