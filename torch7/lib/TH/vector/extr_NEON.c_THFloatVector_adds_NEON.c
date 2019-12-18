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

/* Variables and functions */

__attribute__((used)) static void THFloatVector_adds_NEON(float *y, const float *x, const float c, const ptrdiff_t n) {
  long i = 0;

  for(;i < n-4; i += 4)
  {
    y[i] = x[i] + c;
    y[i+1] = x[i+1] + c;
    y[i+2] = x[i+2] + c;
    y[i+3] = x[i+3] + c;
  }

  for(; i < n; i++)
    y[i] = x[i] + c;
}