#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  WebPAnimEncoderOptions ;
struct TYPE_12__ {int kmax; int kmin; } ;
struct TYPE_14__ {int width; int height; int use_argb; } ;
struct TYPE_13__ {int curr_canvas_copy_modified_; int size_; int is_first_frame_; scalar_t__ got_null_frame_; scalar_t__ prev_candidate_undecided_; scalar_t__ prev_timestamp_; scalar_t__ first_timestamp_; scalar_t__ count_since_key_frame_; int /*<<< orphan*/ * mux_; int /*<<< orphan*/ * encoded_frames_; TYPE_1__ options_; TYPE_3__ prev_canvas_; TYPE_3__ prev_canvas_disposed_; TYPE_3__ curr_canvas_copy_; int /*<<< orphan*/  canvas_height_; int /*<<< orphan*/  canvas_width_; } ;
typedef  TYPE_2__ WebPAnimEncoder ;
typedef  int /*<<< orphan*/  EncodedFrame ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultEncoderOptions (int /*<<< orphan*/ *) ; 
 int MAX_IMAGE_AREA ; 
 int /*<<< orphan*/  MarkNoError (TYPE_2__*) ; 
 int /*<<< orphan*/  ResetCounters (TYPE_2__*) ; 
 int /*<<< orphan*/  SanitizeEncoderOptions (int /*<<< orphan*/ *) ; 
 scalar_t__ WEBP_ABI_IS_INCOMPATIBLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_MUX_ABI_VERSION ; 
 int /*<<< orphan*/  WebPAnimEncoderDelete (TYPE_2__*) ; 
 int /*<<< orphan*/ * WebPMuxNew () ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_3__*) ; 
 int /*<<< orphan*/  WebPPictureCopy (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  WebPPictureInit (TYPE_3__*) ; 
 scalar_t__ WebPSafeCalloc (int,int) ; 
 int /*<<< orphan*/  WebPUtilClearPic (TYPE_3__*,int /*<<< orphan*/ *) ; 

WebPAnimEncoder* WebPAnimEncoderNewInternal(
    int width, int height, const WebPAnimEncoderOptions* enc_options,
    int abi_version) {
  WebPAnimEncoder* enc;

  if (WEBP_ABI_IS_INCOMPATIBLE(abi_version, WEBP_MUX_ABI_VERSION)) {
    return NULL;
  }
  if (width <= 0 || height <= 0 ||
      (width * (uint64_t)height) >= MAX_IMAGE_AREA) {
    return NULL;
  }

  enc = (WebPAnimEncoder*)WebPSafeCalloc(1, sizeof(*enc));
  if (enc == NULL) return NULL;
  // sanity inits, so we can call WebPAnimEncoderDelete():
  enc->encoded_frames_ = NULL;
  enc->mux_ = NULL;
  MarkNoError(enc);

  // Dimensions and options.
  *(int*)&enc->canvas_width_ = width;
  *(int*)&enc->canvas_height_ = height;
  if (enc_options != NULL) {
    *(WebPAnimEncoderOptions*)&enc->options_ = *enc_options;
    SanitizeEncoderOptions((WebPAnimEncoderOptions*)&enc->options_);
  } else {
    DefaultEncoderOptions((WebPAnimEncoderOptions*)&enc->options_);
  }

  // Canvas buffers.
  if (!WebPPictureInit(&enc->curr_canvas_copy_) ||
      !WebPPictureInit(&enc->prev_canvas_) ||
      !WebPPictureInit(&enc->prev_canvas_disposed_)) {
    goto Err;
  }
  enc->curr_canvas_copy_.width = width;
  enc->curr_canvas_copy_.height = height;
  enc->curr_canvas_copy_.use_argb = 1;
  if (!WebPPictureAlloc(&enc->curr_canvas_copy_) ||
      !WebPPictureCopy(&enc->curr_canvas_copy_, &enc->prev_canvas_) ||
      !WebPPictureCopy(&enc->curr_canvas_copy_, &enc->prev_canvas_disposed_)) {
    goto Err;
  }
  WebPUtilClearPic(&enc->prev_canvas_, NULL);
  enc->curr_canvas_copy_modified_ = 1;

  // Encoded frames.
  ResetCounters(enc);
  // Note: one extra storage is for the previous frame.
  enc->size_ = enc->options_.kmax - enc->options_.kmin + 1;
  // We need space for at least 2 frames. But when kmin, kmax are both zero,
  // enc->size_ will be 1. So we handle that special case below.
  if (enc->size_ < 2) enc->size_ = 2;
  enc->encoded_frames_ =
      (EncodedFrame*)WebPSafeCalloc(enc->size_, sizeof(*enc->encoded_frames_));
  if (enc->encoded_frames_ == NULL) goto Err;

  enc->mux_ = WebPMuxNew();
  if (enc->mux_ == NULL) goto Err;

  enc->count_since_key_frame_ = 0;
  enc->first_timestamp_ = 0;
  enc->prev_timestamp_ = 0;
  enc->prev_candidate_undecided_ = 0;
  enc->is_first_frame_ = 1;
  enc->got_null_frame_ = 0;

  return enc;  // All OK.

 Err:
  WebPAnimEncoderDelete(enc);
  return NULL;
}