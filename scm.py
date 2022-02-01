#scm.py
p=0x1af

px0=0x64
px1=0xf8
py0=0x130
py1=0xc7

a0=0x149 
a1=0x1a7

# Fp2_mul(&bunshi, &P->x, &P->x);
bunshi0=px0*px0-px1*px1
bunshi1=2*px0*px1
# Fp2_sub(&bunshi, &bunshi, &one);
bunshi0=bunshi0-1
# Fp2_mul(&bunshi, &bunshi, &bunshi);
bunshi0=bunshi0*bunshi0-bunshi1*bunshi1
bunshi1=2*bunshi0*bunshi1
print(hex(bunshi0%p), hex(bunshi1%p))
            
# //分母の計算(最後にinv)
# Fp2_mul(&bumbo, &P->x, &P->x);
bumbo0=px0*px0-px1*px1
bumbo1=2*px0*px1
# Fp2_mul(&work, ap, &P->x); 
work0=a0*px0-a1*px1
work1=a1*px0+a0*px1
# Fp2_add(&bumbo, &bumbo, &work);
bumbo0=bumbo0+work0
bumbo1=bumbo1+work1
# Fp2_add(&bumbo, &bumbo, &one);
bumbo0=bumbo0+1
# Fp2_mul(&bumbo, &bumbo, &P->x);
bumbo0=bumbo0*px0-bumbo1*px1
bumbo1=bumbo1*px0+bumbo0*px1
# Fp2_mul(&bumbo, &bumbo, &four);
bumbo0=bumbo0*4
bumbo1=bumbo1*4
print(hex(bumbo0%p), hex(bumbo1%p))
# Fp2_inv(&bumbo, &bumbo);
            
# //分子/分母
# Fp2_mul(&U.x, &bunshi, &bumbo);
            
# //y座標
# //かたまり１
# //分子の計算
# Fp2_mul(&work, &P->x, &two2);
# Fp2_add(&work, &work, &P->x);
# Fp2_add(&work, &work, ap);
# Fp2_mul(&work2, &P->x, &P->x);
# Fp2_mul(&work2, &work2, &three2);
# Fp2_mul(&work3, &P->x, ap);
# Fp2_mul(&work3, &work3, &two2);
# Fp2_add(&work2, &work2, &work3);
# Fp2_add(&work2, &work2, &one);
# Fp2_mul(&bunshi, &work, &work2);

# //分母の計算(最後にinv)
# Fp2_mul(&bumbo, &two2, &P->y);
# Fp2_set(&bumbo2, &bumbo);
# Fp2_inv(&bumbo, &bumbo);

# //分子/分母
# Fp2_mul(&katamari, &bunshi, &bumbo);

# //かたまり２
# //分子の計算
# //Fp2_sqr3(&bunshi2, &work2);
# Fp2_mul(&bunshi2, &work2, &work2);
# Fp2_mul(&bunshi2, &bunshi2, &work2);

# //分母の計算(最後にinv)
# //Fp2_sqr3(&bumbo2, &bumbo2);
# Fp2_mul(&work, &bumbo2, &bumbo2);
# Fp2_mul(&bumbo2, &work, &bumbo2);
# Fp2_inv(&bumbo2, &bumbo2);

# //分子/分母
# Fp2_mul(&katamari2, &bunshi2, &bumbo2);
# Fp2_sub(&U.y, &katamari, &katamari2);
# Fp2_sub(&U.y, &U.y, &P->y);