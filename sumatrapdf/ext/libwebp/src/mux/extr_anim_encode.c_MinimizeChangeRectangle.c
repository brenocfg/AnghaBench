#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ width; scalar_t__ height; int argb_stride; int /*<<< orphan*/ * argb; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_8__ {scalar_t__ x_offset_; scalar_t__ width_; scalar_t__ y_offset_; scalar_t__ height_; } ;
typedef  TYPE_2__ FrameRectangle ;
typedef  scalar_t__ (* ComparePixelsFunc ) (int /*<<< orphan*/  const* const,int,int /*<<< orphan*/  const* const,int,scalar_t__,int const) ;

/* Variables and functions */
 scalar_t__ ComparePixelsLossless (int /*<<< orphan*/  const* const,int,int /*<<< orphan*/  const* const,int,scalar_t__,int const) ; 
 scalar_t__ ComparePixelsLossy (int /*<<< orphan*/  const* const,int,int /*<<< orphan*/  const* const,int,scalar_t__,int const) ; 
 scalar_t__ IsEmptyRect (TYPE_2__* const) ; 
 int QualityToMaxDiff (float) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void MinimizeChangeRectangle(const WebPPicture* const src,
                                    const WebPPicture* const dst,
                                    FrameRectangle* const rect,
                                    int is_lossless, float quality) {
  int i, j;
  const ComparePixelsFunc compare_pixels =
      is_lossless ? ComparePixelsLossless : ComparePixelsLossy;
  const int max_allowed_diff_lossy = QualityToMaxDiff(quality);
  const int max_allowed_diff = is_lossless ? 0 : max_allowed_diff_lossy;

  // Sanity checks.
  assert(src->width == dst->width && src->height == dst->height);
  assert(rect->x_offset_ + rect->width_ <= dst->width);
  assert(rect->y_offset_ + rect->height_ <= dst->height);

  // Left boundary.
  for (i = rect->x_offset_; i < rect->x_offset_ + rect->width_; ++i) {
    const uint32_t* const src_argb =
        &src->argb[rect->y_offset_ * src->argb_stride + i];
    const uint32_t* const dst_argb =
        &dst->argb[rect->y_offset_ * dst->argb_stride + i];
    if (compare_pixels(src_argb, src->argb_stride, dst_argb, dst->argb_stride,
                       rect->height_, max_allowed_diff)) {
      --rect->width_;  // Redundant column.
      ++rect->x_offset_;
    } else {
      break;
    }
  }
  if (rect->width_ == 0) goto NoChange;

  // Right boundary.
  for (i = rect->x_offset_ + rect->width_ - 1; i >= rect->x_offset_; --i) {
    const uint32_t* const src_argb =
        &src->argb[rect->y_offset_ * src->argb_stride + i];
    const uint32_t* const dst_argb =
        &dst->argb[rect->y_offset_ * dst->argb_stride + i];
    if (compare_pixels(src_argb, src->argb_stride, dst_argb, dst->argb_stride,
                       rect->height_, max_allowed_diff)) {
      --rect->width_;  // Redundant column.
    } else {
      break;
    }
  }
  if (rect->width_ == 0) goto NoChange;

  // Top boundary.
  for (j = rect->y_offset_; j < rect->y_offset_ + rect->height_; ++j) {
    const uint32_t* const src_argb =
        &src->argb[j * src->argb_stride + rect->x_offset_];
    const uint32_t* const dst_argb =
        &dst->argb[j * dst->argb_stride + rect->x_offset_];
    if (compare_pixels(src_argb, 1, dst_argb, 1, rect->width_,
                       max_allowed_diff)) {
      --rect->height_;  // Redundant row.
      ++rect->y_offset_;
    } else {
      break;
    }
  }
  if (rect->height_ == 0) goto NoChange;

  // Bottom boundary.
  for (j = rect->y_offset_ + rect->height_ - 1; j >= rect->y_offset_; --j) {
    const uint32_t* const src_argb =
        &src->argb[j * src->argb_stride + rect->x_offset_];
    const uint32_t* const dst_argb =
        &dst->argb[j * dst->argb_stride + rect->x_offset_];
    if (compare_pixels(src_argb, 1, dst_argb, 1, rect->width_,
                       max_allowed_diff)) {
      --rect->height_;  // Redundant row.
    } else {
      break;
    }
  }
  if (rect->height_ == 0) goto NoChange;

  if (IsEmptyRect(rect)) {
 NoChange:
    rect->x_offset_ = 0;
    rect->y_offset_ = 0;
    rect->width_ = 0;
    rect->height_ = 0;
  }
}