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
typedef  scalar_t__ x ;
typedef  int ptrdiff_t ;
typedef  int n ;
typedef  int /*<<< orphan*/  __m128d ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_set1_pd (double const) ; 
 int /*<<< orphan*/  _mm_storeu_pd (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THDoubleVector_fill_SSE(double *x, const double c, const ptrdiff_t n) {
  ptrdiff_t i;
  ptrdiff_t off;
  __m128d XMM0 = _mm_set1_pd(c);
  for (i=0; i<=((n)-8); i+=8) {
    _mm_storeu_pd((x)+i  , XMM0);
    _mm_storeu_pd((x)+i+2, XMM0);
    _mm_storeu_pd((x)+i+4, XMM0);
    _mm_storeu_pd((x)+i+6, XMM0);
  }
  off = (n) - ((n)%8);
  for (i=0; i<((n)%8); i++) {
    x[off+i] = c;
  }
}