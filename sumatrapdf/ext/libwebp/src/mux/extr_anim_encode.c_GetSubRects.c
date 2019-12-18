#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_11__ {int /*<<< orphan*/  height_; int /*<<< orphan*/  width_; scalar_t__ y_offset_; scalar_t__ x_offset_; } ;
struct TYPE_10__ {int /*<<< orphan*/  sub_frame_lossy_; TYPE_8__ rect_lossy_; int /*<<< orphan*/  empty_rect_allowed_; TYPE_8__ rect_ll_; int /*<<< orphan*/  sub_frame_ll_; } ;
typedef  TYPE_2__ SubFrameParams ;

/* Variables and functions */
 int GetSubRect (TYPE_1__ const* const,TYPE_1__ const* const,int,int,int /*<<< orphan*/ ,int,float,TYPE_8__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int GetSubRects(const WebPPicture* const prev_canvas,
                       const WebPPicture* const curr_canvas, int is_key_frame,
                       int is_first_frame, float quality,
                       SubFrameParams* const params) {
  // Lossless frame rectangle.
  params->rect_ll_.x_offset_ = 0;
  params->rect_ll_.y_offset_ = 0;
  params->rect_ll_.width_ = curr_canvas->width;
  params->rect_ll_.height_ = curr_canvas->height;
  if (!GetSubRect(prev_canvas, curr_canvas, is_key_frame, is_first_frame,
                  params->empty_rect_allowed_, 1, quality,
                  &params->rect_ll_, &params->sub_frame_ll_)) {
    return 0;
  }
  // Lossy frame rectangle.
  params->rect_lossy_ = params->rect_ll_;  // seed with lossless rect.
  return GetSubRect(prev_canvas, curr_canvas, is_key_frame, is_first_frame,
                    params->empty_rect_allowed_, 0, quality,
                    &params->rect_lossy_, &params->sub_frame_lossy_);
}