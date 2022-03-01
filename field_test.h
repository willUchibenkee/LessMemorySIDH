#pragma once

#ifndef FIELD_TEST_H
#define FIELD_TEST_H

// #include "count.h"
#include "fp2.h"
#include "./time.h"

int test_fp(int fp_n);
int test_fp2(int fp2_n);
int test_fp6(int fp6_n);
int test_field(int fp, int fp2, int fp6, int sqr);
int test_fp_montgomery(int fp_n);

void check_fp_with_montgomery();
void check_fp2_with_montgomery();
void check_fp6_with_montgomery();

void check_fp();
void check_fp2();

void BENCH_fp2_fp6_mul_lazy_montgomery(int LOOP);
void BENCH_miller_jac_lazy_montgomery(int LOOP);
void BENCH_miller_proj_lazy_montgomery(int LOOP);
void BENCH_finalexp_lazy_montgomery(int LOOP);
void BENCH_Pairing_jac_lazy_montgomery(int LOOP);
void BENCH_Pairing_proj_lazy_montgomery(int LOOP);

void check_count_finalexp_pow_2NAF();
#endif
void BENCH_Pairing_proj_lazy_montgomery_static(int LOOP);