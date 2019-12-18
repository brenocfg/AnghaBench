#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_8__ {int width; int height; int y_stride; int uv_stride; int a_stride; int argb_stride; scalar_t__ argb; int /*<<< orphan*/  const* a; int /*<<< orphan*/  const* v; int /*<<< orphan*/  const* u; int /*<<< orphan*/  const* y; int /*<<< orphan*/  use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustAndCheckRectangle (TYPE_1__*,int*,int*,int,int) ; 
 int HALVE (int) ; 
 int /*<<< orphan*/  PictureGrabSpecs (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  WebPCopyPlane (int /*<<< orphan*/  const* const,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 

int WebPPictureCrop(WebPPicture* pic,
                    int left, int top, int width, int height) {
  WebPPicture tmp;

  if (pic == NULL) return 0;
  if (!AdjustAndCheckRectangle(pic, &left, &top, width, height)) return 0;

  PictureGrabSpecs(pic, &tmp);
  tmp.width = width;
  tmp.height = height;
  if (!WebPPictureAlloc(&tmp)) return 0;

  if (!pic->use_argb) {
    const int y_offset = top * pic->y_stride + left;
    const int uv_offset = (top / 2) * pic->uv_stride + left / 2;
    WebPCopyPlane(pic->y + y_offset, pic->y_stride,
                  tmp.y, tmp.y_stride, width, height);
    WebPCopyPlane(pic->u + uv_offset, pic->uv_stride,
                  tmp.u, tmp.uv_stride, HALVE(width), HALVE(height));
    WebPCopyPlane(pic->v + uv_offset, pic->uv_stride,
                  tmp.v, tmp.uv_stride, HALVE(width), HALVE(height));

    if (tmp.a != NULL) {
      const int a_offset = top * pic->a_stride + left;
      WebPCopyPlane(pic->a + a_offset, pic->a_stride,
                    tmp.a, tmp.a_stride, width, height);
    }
  } else {
    const uint8_t* const src =
        (const uint8_t*)(pic->argb + top * pic->argb_stride + left);
    WebPCopyPlane(src, pic->argb_stride * 4, (uint8_t*)tmp.argb,
                  tmp.argb_stride * 4, width * 4, height);
  }
  WebPPictureFree(pic);
  *pic = tmp;
  return 1;
}