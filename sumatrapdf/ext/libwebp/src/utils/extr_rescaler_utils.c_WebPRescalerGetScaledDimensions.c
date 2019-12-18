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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int WebPRescalerGetScaledDimensions(int src_width, int src_height,
                                    int* const scaled_width,
                                    int* const scaled_height) {
  assert(scaled_width != NULL);
  assert(scaled_height != NULL);
  {
    int width = *scaled_width;
    int height = *scaled_height;

    // if width is unspecified, scale original proportionally to height ratio.
    if (width == 0 && src_height > 0) {
      width =
          (int)(((uint64_t)src_width * height + src_height - 1) / src_height);
    }
    // if height is unspecified, scale original proportionally to width ratio.
    if (height == 0 && src_width > 0) {
      height =
          (int)(((uint64_t)src_height * width + src_width - 1) / src_width);
    }
    // Check if the overall dimensions still make sense.
    if (width <= 0 || height <= 0) {
      return 0;
    }

    *scaled_width = width;
    *scaled_height = height;
    return 1;
  }
}