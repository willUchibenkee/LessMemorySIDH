r=0x100000000
p=0x1af

px=0x12
py=0x6

a=0x6

# # print(hex(100))
# # print(hex(248))
# # print(hex(304))
# # print(hex(199))

# # print(hex(p+1))

# # one=r%p
# # two=2*r%p
# # three=3*r%p
# four=4*r%p
# # six = 6 * r %p
# # nihachi=28*r%p
# # print("one",hex(one))
# # print("two",hex(two))
# # print("three",hex(three))
# # print("four",hex(four))
# # print("six:", hex(six))
# # print("nihachi:", hex(nihachi))

# # print("432=", bin(432))

# # x4=px**4%p
# # ax4=a*px*4%p

# # work=(x4-ax4)%p

# # print("x4:", hex(x4))
# # print("4ax:", hex(ax4))
# # print("x4-4ax:", hex(work))
# x8=px**8%p
# x7=4*a*(px**7)%p

# tasu=(x8+x7)%p

# x6= (28 * (px**6))%p

# #(x**8 + 4Ax**7 + 28x**6 + 28Ax**5 + (16A**2 + 6)x**4 + 28Ax**3 + 28x**2 + 4Ax + 1)
# x5=(28*a*(px**5))%p
# x4=((16*a*a + 6)*(px**4))%p
# x3=28*a*(px**3)%p
# #print("ax**7:",hex(x7a))
# print("tasu:",hex(tasu))

# print("x5:", hex(x5))
# print("x4:", hex(x4))
# print("x3:", hex(x3))

# # x41=16*a%p
# # x42=x41*a%p
# # x43=(x42+6)%p
# # x44=x43*px%p
# # print("1:", hex(x41))
# # print("2:", hex(x42))
# # print("3:", hex(x43))
# # print("4:", hex(x44))
# x2= 28*(px**2)%p
# x = 4*a*px%p

# print("x2:", hex(x2))
# print("x1:", hex(x))

# w=16*r%p
# print("hex:", hex(w))

# tasu = (tasu +x6)%p
# print("tasu2:",hex(tasu))
# tasu = (tasu +x5)%p
# print("tasu3:",hex(tasu))
# tasu = (tasu +x4)%p
# print("tasu4:",hex(tasu))
# tasu = (tasu +x3)%p
# print("tasu5:",hex(tasu))
# tasu = (tasu +x2)%p
# print("tasu6:",hex(tasu))
# tasu = (tasu +x)%p
# print("tasu7:",hex(tasu))
x3 = (4*a*(px**3) )%p
x4 = (3*(px**4))%p
x2 = (6*(px**2))%p
katamari = (x3+x4+x2-1)%p
ans=katamari**3%p

print("x3:", hex(x3))
print("x4:", hex(x4))
print("x2:", hex(x2))
print("katamari:", hex(katamari))
print("ans:", hex(ans))