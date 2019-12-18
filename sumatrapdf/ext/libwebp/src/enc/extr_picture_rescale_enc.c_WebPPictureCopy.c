#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_7__ {int y_stride; int width; int height; int uv_stride; int a_stride; int argb_stride; scalar_t__ argb; int /*<<< orphan*/  const* a; int /*<<< orphan*/  const* v; int /*<<< orphan*/  const* u; int /*<<< orphan*/  const* y; int /*<<< orphan*/  use_argb; } ;
typedef  TYPE_1__ const WebPPicture ;

/* Variables and functions */
 int HALVE (int) ; 
 int /*<<< orphan*/  PictureGrabSpecs (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  WebPCopyPlane (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__ const*) ; 

int WebPPictureCopy(const WebPPicture* src, WebPPicture* dst) {
  if (src == NULL || dst == NULL) return 0;
  if (src == dst) return 1;

  PictureGrabSpecs(src, dst);
  if (!WebPPictureAlloc(dst)) return 0;

  if (!src->use_argb) {
    WebPCopyPlane(src->y, src->y_stride,
                  dst->y, dst->y_stride, dst->width, dst->height);
    WebPCopyPlane(src->u, src->uv_stride, dst->u, dst->uv_stride,
                  HALVE(dst->width), HALVE(dst->height));
    WebPCopyPlane(src->v, src->uv_stride, dst->v, dst->uv_stride,
                  HALVE(dst->width), HALVE(dst->height));
    if (dst->a != NULL)  {
      WebPCopyPlane(src->a, src->a_stride,
                    dst->a, dst->a_stride, dst->width, dst->height);
    }
  } else {
    WebPCopyPlane((const uint8_t*)src->argb, 4 * src->argb_stride,
                  (uint8_t*)dst->argb, 4 * dst->argb_stride,
                  4 * dst->width, dst->height);
  }
  return 1;
}