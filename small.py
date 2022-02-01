#small.py

r=0x100000000
p=0x1af

tr=3*r%p
print(hex(tr))
p2=p-2
print("p-2:",bin(p2))

pm=-p
mprime=pow(pm,-1,r)

a=0xB
b=0x6

add=(a+b)%p
sub=(a-b)%p

mul=a*b%p
ar=a*r%p
br=b*r%p
abr=a*b*r%p

rsq=(r*r)%p
one=r%p

print("Mprime:",hex(mprime))
print("Rsq:",hex(rsq))
print("One:",hex(one))

print("A+B:",hex(add))
print("A-B:",hex(sub))
print("AR:",hex(ar))
print("BR:",hex(br))
print("ABR:",hex(abr))
print("AB:",hex(mul))