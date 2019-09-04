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
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_set_ps1 (float const) ; 
 int /*<<< orphan*/  _mm_storeu_ps (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THFloatVector_fill_SSE(float *x, const float c, const ptrdiff_t n) {
  ptrdiff_t i;
  __m128 XMM0 = _mm_set_ps1(c);
  ptrdiff_t off;
  for (i=0; i<=((n)-16); i+=16) {
    _mm_storeu_ps((x)+i  ,  XMM0);
    _mm_storeu_ps((x)+i+4,  XMM0);
    _mm_storeu_ps((x)+i+8,  XMM0);
    _mm_storeu_ps((x)+i+12, XMM0);
  }
  off = (n) - ((n)%16);
  for (i=0; i<((n)%16); i++) {
    x[off+i] = c;
  }
}