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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */

__attribute__((used)) static void set_pixel32(uint8 * data, int x, int y,
                        int width, int height, int pixel)
{
  if (x >= 0 && y >= 0 && x < width && y < height)
  {
    *(((int*)data) + (y * width + x)) = pixel;
  }
}