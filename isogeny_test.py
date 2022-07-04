#isogeny_test.py
import define
import fp
import fp2
import isogeny

#PA := (100i + 248, 304i + 199) and QA := (426i + 394, 51i + 79),

px = fp2.fp2_t(248, 100)
py = fp2.fp2_t(199, 304)
qx = fp2.fp2_t(394, 426)
qy = fp2.fp2_t(79, 51)

olda = fp2.fp2_t(37, 18)
oldb = fp2.fp2_t(1,0)

nexta, nextb = isogeny.isogeny_changea(oldb, olda)

print(f'nexta = {nexta.x0}+{nexta.x1}i, nextb = {nextb.x0}+{nextb.x1}i')