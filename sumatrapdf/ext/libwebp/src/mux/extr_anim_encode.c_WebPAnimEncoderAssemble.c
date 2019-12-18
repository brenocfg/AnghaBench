#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  double uint32_t ;
typedef  scalar_t__ WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  int /*<<< orphan*/  WebPData ;
struct TYPE_10__ {int /*<<< orphan*/  anim_params; } ;
struct TYPE_11__ {int in_frame_count_; scalar_t__ count_; double first_timestamp_; scalar_t__ flush_count_; int out_frame_count_; TYPE_1__ options_; int /*<<< orphan*/  canvas_height_; int /*<<< orphan*/  canvas_width_; int /*<<< orphan*/ * mux_; scalar_t__ prev_timestamp_; int /*<<< orphan*/  got_null_frame_; } ;
typedef  TYPE_2__ WebPAnimEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  FlushFrames (TYPE_2__*) ; 
 int /*<<< orphan*/  IncreasePreviousDuration (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  MarkError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  MarkError2 (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  MarkNoError (TYPE_2__*) ; 
 scalar_t__ OptimizeSingleFrame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ WEBP_MUX_OK ; 
 scalar_t__ WebPMuxAssemble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WebPMuxSetAnimationParams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WebPMuxSetCanvasSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int WebPAnimEncoderAssemble(WebPAnimEncoder* enc, WebPData* webp_data) {
  WebPMux* mux;
  WebPMuxError err;

  if (enc == NULL) {
    return 0;
  }
  MarkNoError(enc);

  if (webp_data == NULL) {
    MarkError(enc, "ERROR assembling: NULL input");
    return 0;
  }

  if (enc->in_frame_count_ == 0) {
    MarkError(enc, "ERROR: No frames to assemble");
    return 0;
  }

  if (!enc->got_null_frame_ && enc->in_frame_count_ > 1 && enc->count_ > 0) {
    // set duration of the last frame to be avg of durations of previous frames.
    const double delta_time =
        (uint32_t)enc->prev_timestamp_ - enc->first_timestamp_;
    const int average_duration = (int)(delta_time / (enc->in_frame_count_ - 1));
    if (!IncreasePreviousDuration(enc, average_duration)) {
      return 0;
    }
  }

  // Flush any remaining frames.
  enc->flush_count_ = enc->count_;
  if (!FlushFrames(enc)) {
    return 0;
  }

  // Set definitive canvas size.
  mux = enc->mux_;
  err = WebPMuxSetCanvasSize(mux, enc->canvas_width_, enc->canvas_height_);
  if (err != WEBP_MUX_OK) goto Err;

  err = WebPMuxSetAnimationParams(mux, &enc->options_.anim_params);
  if (err != WEBP_MUX_OK) goto Err;

  // Assemble into a WebP bitstream.
  err = WebPMuxAssemble(mux, webp_data);
  if (err != WEBP_MUX_OK) goto Err;

  if (enc->out_frame_count_ == 1) {
    err = OptimizeSingleFrame(enc, webp_data);
    if (err != WEBP_MUX_OK) goto Err;
  }
  return 1;

 Err:
  MarkError2(enc, "ERROR assembling WebP", err);
  return 0;
}