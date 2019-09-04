#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ y ;
typedef  scalar_t__ x ;
typedef  int ptrdiff_t ;
typedef  int n ;
typedef  int /*<<< orphan*/  __m128d ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_loadu_pd (scalar_t__) ; 
 int /*<<< orphan*/  _mm_mul_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_pd (double const) ; 
 int /*<<< orphan*/  _mm_storeu_pd (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THDoubleVector_muls_SSE(double *y, const double *x, const double c, const ptrdiff_t n) {
  ptrdiff_t i;
  __m128d XMM15 = _mm_set1_pd(c);
  for (i=0; i<=((n)-8); i+=8) {
    __m128d XMM0 = _mm_loadu_pd((x)+i  );
    __m128d XMM1 = _mm_loadu_pd((x)+i+2);
    __m128d XMM2 = _mm_loadu_pd((x)+i+4);
    __m128d XMM3 = _mm_loadu_pd((x)+i+6);
    __m128d XMM4 = _mm_mul_pd(XMM15, XMM0);
    __m128d XMM5 = _mm_mul_pd(XMM15, XMM1);
    __m128d XMM6 = _mm_mul_pd(XMM15, XMM2);
    __m128d XMM7 = _mm_mul_pd(XMM15, XMM3);
    _mm_storeu_pd((y)+i  , XMM4);
    _mm_storeu_pd((y)+i+2, XMM5);
    _mm_storeu_pd((y)+i+4, XMM6);
    _mm_storeu_pd((y)+i+6, XMM7);
  }
  for (; i<(n); i++) {
    y[i] = x[i] * c;
  }
}