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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static int SmoothenBlock(const uint8_t* a_ptr, int a_stride, uint8_t* y_ptr,
                         int y_stride, int width, int height) {
  int sum = 0, count = 0;
  int x, y;
  const uint8_t* alpha_ptr = a_ptr;
  uint8_t* luma_ptr = y_ptr;
  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      if (alpha_ptr[x] != 0) {
        ++count;
        sum += luma_ptr[x];
      }
    }
    alpha_ptr += a_stride;
    luma_ptr += y_stride;
  }
  if (count > 0 && count < width * height) {
    const uint8_t avg_u8 = (uint8_t)(sum / count);
    alpha_ptr = a_ptr;
    luma_ptr = y_ptr;
    for (y = 0; y < height; ++y) {
      for (x = 0; x < width; ++x) {
        if (alpha_ptr[x] == 0) luma_ptr[x] = avg_u8;
      }
      alpha_ptr += a_stride;
      luma_ptr += y_stride;
    }
  }
  return (count == 0);
}