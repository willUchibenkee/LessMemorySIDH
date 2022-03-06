#pragma once

#ifndef TEST_ISOGENY_H
#define TEST_ISOGENY_H

#endif

// #include "count.h"
#include "isogeny.h"
#include "./time.h"

void check_gets(efp2_t *P, efp2_t *Q, efp2_t *S, fp2_t *A, int flag);

void check_isogeny(efp2_t *P, efp2_t *Q, efp2_t *S, fp2_t *A, int flag);

void check_getj(fp2_t *A);