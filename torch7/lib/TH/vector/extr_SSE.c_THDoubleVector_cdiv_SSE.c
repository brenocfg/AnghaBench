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
typedef  int ptrdiff_t ;
typedef  int n ;
typedef  int /*<<< orphan*/  __m128d ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_div_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_loadu_pd (double const*) ; 
 int /*<<< orphan*/  _mm_storeu_pd (double*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THDoubleVector_cdiv_SSE(double *z, const double *x, const double *y, const ptrdiff_t n) {
  ptrdiff_t i;
  __m128d XMM0, XMM1, XMM2, XMM3;
  for (i=0; i<=((n)-4); i+=4) {
    XMM0 = _mm_loadu_pd(x+i);
    XMM1 = _mm_loadu_pd(x+i+2);
    XMM2 = _mm_loadu_pd(y+i);
    XMM3 = _mm_loadu_pd(y+i+2);
    XMM2 = _mm_div_pd(XMM0, XMM2);
    XMM3 = _mm_div_pd(XMM1, XMM3);
    _mm_storeu_pd(z+i, XMM2);
    _mm_storeu_pd(z+i+2, XMM3);
  }
  for (; i<(n); i++) {
    z[i] = x[i] / y[i];
  }
}