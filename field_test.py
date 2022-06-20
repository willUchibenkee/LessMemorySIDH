# field_test.py
import define
import fp
import fp2

#fpのテストです
# a = fp.fp_t(56)
# b = fp.fp_t(281)
# ans = fp.fp_t(0)

# #add 337になるはず
# print(f'a + b = {a + b}')

# #sub 206のはず
# print(f'a - b = {a - b}')

# #フェルマーの小定理 A*(A/1) = 1
# ans.inv(a)
# print("フェルマーの小定理の確認")
# ans = fp.mul(a, ans)
# fp.print_fp(ans)

#fp2のテストです
a, bi = 56, 67
c, di = 281, 38

ans, ansi = fp2.fp2_add(a, bi, c, di)

#add 337になるはず
print(f'c + d = {ans} + {ansi}i')

ans, ansi = fp2.fp2_sub(a, bi, c, di)

#sub 206のはず
print(f'c - d = {ans} + {ansi}i')

#フェルマーの小定理 A*(A/1) = 1
fp2.fp2_print(c, di)
tmp, tmpi = fp2.fp2_inv(c, di)
print("フェルマーの小定理の確認")
ans, ansi = fp2.fp2_mul(c, di, tmp, tmpi)
fp2.fp2_print(ans, ansi)