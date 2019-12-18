#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  candidates ;
typedef  int /*<<< orphan*/  const WebPPicture ;
typedef  scalar_t__ WebPEncodingError ;
struct TYPE_20__ {int lossless; int /*<<< orphan*/  quality; } ;
typedef  TYPE_2__ WebPConfig ;
struct TYPE_19__ {scalar_t__ minimize_size; scalar_t__ allow_mixed; } ;
struct TYPE_21__ {int is_first_frame_; TYPE_1__ options_; int /*<<< orphan*/  prev_rect_; int /*<<< orphan*/  const prev_canvas_disposed_; TYPE_2__ last_config_reversed_; TYPE_2__ last_config_; int /*<<< orphan*/  prev_candidate_undecided_; int /*<<< orphan*/  const prev_canvas_; int /*<<< orphan*/  const curr_canvas_copy_; } ;
typedef  TYPE_3__ WebPAnimEncoder ;
struct TYPE_23__ {int /*<<< orphan*/  mem_; scalar_t__ evaluate_; } ;
struct TYPE_22__ {int should_try_; int /*<<< orphan*/  rect_lossy_; int /*<<< orphan*/  rect_ll_; } ;
typedef  TYPE_4__ SubFrameParams ;
typedef  int /*<<< orphan*/  EncodedFrame ;
typedef  TYPE_5__ Candidate ;

/* Variables and functions */
 int CANDIDATE_COUNT ; 
 int /*<<< orphan*/  DisposeFrameRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 scalar_t__ GenerateCandidates (TYPE_3__* const,TYPE_5__*,int /*<<< orphan*/ ,int const,int,TYPE_4__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  GetSubRects (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int,int const,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ IsEmptyRect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PickBestCandidate (TYPE_3__* const,TYPE_5__*,int,int /*<<< orphan*/ * const) ; 
 scalar_t__ RectArea (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SubFrameParamsFree (TYPE_4__*) ; 
 int /*<<< orphan*/  SubFrameParamsInit (TYPE_4__*,int,int const) ; 
 scalar_t__ VP8_ENC_ERROR_INVALID_CONFIGURATION ; 
 scalar_t__ VP8_ENC_OK ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_BACKGROUND ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_NONE ; 
 int /*<<< orphan*/  WebPCopyPixels (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  WebPMemoryWriterClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int const) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static WebPEncodingError SetFrame(WebPAnimEncoder* const enc,
                                  const WebPConfig* const config,
                                  int is_key_frame,
                                  EncodedFrame* const encoded_frame,
                                  int* const frame_skipped) {
  int i;
  WebPEncodingError error_code = VP8_ENC_OK;
  const WebPPicture* const curr_canvas = &enc->curr_canvas_copy_;
  const WebPPicture* const prev_canvas = &enc->prev_canvas_;
  Candidate candidates[CANDIDATE_COUNT];
  const int is_lossless = config->lossless;
  const int consider_lossless = is_lossless || enc->options_.allow_mixed;
  const int consider_lossy = !is_lossless || enc->options_.allow_mixed;
  const int is_first_frame = enc->is_first_frame_;

  // First frame cannot be skipped as there is no 'previous frame' to merge it
  // to. So, empty rectangle is not allowed for the first frame.
  const int empty_rect_allowed_none = !is_first_frame;

  // Even if there is exact pixel match between 'disposed previous canvas' and
  // 'current canvas', we can't skip current frame, as there may not be exact
  // pixel match between 'previous canvas' and 'current canvas'. So, we don't
  // allow empty rectangle in this case.
  const int empty_rect_allowed_bg = 0;

  // If current frame is a key-frame, dispose method of previous frame doesn't
  // matter, so we don't try dispose to background.
  // Also, if key-frame insertion is on, and previous frame could be picked as
  // either a sub-frame or a key-frame, then we can't be sure about what frame
  // rectangle would be disposed. In that case too, we don't try dispose to
  // background.
  const int dispose_bg_possible =
      !is_key_frame && !enc->prev_candidate_undecided_;

  SubFrameParams dispose_none_params;
  SubFrameParams dispose_bg_params;

  WebPConfig config_ll = *config;
  WebPConfig config_lossy = *config;
  config_ll.lossless = 1;
  config_lossy.lossless = 0;
  enc->last_config_ = *config;
  enc->last_config_reversed_ = config->lossless ? config_lossy : config_ll;
  *frame_skipped = 0;

  if (!SubFrameParamsInit(&dispose_none_params, 1, empty_rect_allowed_none) ||
      !SubFrameParamsInit(&dispose_bg_params, 0, empty_rect_allowed_bg)) {
    return VP8_ENC_ERROR_INVALID_CONFIGURATION;
  }

  memset(candidates, 0, sizeof(candidates));

  // Change-rectangle assuming previous frame was DISPOSE_NONE.
  if (!GetSubRects(prev_canvas, curr_canvas, is_key_frame, is_first_frame,
                   config_lossy.quality, &dispose_none_params)) {
    error_code = VP8_ENC_ERROR_INVALID_CONFIGURATION;
    goto Err;
  }

  if ((consider_lossless && IsEmptyRect(&dispose_none_params.rect_ll_)) ||
      (consider_lossy && IsEmptyRect(&dispose_none_params.rect_lossy_))) {
    // Don't encode the frame at all. Instead, the duration of the previous
    // frame will be increased later.
    assert(empty_rect_allowed_none);
    *frame_skipped = 1;
    goto End;
  }

  if (dispose_bg_possible) {
    // Change-rectangle assuming previous frame was DISPOSE_BACKGROUND.
    WebPPicture* const prev_canvas_disposed = &enc->prev_canvas_disposed_;
    WebPCopyPixels(prev_canvas, prev_canvas_disposed);
    DisposeFrameRectangle(WEBP_MUX_DISPOSE_BACKGROUND, &enc->prev_rect_,
                          prev_canvas_disposed);

    if (!GetSubRects(prev_canvas_disposed, curr_canvas, is_key_frame,
                     is_first_frame, config_lossy.quality,
                     &dispose_bg_params)) {
      error_code = VP8_ENC_ERROR_INVALID_CONFIGURATION;
      goto Err;
    }
    assert(!IsEmptyRect(&dispose_bg_params.rect_ll_));
    assert(!IsEmptyRect(&dispose_bg_params.rect_lossy_));

    if (enc->options_.minimize_size) {  // Try both dispose methods.
      dispose_bg_params.should_try_ = 1;
      dispose_none_params.should_try_ = 1;
    } else if ((is_lossless &&
                RectArea(&dispose_bg_params.rect_ll_) <
                    RectArea(&dispose_none_params.rect_ll_)) ||
               (!is_lossless &&
                RectArea(&dispose_bg_params.rect_lossy_) <
                    RectArea(&dispose_none_params.rect_lossy_))) {
      dispose_bg_params.should_try_ = 1;  // Pick DISPOSE_BACKGROUND.
      dispose_none_params.should_try_ = 0;
    }
  }

  if (dispose_none_params.should_try_) {
    error_code = GenerateCandidates(
        enc, candidates, WEBP_MUX_DISPOSE_NONE, is_lossless, is_key_frame,
        &dispose_none_params, &config_ll, &config_lossy);
    if (error_code != VP8_ENC_OK) goto Err;
  }

  if (dispose_bg_params.should_try_) {
    assert(!enc->is_first_frame_);
    assert(dispose_bg_possible);
    error_code = GenerateCandidates(
        enc, candidates, WEBP_MUX_DISPOSE_BACKGROUND, is_lossless, is_key_frame,
        &dispose_bg_params, &config_ll, &config_lossy);
    if (error_code != VP8_ENC_OK) goto Err;
  }

  PickBestCandidate(enc, candidates, is_key_frame, encoded_frame);

  goto End;

 Err:
  for (i = 0; i < CANDIDATE_COUNT; ++i) {
    if (candidates[i].evaluate_) {
      WebPMemoryWriterClear(&candidates[i].mem_);
    }
  }

 End:
  SubFrameParamsFree(&dispose_none_params);
  SubFrameParamsFree(&dispose_bg_params);
  return error_code;
}