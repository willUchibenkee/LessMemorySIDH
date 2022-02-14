#mul2.py

x0=248
x1=100

y0=199
y1=304

a0=37
a1=23

p=431

mul0=(x0*a0 - x1*a1)%p
mul1=(x0*a1 + x1*a0)%p

sa0=(x0 - a0)%p
sa1=(x1 - a1)%p

print("x-a:", sa0, sa1)

print("zenhan:", mul0 - 1, mul1)

maru10=(mul0*x0 - mul1*x1)%p
maru11=(mul0*x1 + mul1*x0)%p

print("maru1:", maru10, maru11)

maru20=(mul0*a0 - mul1*a1)%p
maru21=(mul0*a1 + mul1*a0)%p

print("maru2:", maru20, maru21)

print("3 * maru2:", (maru20 * 3)%p, (maru21 * 3)%p)

hiki0=(maru10 - (maru20 * 3)%p)%p
hiki1=(maru11 - (maru21 * 3)%p)%p

print("maru1 - 3 * maru2:", hiki0, hiki1)

tasu0=(hiki0 + x0)%p
tasu1=(hiki1 + x1)%p

print("maru1 - 3 * maru2 + x:", tasu0, tasu1)

kouhan0=(tasu0+a0)%p
kouhan1=(tasu1+a1)%p

print("kouhan:", kouhan0, kouhan1)

zenhan0=(mul0 - 1)%p
zenhan1=mul1%p

bunshi0=(zenhan0*kouhan0 - zenhan1*kouhan1)%p
bunshi1=(zenhan0*kouhan1 + zenhan1*kouhan0)%p

print("bunshi:", bunshi0, bunshi1)

jijyo0=(sa0*sa0 - sa1*sa1)%p
jijyo1=(2*sa0*sa1)%p
bumbo0=(sa0*jijyo0 - sa1*jijyo1)%p
bumbo1=(sa1*jijyo0 + sa0*jijyo1)%p

print("bumbo:", bumbo0, bumbo1)

# inv0
# inv1