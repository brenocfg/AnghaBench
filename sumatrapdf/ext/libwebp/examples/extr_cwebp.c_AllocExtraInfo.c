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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int width; int height; int /*<<< orphan*/ * extra_info; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 scalar_t__ WebPMalloc (int const) ; 

__attribute__((used)) static void AllocExtraInfo(WebPPicture* const pic) {
  const int mb_w = (pic->width + 15) / 16;
  const int mb_h = (pic->height + 15) / 16;
  pic->extra_info =
      (uint8_t*)WebPMalloc(mb_w * mb_h * sizeof(*pic->extra_info));
}