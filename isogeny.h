#pragma once
#ifndef ISOGENY_H
#define ISOGENY_H
#endif

#include "efp2.h"
#include <gmp.h>

void Isogeny_gets(efp2_t *S, efp2_t *P, efp2_t *Q, mpz_t k, fp2_t *ap);
void Isogeny_changea(fp2_t *nexta, fp2_t *alpha);
void Isogeny_changeb(fp2_t *nexta, fp2_t *beta, fp2_t *olda);
void Isogeny_nextp(efp2_t *ans, efp2_t *P, fp2_t *alpha, int l);
void Isogeny_mgec3(efp2_t *R, efp2_t *P, fp2_t *ap);
void isogeny_getj(fp2_t *jval, fp2_t *A);