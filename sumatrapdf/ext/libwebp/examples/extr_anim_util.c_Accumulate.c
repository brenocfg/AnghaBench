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

/* Variables and functions */
 double fabs (double) ; 

__attribute__((used)) static void Accumulate(double v1, double v2, double* const max_diff,
                       double* const sse) {
  const double diff = fabs(v1 - v2);
  if (diff > *max_diff) *max_diff = diff;
  *sse += diff * diff;
}