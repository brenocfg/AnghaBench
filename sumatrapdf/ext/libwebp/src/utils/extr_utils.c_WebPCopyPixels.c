#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int width; scalar_t__ height; int argb_stride; scalar_t__ argb; scalar_t__ use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  WebPCopyPlane (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 

void WebPCopyPixels(const WebPPicture* const src, WebPPicture* const dst) {
  assert(src != NULL && dst != NULL);
  assert(src->width == dst->width && src->height == dst->height);
  assert(src->use_argb && dst->use_argb);
  WebPCopyPlane((uint8_t*)src->argb, 4 * src->argb_stride, (uint8_t*)dst->argb,
                4 * dst->argb_stride, 4 * src->width, src->height);
}