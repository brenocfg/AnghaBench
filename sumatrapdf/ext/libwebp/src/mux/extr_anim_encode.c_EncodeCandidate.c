#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_2__ WebPPicture ;
typedef  int /*<<< orphan*/  WebPEncodingError ;
struct TYPE_15__ {scalar_t__ filter_strength; scalar_t__ autofilter; int /*<<< orphan*/  lossless; } ;
typedef  TYPE_3__ WebPConfig ;
struct TYPE_13__ {scalar_t__ duration; int /*<<< orphan*/  blend_method; int /*<<< orphan*/  dispose_method; int /*<<< orphan*/  y_offset; int /*<<< orphan*/  x_offset; int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int /*<<< orphan*/  y_offset_; int /*<<< orphan*/  x_offset_; } ;
struct TYPE_17__ {int evaluate_; int /*<<< orphan*/  mem_; TYPE_1__ info_; TYPE_4__ rect_; } ;
typedef  TYPE_4__ FrameRectangle ;
typedef  TYPE_5__ Candidate ;

/* Variables and functions */
 int /*<<< orphan*/  EncodeFrame (TYPE_3__*,TYPE_2__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8_ENC_OK ; 
 int /*<<< orphan*/  WEBP_CHUNK_ANMF ; 
 int /*<<< orphan*/  WEBP_MUX_BLEND ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_NONE ; 
 int /*<<< orphan*/  WEBP_MUX_NO_BLEND ; 
 int /*<<< orphan*/  WebPMemoryWriterClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPMemoryWriterInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static WebPEncodingError EncodeCandidate(WebPPicture* const sub_frame,
                                         const FrameRectangle* const rect,
                                         const WebPConfig* const encoder_config,
                                         int use_blending,
                                         Candidate* const candidate) {
  WebPConfig config = *encoder_config;
  WebPEncodingError error_code = VP8_ENC_OK;
  assert(candidate != NULL);
  memset(candidate, 0, sizeof(*candidate));

  // Set frame rect and info.
  candidate->rect_ = *rect;
  candidate->info_.id = WEBP_CHUNK_ANMF;
  candidate->info_.x_offset = rect->x_offset_;
  candidate->info_.y_offset = rect->y_offset_;
  candidate->info_.dispose_method = WEBP_MUX_DISPOSE_NONE;  // Set later.
  candidate->info_.blend_method =
      use_blending ? WEBP_MUX_BLEND : WEBP_MUX_NO_BLEND;
  candidate->info_.duration = 0;  // Set in next call to WebPAnimEncoderAdd().

  // Encode picture.
  WebPMemoryWriterInit(&candidate->mem_);

  if (!config.lossless && use_blending) {
    // Disable filtering to avoid blockiness in reconstructed frames at the
    // time of decoding.
    config.autofilter = 0;
    config.filter_strength = 0;
  }
  if (!EncodeFrame(&config, sub_frame, &candidate->mem_)) {
    error_code = sub_frame->error_code;
    goto Err;
  }

  candidate->evaluate_ = 1;
  return error_code;

 Err:
  WebPMemoryWriterClear(&candidate->mem_);
  return error_code;
}