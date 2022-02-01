#small.py

r=0x100000000
p=0x1af



a0=0xB
a1=0x4E
b0=0x6
b1=0x17A

add0=(a0+b0)%p
add1=(a1+b1)%p
sub0=(a0-b0)%p
sub1=(a1-b1)%p

mul0=(a0*b0 - a1*b1)%p
mul1=(a0*b1 + a1*b0)%p
ar0=a0*r%p
ar1=a1*r%p
br0=b0*r%p
br1=b1*r%p
abr0=(a0*br0 - a1*br1)%p
abr1=(a0*br1 + a1*br0)%p

print("A+B:",hex(add0),hex(add1))
print("A-B:",hex(sub0),hex(sub1))
print("AR:",hex(ar0), hex(ar1))
print("BR:",hex(br0), hex(br1))
print("ABR:",hex(abr0), hex(abr1))
print("AB:",hex(mul0), hex(mul1))