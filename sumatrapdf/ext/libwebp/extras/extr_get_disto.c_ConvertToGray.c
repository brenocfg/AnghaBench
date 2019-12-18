#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int height; int* argb; int argb_stride; int width; int /*<<< orphan*/  use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ConvertToGray(WebPPicture* const pic) {
  int x, y;
  assert(pic != NULL);
  assert(pic->use_argb);
  for (y = 0; y < pic->height; ++y) {
    uint32_t* const row = &pic->argb[y * pic->argb_stride];
    for (x = 0; x < pic->width; ++x) {
      const uint32_t argb = row[x];
      const uint32_t r = (argb >> 16) & 0xff;
      const uint32_t g = (argb >>  8) & 0xff;
      const uint32_t b = (argb >>  0) & 0xff;
      // We use BT.709 for converting to luminance.
      const uint32_t Y = (uint32_t)(0.2126 * r + 0.7152 * g + 0.0722 * b + .5);
      row[x] = (argb & 0xff000000u) | (Y * 0x010101u);
    }
  }
}