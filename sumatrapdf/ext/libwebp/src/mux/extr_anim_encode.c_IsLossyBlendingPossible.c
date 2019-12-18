#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; int* argb; int argb_stride; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_7__ {scalar_t__ x_offset_; scalar_t__ width_; scalar_t__ y_offset_; scalar_t__ height_; } ;
typedef  TYPE_2__ FrameRectangle ;

/* Variables and functions */
 int /*<<< orphan*/  PixelsAreSimilar (int const,int const,int const) ; 
 int QualityToMaxDiff (float) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int IsLossyBlendingPossible(const WebPPicture* const src,
                                   const WebPPicture* const dst,
                                   const FrameRectangle* const rect,
                                   float quality) {
  const int max_allowed_diff_lossy = QualityToMaxDiff(quality);
  int i, j;
  assert(src->width == dst->width && src->height == dst->height);
  assert(rect->x_offset_ + rect->width_ <= dst->width);
  assert(rect->y_offset_ + rect->height_ <= dst->height);
  for (j = rect->y_offset_; j < rect->y_offset_ + rect->height_; ++j) {
    for (i = rect->x_offset_; i < rect->x_offset_ + rect->width_; ++i) {
      const uint32_t src_pixel = src->argb[j * src->argb_stride + i];
      const uint32_t dst_pixel = dst->argb[j * dst->argb_stride + i];
      const uint32_t dst_alpha = dst_pixel >> 24;
      if (dst_alpha != 0xff &&
          !PixelsAreSimilar(src_pixel, dst_pixel, max_allowed_diff_lossy)) {
        // In this case, if we use blending, we can't attain the desired
        // 'dst_pixel' value for this pixel. So, blending is not possible.
        return 0;
      }
    }
  }
  return 1;
}