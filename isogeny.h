#pragma once
#ifndef ISOGENY_H
#define ISOGENY_H

#include "efp2.h"

void isogeny_gets(efp2_t *S, efp2_t *P, efp2_t *Q, mpz_t k, fp2_t *ap);
void isogeny_changea(fp2_t *nexta, fp2_t *nextb, fp2_t *oldb, fp2_t *alpha);
void isogeny_changeb(fp2_t *nexta, fp2_t *nextb, fp2_t *beta, fp2_t *olda, fp2_t *oldb);
void isogeny_nextp(efp2_t *ans, efp2_t *P, fp2_t *alpha, int l);
void isogeny_mgec3(efp2_t *R, efp2_t *P, fp2_t *ap);
void isogeny_getj(fp2_t *jval, fp2_t *A);

#endif
