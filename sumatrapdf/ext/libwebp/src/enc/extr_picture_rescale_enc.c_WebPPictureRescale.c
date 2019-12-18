#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  rescaler_t ;
struct TYPE_9__ {int width; int height; int a_stride; int y_stride; int uv_stride; int argb_stride; scalar_t__ argb; int /*<<< orphan*/  const* v; int /*<<< orphan*/  const* u; int /*<<< orphan*/  const* y; int /*<<< orphan*/  const* a; int /*<<< orphan*/  use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  AlphaMultiplyARGB (TYPE_1__*,int) ; 
 int /*<<< orphan*/  AlphaMultiplyY (TYPE_1__*,int) ; 
 int HALVE (int) ; 
 int /*<<< orphan*/  PictureGrabSpecs (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  RescalePlane (int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WebPInitAlphaProcessing () ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPRescalerGetScaledDimensions (int,int,int*,int*) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,int) ; 

int WebPPictureRescale(WebPPicture* pic, int width, int height) {
  WebPPicture tmp;
  int prev_width, prev_height;
  rescaler_t* work;

  if (pic == NULL) return 0;
  prev_width = pic->width;
  prev_height = pic->height;
  if (!WebPRescalerGetScaledDimensions(
          prev_width, prev_height, &width, &height)) {
    return 0;
  }

  PictureGrabSpecs(pic, &tmp);
  tmp.width = width;
  tmp.height = height;
  if (!WebPPictureAlloc(&tmp)) return 0;

  if (!pic->use_argb) {
    work = (rescaler_t*)WebPSafeMalloc(2ULL * width, sizeof(*work));
    if (work == NULL) {
      WebPPictureFree(&tmp);
      return 0;
    }
    // If present, we need to rescale alpha first (for AlphaMultiplyY).
    if (pic->a != NULL) {
      WebPInitAlphaProcessing();
      RescalePlane(pic->a, prev_width, prev_height, pic->a_stride,
                   tmp.a, width, height, tmp.a_stride, work, 1);
    }

    // We take transparency into account on the luma plane only. That's not
    // totally exact blending, but still is a good approximation.
    AlphaMultiplyY(pic, 0);
    RescalePlane(pic->y, prev_width, prev_height, pic->y_stride,
                 tmp.y, width, height, tmp.y_stride, work, 1);
    AlphaMultiplyY(&tmp, 1);

    RescalePlane(pic->u,
                 HALVE(prev_width), HALVE(prev_height), pic->uv_stride,
                 tmp.u,
                 HALVE(width), HALVE(height), tmp.uv_stride, work, 1);
    RescalePlane(pic->v,
                 HALVE(prev_width), HALVE(prev_height), pic->uv_stride,
                 tmp.v,
                 HALVE(width), HALVE(height), tmp.uv_stride, work, 1);
  } else {
    work = (rescaler_t*)WebPSafeMalloc(2ULL * width * 4, sizeof(*work));
    if (work == NULL) {
      WebPPictureFree(&tmp);
      return 0;
    }
    // In order to correctly interpolate colors, we need to apply the alpha
    // weighting first (black-matting), scale the RGB values, and remove
    // the premultiplication afterward (while preserving the alpha channel).
    WebPInitAlphaProcessing();
    AlphaMultiplyARGB(pic, 0);
    RescalePlane((const uint8_t*)pic->argb, prev_width, prev_height,
                 pic->argb_stride * 4,
                 (uint8_t*)tmp.argb, width, height,
                 tmp.argb_stride * 4,
                 work, 4);
    AlphaMultiplyARGB(&tmp, 1);
  }
  WebPPictureFree(pic);
  WebPSafeFree(work);
  *pic = tmp;
  return 1;
}