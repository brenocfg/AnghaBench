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
typedef  scalar_t__ z ;
typedef  scalar_t__ y ;
typedef  scalar_t__ x ;
typedef  int ptrdiff_t ;
typedef  int n ;
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_loadu_ps (scalar_t__) ; 
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_storeu_ps (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THFloatVector_cmul_SSE(float *z, const float *x, const float *y, const ptrdiff_t n) {
  ptrdiff_t i;
  for (i=0; i<=((n)-16); i+=16) {
    __m128 XMM0 = _mm_loadu_ps((x)+i   );
    __m128 XMM1 = _mm_loadu_ps((x)+i+ 4);
    __m128 XMM2 = _mm_loadu_ps((x)+i+ 8);
    __m128 XMM3 = _mm_loadu_ps((x)+i+12);
    __m128 XMM4 = _mm_loadu_ps((y)+i   );
    __m128 XMM5 = _mm_loadu_ps((y)+i+ 4);
    __m128 XMM6 = _mm_loadu_ps((y)+i+ 8);
    __m128 XMM7 = _mm_loadu_ps((y)+i+12);
    XMM4 = _mm_mul_ps(XMM4, XMM0);
    XMM5 = _mm_mul_ps(XMM5, XMM1);
    XMM6 = _mm_mul_ps(XMM6, XMM2);
    XMM7 = _mm_mul_ps(XMM7, XMM3);
    _mm_storeu_ps((z)+i   , XMM4);
    _mm_storeu_ps((z)+i+ 4, XMM5);
    _mm_storeu_ps((z)+i+ 8, XMM6);
    _mm_storeu_ps((z)+i+12, XMM7);
  }
  for (; i<(n); i++) {
    z[i] = x[i] * y[i];
  }
}