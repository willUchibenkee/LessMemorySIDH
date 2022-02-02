#scm.py
p=0x1af

px=0x12
py=0x6

a=0x6

#y**2=x**3+ax**2+x

# //x座標

#             //分子の計算
# (x**2-1)**2
bunshi=px*px%p
bunshi=(bunshi-1)%p
bunshi=bunshi*bunshi%p
print("bunshi:", hex(bunshi))
     
#             //分母の計算(最後にinv)
#4*x(x**2 + A*x + 1)
bumbo=px*px%p
work=a*px%p
bumbo=(bumbo+work)%p
bumbo=(bumbo+1)%p
bumbo=bumbo*px%p
bumbo=bumbo*4%p
print("bumbo:", hex(bumbo))

hanten=pow(bumbo, -1, p)
ux=bunshi*hanten%p
print("ux:", hex(ux))

#    (x**2 − 1)(x**4 + 2*A*x**3 + 6*x**2 + 2*A*x + 1)           
#             //y座標 py*(bunshi*bumbo(inv))
#             //分子の計算
work=px*px%p
work=(work-1)%p
work2=(px**4)%p
work3=(2*a*px**3)%p
work2=(work2+work3)%p
work3=(6*px*px)%p
work2=(work2+work3)%p
work3=(2*a*px)%p
work2=(work2+work3+1)%p
bunshi2=work*work2%p

print("bunshi2:", hex(bunshi2))

#8x**2(x**2 + Ax + 1)**2
work=8*px*px%p
work2=((px*px%p)+(a*px%p)+1)%p
work=(work*work2*work2)%p

bumbo2=pow(work, -1, p)

print("bumbo2:", hex(bumbo2))

uy=py*(bunshi2*bumbo2)%p
            
print("U.y:", hex(uy))

#eca x: λ**2 − (xP + xQ) − A
ramda=(uy-py)%p
waru=(ux-px)%p
wari=pow(waru, -1, p)
rmd=ramda*wari%p

print("ramda:", hex(rmd))

rx=((rmd*rmd)%p -((px+ux)%p) - a)%p

print("rx:", hex(rx))
#305
#λはかたむき
# y: λ(xP − xR) − yP
ry=((rmd*(px-rx)%p) - py)%p

print("ry:", hex(ry))
#291

#(x**4 − 4Ax − 6x**2 − 3)(x**8 + 4Ax**7 + 28x**6 + 28Ax**5 + (16A**2 + 6)x**4 + 28Ax**3 + 28x**2 + 4Ax + 1)

bunshi3 = (px**4 - 4*a*px - 6*(px**2) - 3)%p

print("zenhan:", hex(bunshi3))

kouhan=(px**8 + 4*a*(px**7) + 28*(px**6) + 28*a*(px**5) + (16*a**2 + 6)*(px**4) + 28*a*(px**3) + 28*(px**2) + 4*a*px + 1)%p

print("kouhan:",hex(kouhan))

bunshi3=bunshi3*kouhan%p

print("ect_bunshi:", hex(bunshi3))

#(4Ax**3 + 3x**4 + 6x**2 − 1)**3

bumbo=((4*a*(px**3) + 3*(px**4) + 6*(px**2) - 1)**3)%p

hanten = pow(bumbo, -1, p)

print("ect_bumbo(inv)", hex(hanten))

ty = bunshi3*hanten*py%p

print("ect_y:", hex(ty))