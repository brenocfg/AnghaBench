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
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_div_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_loadu_ps (float const*) ; 
 int /*<<< orphan*/  _mm_set1_ps (float const) ; 
 int /*<<< orphan*/  _mm_storeu_ps (float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THFloatVector_divs_SSE(float *y, const float *x, const float c, const ptrdiff_t n) {
  ptrdiff_t i;
  __m128 XMM7 = _mm_set1_ps(c);
  __m128 XMM0, XMM1;
  for (i=0; i<=((n)-8); i+=8) {
    XMM0 = _mm_loadu_ps(x+i);
    XMM1 = _mm_loadu_ps(x+i+4);
    XMM0 = _mm_div_ps(XMM0, XMM7);
    XMM1 = _mm_div_ps(XMM1, XMM7);
    _mm_storeu_ps(y+i, XMM0);
    _mm_storeu_ps(y+i+4, XMM1);
  }
  for (; i<(n); i++) {
    y[i] = x[i] / c;
  }
}