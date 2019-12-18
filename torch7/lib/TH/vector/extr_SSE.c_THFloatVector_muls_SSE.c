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
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_loadu_ps (scalar_t__) ; 
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set_ps1 (float const) ; 
 int /*<<< orphan*/  _mm_storeu_ps (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THFloatVector_muls_SSE(float *y, const float *x, const float c, const ptrdiff_t n) {
  ptrdiff_t i;
  __m128 XMM15 = _mm_set_ps1(c);
  for (i=0; i<=((n)-16); i+=16) {
    __m128 XMM0 = _mm_loadu_ps((x)+i   );
    __m128 XMM1 = _mm_loadu_ps((x)+i+ 4);
    __m128 XMM2 = _mm_loadu_ps((x)+i+ 8);
    __m128 XMM3 = _mm_loadu_ps((x)+i+12);
    __m128 XMM4 = _mm_mul_ps(XMM15, XMM0);
    __m128 XMM5 = _mm_mul_ps(XMM15, XMM1);
    __m128 XMM6 = _mm_mul_ps(XMM15, XMM2);
    __m128 XMM7 = _mm_mul_ps(XMM15, XMM3);
    _mm_storeu_ps((y)+i   , XMM4);
    _mm_storeu_ps((y)+i+ 4, XMM5);
    _mm_storeu_ps((y)+i+ 8, XMM6);
    _mm_storeu_ps((y)+i+12, XMM7);
  }
  for (; i<(n); i++) {
    y[i] = x[i] * c;
  }
}