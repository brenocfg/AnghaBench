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
typedef  int uint32_t ;

/* Variables and functions */

void VP8LSubtractGreenFromBlueAndRed_C(uint32_t* argb_data, int num_pixels) {
  int i;
  for (i = 0; i < num_pixels; ++i) {
    const int argb = argb_data[i];
    const int green = (argb >> 8) & 0xff;
    const uint32_t new_r = (((argb >> 16) & 0xff) - green) & 0xff;
    const uint32_t new_b = (((argb >>  0) & 0xff) - green) & 0xff;
    argb_data[i] = (argb & 0xff00ff00u) | (new_r << 16) | new_b;
  }
}