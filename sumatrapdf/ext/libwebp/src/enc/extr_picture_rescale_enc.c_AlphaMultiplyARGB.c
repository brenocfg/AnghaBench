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
struct TYPE_3__ {int argb_stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  WebPMultARGBRows (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AlphaMultiplyARGB(WebPPicture* const pic, int inverse) {
  assert(pic->argb != NULL);
  WebPMultARGBRows((uint8_t*)pic->argb, pic->argb_stride * sizeof(*pic->argb),
                   pic->width, pic->height, inverse);
}