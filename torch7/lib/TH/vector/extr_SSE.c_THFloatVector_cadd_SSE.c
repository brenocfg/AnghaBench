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
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  y ;
typedef  int /*<<< orphan*/  x ;
typedef  int ptrdiff_t ;
typedef  int n ;
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_add_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_loadu_ps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set_ps1 (float const) ; 
 int /*<<< orphan*/  _mm_storeu_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THFloatVector_cadd_SSE(float *z, const float *x, const float *y, const float c, const ptrdiff_t n) {
  ptrdiff_t i;
  __m128 XMM7 = _mm_set_ps1(c);
  __m128 XMM0, XMM2;
  for (i=0; i<=((n)-4); i+=4) {
    XMM0 = _mm_loadu_ps((x)+i);
    XMM2 = _mm_loadu_ps((y)+i);
    XMM2 = _mm_mul_ps(XMM2, XMM7);
    XMM2 = _mm_add_ps(XMM0, XMM2);
    _mm_storeu_ps((z)+i, XMM2);
  }
  for (; i<(n); i++) {
    z[i] = x[i] + c * y[i];
  }
}