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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  RescalePlane (int*,int,int,int,int,int) ; 
 int abs (int const) ; 

__attribute__((used)) static int DiffScaleChannel(uint8_t* src1, int stride1,
                            const uint8_t* src2, int stride2,
                            int x_stride, int w, int h, int do_scaling) {
  int x, y;
  int max = 0;
  for (y = 0; y < h; ++y) {
    uint8_t* const ptr1 = src1 + y * stride1;
    const uint8_t* const ptr2 = src2 + y * stride2;
    for (x = 0; x < w * x_stride; x += x_stride) {
      const int diff = abs(ptr1[x] - ptr2[x]);
      if (diff > max) max = diff;
      ptr1[x] = diff;
    }
  }

  if (do_scaling) RescalePlane(src1, w, h, x_stride, stride1, max);
  return max;
}