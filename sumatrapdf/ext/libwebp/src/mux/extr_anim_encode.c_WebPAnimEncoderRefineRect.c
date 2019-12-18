#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  use_argb; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_10__ {int x_offset_; int y_offset_; int width_; int height_; } ;
typedef  TYPE_2__ FrameRectangle ;

/* Variables and functions */
 int /*<<< orphan*/  MinimizeChangeRectangle (TYPE_1__ const* const,TYPE_1__ const* const,TYPE_2__*,int,float) ; 
 int /*<<< orphan*/  SnapToEvenOffsets (TYPE_2__*) ; 
 void* clip (int const,int /*<<< orphan*/ ,scalar_t__) ; 

int WebPAnimEncoderRefineRect(
    const WebPPicture* const prev_canvas, const WebPPicture* const curr_canvas,
    int is_lossless, float quality, int* const x_offset, int* const y_offset,
    int* const width, int* const height) {
  FrameRectangle rect;
  const int right = clip(*x_offset + *width, 0, curr_canvas->width);
  const int left = clip(*x_offset, 0, curr_canvas->width - 1);
  const int bottom = clip(*y_offset + *height, 0, curr_canvas->height);
  const int top = clip(*y_offset, 0, curr_canvas->height - 1);
  if (prev_canvas == NULL || curr_canvas == NULL ||
      prev_canvas->width != curr_canvas->width ||
      prev_canvas->height != curr_canvas->height ||
      !prev_canvas->use_argb || !curr_canvas->use_argb) {
    return 0;
  }
  rect.x_offset_ = left;
  rect.y_offset_ = top;
  rect.width_ = clip(right - left, 0, curr_canvas->width - rect.x_offset_);
  rect.height_ = clip(bottom - top, 0, curr_canvas->height - rect.y_offset_);
  MinimizeChangeRectangle(prev_canvas, curr_canvas, &rect, is_lossless,
                          quality);
  SnapToEvenOffsets(&rect);
  *x_offset = rect.x_offset_;
  *y_offset = rect.y_offset_;
  *width = rect.width_;
  *height = rect.height_;
  return 1;
}