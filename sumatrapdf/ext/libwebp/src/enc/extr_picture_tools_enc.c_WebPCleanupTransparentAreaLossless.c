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
struct TYPE_3__ {int width; int height; int* argb; int /*<<< orphan*/  argb_stride; scalar_t__ use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void WebPCleanupTransparentAreaLossless(WebPPicture* const pic) {
  int x, y, w, h;
  uint32_t* argb;
  assert(pic != NULL && pic->use_argb);
  w = pic->width;
  h = pic->height;
  argb = pic->argb;

  for (y = 0; y < h; ++y) {
    for (x = 0; x < w; ++x) {
      if ((argb[x] & 0xff000000) == 0) {
        argb[x] = 0x00000000;
      }
    }
    argb += pic->argb_stride;
  }
}