r=0x100000000
p=0x1af

xp0=0xf8
xp1=0x64
yp0=0xc7
yp1=0x130

three0=0x4
three1=0x0  
one0=0x91
one1=0x0

#U:x:f8 64
#y:c7 130

a0=0x25
a1=0x17

# #//y 分子 (xP*a − 1)(xP**2*a − 3*xP*a**3 + xP + a)


# zenhan0=((xp0*a0 - xp1*a1)- 1)%p
# zenhan1=(xp0*a1 + xp1*a0)%p

# print("zenhan:", hex(zenhan0), hex(zenhan1))

# kouhan0=(xp0*xp0 - xp1*xp1)%p
# kouhan1=2*xp0*xp1%p
# temp0=(kouhan0*a0 - kouhan1*a1)%p
# temp1=(kouhan0*a1+kouhan1*a0)%p

# #//分母 (xP − x3)3

print("256は16進数で",hex(256))

le=(int)((p*p-1)/2)

print("(p*p-1)/2",hex(le))

#423i + 179,(142i + 183, 119i + 360),(220i + 314, 289i + 10
aa0=179
aa1=423

pbx0=183
pbx1=142
pby0=360
pby1=119

qbx0=314
qbx1=220
qby0=10
qby1=289

print("Ea:", hex(aa0), hex(aa1))
print("Pb:", hex(pbx0), hex(pbx1))
print(hex(pby0), hex(pby1))
print("Qb:", hex(qbx0), hex(qbx1))
print(hex(qby0), hex(qby1))