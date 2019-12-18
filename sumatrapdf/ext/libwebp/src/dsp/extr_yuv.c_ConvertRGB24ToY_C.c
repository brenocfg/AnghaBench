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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  VP8RGBToY (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YUV_HALF ; 

__attribute__((used)) static void ConvertRGB24ToY_C(const uint8_t* rgb, uint8_t* y, int width) {
  int i;
  for (i = 0; i < width; ++i, rgb += 3) {
    y[i] = VP8RGBToY(rgb[0], rgb[1], rgb[2], YUV_HALF);
  }
}