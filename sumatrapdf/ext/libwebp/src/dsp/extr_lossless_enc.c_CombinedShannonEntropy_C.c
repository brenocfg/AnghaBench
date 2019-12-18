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
 scalar_t__ VP8LFastSLog2 (int const) ; 

__attribute__((used)) static float CombinedShannonEntropy_C(const int X[256], const int Y[256]) {
  int i;
  double retval = 0.;
  int sumX = 0, sumXY = 0;
  for (i = 0; i < 256; ++i) {
    const int x = X[i];
    if (x != 0) {
      const int xy = x + Y[i];
      sumX += x;
      retval -= VP8LFastSLog2(x);
      sumXY += xy;
      retval -= VP8LFastSLog2(xy);
    } else if (Y[i] != 0) {
      sumXY += Y[i];
      retval -= VP8LFastSLog2(Y[i]);
    }
  }
  retval += VP8LFastSLog2(sumX) + VP8LFastSLog2(sumXY);
  return (float)retval;
}