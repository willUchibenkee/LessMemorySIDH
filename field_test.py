# field_test.py
import define
import fp
import fp2

#fpのテストです
afp = fp.fp_t(56)
bfp = fp.fp_t(281)
ansfp = fp.fp_t(0)
#add 337になるはず
print(f'a + b = {afp + bfp}')
#sub 206のはず
print(f'a - b = {afp - bfp}')
#フェルマーの小定理 A*(A/1) = 1
inv = afp.inv()
print("フェルマーの小定理の確認")
ansfp = afp*inv
print(ansfp)
#fp2のテストです

#fp2のテストです
c = fp2.fp2_t(56,334)
d = fp2.fp2_t(281,27)
ans2 = fp2.fp2_t(0,0)
#add 337になるはず
print(f'c + d = {c + d}')
#sub 206のはず
print(f'c - d = {c - d}')
#フェルマーの小定理 A*(A/1) = 1
inv2 = c.inv()
print("フェルマーの小定理の確認")
ans2 = c*inv2
print(ans2)