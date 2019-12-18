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
typedef  double uint8_t ;

/* Variables and functions */
 int RADIUS ; 

__attribute__((used)) static double AccumulateLSIM(const uint8_t* src, int src_stride,
                             const uint8_t* ref, int ref_stride,
                             int w, int h) {
  int x, y;
  double total_sse = 0.;
  for (y = 0; y < h; ++y) {
    const int y_0 = (y - RADIUS < 0) ? 0 : y - RADIUS;
    const int y_1 = (y + RADIUS + 1 >= h) ? h : y + RADIUS + 1;
    for (x = 0; x < w; ++x) {
      const int x_0 = (x - RADIUS < 0) ? 0 : x - RADIUS;
      const int x_1 = (x + RADIUS + 1 >= w) ? w : x + RADIUS + 1;
      double best_sse = 255. * 255.;
      const double value = (double)ref[y * ref_stride + x];
      int i, j;
      for (j = y_0; j < y_1; ++j) {
        const uint8_t* const s = src + j * src_stride;
        for (i = x_0; i < x_1; ++i) {
          const double diff = s[i] - value;
          const double sse = diff * diff;
          if (sse < best_sse) best_sse = sse;
        }
      }
      total_sse += best_sse;
    }
  }
  return total_sse;
}