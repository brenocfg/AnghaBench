#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VP8StatusCode ;
struct TYPE_8__ {int const crop_left; int const crop_top; int crop_bottom; int crop_right; scalar_t__ bypass_filtering; int /*<<< orphan*/  (* setup ) (TYPE_1__* const) ;} ;
typedef  TYPE_1__ VP8Io ;
struct TYPE_9__ {size_t filter_type_; int tl_mb_x_; int tl_mb_y_; int br_mb_y_; int br_mb_x_; int mb_w_; int mb_h_; int /*<<< orphan*/  status_; } ;
typedef  TYPE_2__ VP8Decoder ;

/* Variables and functions */
 int /*<<< orphan*/  PrecomputeFilterStrengths (TYPE_2__* const) ; 
 int /*<<< orphan*/  VP8SetError (TYPE_2__* const,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VP8_STATUS_OK ; 
 int /*<<< orphan*/  VP8_STATUS_USER_ABORT ; 
 int* kFilterExtraRows ; 
 int /*<<< orphan*/  stub1 (TYPE_1__* const) ; 

VP8StatusCode VP8EnterCritical(VP8Decoder* const dec, VP8Io* const io) {
  // Call setup() first. This may trigger additional decoding features on 'io'.
  // Note: Afterward, we must call teardown() no matter what.
  if (io->setup != NULL && !io->setup(io)) {
    VP8SetError(dec, VP8_STATUS_USER_ABORT, "Frame setup failed");
    return dec->status_;
  }

  // Disable filtering per user request
  if (io->bypass_filtering) {
    dec->filter_type_ = 0;
  }

  // Define the area where we can skip in-loop filtering, in case of cropping.
  //
  // 'Simple' filter reads two luma samples outside of the macroblock
  // and filters one. It doesn't filter the chroma samples. Hence, we can
  // avoid doing the in-loop filtering before crop_top/crop_left position.
  // For the 'Complex' filter, 3 samples are read and up to 3 are filtered.
  // Means: there's a dependency chain that goes all the way up to the
  // top-left corner of the picture (MB #0). We must filter all the previous
  // macroblocks.
  {
    const int extra_pixels = kFilterExtraRows[dec->filter_type_];
    if (dec->filter_type_ == 2) {
      // For complex filter, we need to preserve the dependency chain.
      dec->tl_mb_x_ = 0;
      dec->tl_mb_y_ = 0;
    } else {
      // For simple filter, we can filter only the cropped region.
      // We include 'extra_pixels' on the other side of the boundary, since
      // vertical or horizontal filtering of the previous macroblock can
      // modify some abutting pixels.
      dec->tl_mb_x_ = (io->crop_left - extra_pixels) >> 4;
      dec->tl_mb_y_ = (io->crop_top - extra_pixels) >> 4;
      if (dec->tl_mb_x_ < 0) dec->tl_mb_x_ = 0;
      if (dec->tl_mb_y_ < 0) dec->tl_mb_y_ = 0;
    }
    // We need some 'extra' pixels on the right/bottom.
    dec->br_mb_y_ = (io->crop_bottom + 15 + extra_pixels) >> 4;
    dec->br_mb_x_ = (io->crop_right + 15 + extra_pixels) >> 4;
    if (dec->br_mb_x_ > dec->mb_w_) {
      dec->br_mb_x_ = dec->mb_w_;
    }
    if (dec->br_mb_y_ > dec->mb_h_) {
      dec->br_mb_y_ = dec->mb_h_;
    }
  }
  PrecomputeFilterStrengths(dec);
  return VP8_STATUS_OK;
}