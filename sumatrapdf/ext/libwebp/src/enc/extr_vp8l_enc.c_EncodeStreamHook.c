#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int width; int height; } ;
typedef  TYPE_1__ WebPPicture ;
typedef  scalar_t__ WebPEncodingError ;
struct TYPE_17__ {scalar_t__ method; int near_lossless; scalar_t__ quality; } ;
typedef  TYPE_2__ WebPConfig ;
struct TYPE_18__ {int lossless_features; int palette_size; int lossless_size; int lossless_hdr_size; int lossless_data_size; scalar_t__ cache_bits; int /*<<< orphan*/  transform_bits; int /*<<< orphan*/  histogram_bits; } ;
typedef  TYPE_3__ WebPAuxStats ;
struct TYPE_19__ {int use_palette_; int use_subtract_green_; int use_predict_; int use_cross_color_; scalar_t__ argb_content_; int palette_size_; scalar_t__ cache_bits_; int /*<<< orphan*/  transform_bits_; int /*<<< orphan*/  histo_bits_; int /*<<< orphan*/  current_width_; int /*<<< orphan*/ * refs_; int /*<<< orphan*/  hash_chain_; int /*<<< orphan*/  argb_; } ;
typedef  TYPE_4__ VP8LEncoder ;
typedef  int /*<<< orphan*/  VP8LBitWriter ;
struct TYPE_21__ {int entropy_idx_; } ;
struct TYPE_20__ {int use_cache_; int num_crunch_configs_; int red_and_blue_always_zero_; scalar_t__ err_; TYPE_3__* stats_; TYPE_6__* crunch_configs_; TYPE_4__* enc_; int /*<<< orphan*/ * bw_; TYPE_1__* picture_; TYPE_2__* config_; } ;
typedef  TYPE_5__ StreamEncodeContext ;
typedef  TYPE_6__ CrunchConfig ;

/* Variables and functions */
 scalar_t__ AllocateTransformBuffer (TYPE_4__* const,int const,int const) ; 
 scalar_t__ ApplyCrossColorFilter (TYPE_4__* const,int /*<<< orphan*/ ,int const,int const,int const,int /*<<< orphan*/ * const) ; 
 scalar_t__ ApplyPredictFilter (TYPE_4__* const,int /*<<< orphan*/ ,int const,int const,int const,int,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ApplySubtractGreen (TYPE_4__* const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ * const) ; 
 scalar_t__ BitsLog2Floor (int) ; 
 scalar_t__ EncodeImageInternal (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int const,int const,int const,TYPE_6__ const*,scalar_t__*,int /*<<< orphan*/ ,size_t const,int*,int*) ; 
 scalar_t__ EncodePalette (int /*<<< orphan*/ * const,int const,TYPE_4__* const) ; 
 int MAX_COLOR_CACHE_BITS ; 
 scalar_t__ MakeInputImageCopy (TYPE_4__* const) ; 
 scalar_t__ MapImageFromPalette (TYPE_4__* const,int) ; 
 int /*<<< orphan*/  TRANSFORM_PRESENT ; 
 int /*<<< orphan*/  VP8ApplyNearLossless (TYPE_1__ const* const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8LBackwardRefsClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LBitWriterClone (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LBitWriterInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t VP8LBitWriterNumBytes (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8LBitWriterReset (int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8LBitWriterSwap (int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8LBitWriterWipeOut (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LPutBits (int /*<<< orphan*/ * const,int,int) ; 
 scalar_t__ VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VP8_ENC_OK ; 
 scalar_t__ kEncoderNearLossless ; 
 void* kEncoderNone ; 
 scalar_t__ kEncoderPalette ; 
 int const kPalette ; 
 int const kSpatial ; 
 int const kSpatialSubGreen ; 
 int const kSubGreen ; 

__attribute__((used)) static int EncodeStreamHook(void* input, void* data2) {
  StreamEncodeContext* const params = (StreamEncodeContext*)input;
  const WebPConfig* const config = params->config_;
  const WebPPicture* const picture = params->picture_;
  VP8LBitWriter* const bw = params->bw_;
  VP8LEncoder* const enc = params->enc_;
  const int use_cache = params->use_cache_;
  const CrunchConfig* const crunch_configs = params->crunch_configs_;
  const int num_crunch_configs = params->num_crunch_configs_;
  const int red_and_blue_always_zero = params->red_and_blue_always_zero_;
#if !defined(WEBP_DISABLE_STATS)
  WebPAuxStats* const stats = params->stats_;
#endif
  WebPEncodingError err = VP8_ENC_OK;
  const int quality = (int)config->quality;
  const int low_effort = (config->method == 0);
#if (WEBP_NEAR_LOSSLESS == 1)
  const int width = picture->width;
#endif
  const int height = picture->height;
  const size_t byte_position = VP8LBitWriterNumBytes(bw);
#if (WEBP_NEAR_LOSSLESS == 1)
  int use_near_lossless = 0;
#endif
  int hdr_size = 0;
  int data_size = 0;
  int use_delta_palette = 0;
  int idx;
  size_t best_size = 0;
  VP8LBitWriter bw_init = *bw, bw_best;
  (void)data2;

  if (!VP8LBitWriterInit(&bw_best, 0) ||
      (num_crunch_configs > 1 && !VP8LBitWriterClone(bw, &bw_best))) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  for (idx = 0; idx < num_crunch_configs; ++idx) {
    const int entropy_idx = crunch_configs[idx].entropy_idx_;
    enc->use_palette_ = (entropy_idx == kPalette);
    enc->use_subtract_green_ =
        (entropy_idx == kSubGreen) || (entropy_idx == kSpatialSubGreen);
    enc->use_predict_ =
        (entropy_idx == kSpatial) || (entropy_idx == kSpatialSubGreen);
    if (low_effort) {
      enc->use_cross_color_ = 0;
    } else {
      enc->use_cross_color_ = red_and_blue_always_zero ? 0 : enc->use_predict_;
    }
    // Reset any parameter in the encoder that is set in the previous iteration.
    enc->cache_bits_ = 0;
    VP8LBackwardRefsClear(&enc->refs_[0]);
    VP8LBackwardRefsClear(&enc->refs_[1]);

#if (WEBP_NEAR_LOSSLESS == 1)
    // Apply near-lossless preprocessing.
    use_near_lossless = (config->near_lossless < 100) && !enc->use_palette_ &&
                        !enc->use_predict_;
    if (use_near_lossless) {
      err = AllocateTransformBuffer(enc, width, height);
      if (err != VP8_ENC_OK) goto Error;
      if ((enc->argb_content_ != kEncoderNearLossless) &&
          !VP8ApplyNearLossless(picture, config->near_lossless, enc->argb_)) {
        err = VP8_ENC_ERROR_OUT_OF_MEMORY;
        goto Error;
      }
      enc->argb_content_ = kEncoderNearLossless;
    } else {
      enc->argb_content_ = kEncoderNone;
    }
#else
    enc->argb_content_ = kEncoderNone;
#endif

    // Encode palette
    if (enc->use_palette_) {
      err = EncodePalette(bw, low_effort, enc);
      if (err != VP8_ENC_OK) goto Error;
      err = MapImageFromPalette(enc, use_delta_palette);
      if (err != VP8_ENC_OK) goto Error;
      // If using a color cache, do not have it bigger than the number of
      // colors.
      if (use_cache && enc->palette_size_ < (1 << MAX_COLOR_CACHE_BITS)) {
        enc->cache_bits_ = BitsLog2Floor(enc->palette_size_) + 1;
      }
    }
    if (!use_delta_palette) {
      // In case image is not packed.
      if (enc->argb_content_ != kEncoderNearLossless &&
          enc->argb_content_ != kEncoderPalette) {
        err = MakeInputImageCopy(enc);
        if (err != VP8_ENC_OK) goto Error;
      }

      // -----------------------------------------------------------------------
      // Apply transforms and write transform data.

      if (enc->use_subtract_green_) {
        ApplySubtractGreen(enc, enc->current_width_, height, bw);
      }

      if (enc->use_predict_) {
        err = ApplyPredictFilter(enc, enc->current_width_, height, quality,
                                 low_effort, enc->use_subtract_green_, bw);
        if (err != VP8_ENC_OK) goto Error;
      }

      if (enc->use_cross_color_) {
        err = ApplyCrossColorFilter(enc, enc->current_width_, height, quality,
                                    low_effort, bw);
        if (err != VP8_ENC_OK) goto Error;
      }
    }

    VP8LPutBits(bw, !TRANSFORM_PRESENT, 1);  // No more transforms.

    // -------------------------------------------------------------------------
    // Encode and write the transformed image.
    err = EncodeImageInternal(bw, enc->argb_, &enc->hash_chain_, enc->refs_,
                              enc->current_width_, height, quality, low_effort,
                              use_cache, &crunch_configs[idx],
                              &enc->cache_bits_, enc->histo_bits_,
                              byte_position, &hdr_size, &data_size);
    if (err != VP8_ENC_OK) goto Error;

    // If we are better than what we already have.
    if (idx == 0 || VP8LBitWriterNumBytes(bw) < best_size) {
      best_size = VP8LBitWriterNumBytes(bw);
      // Store the BitWriter.
      VP8LBitWriterSwap(bw, &bw_best);
#if !defined(WEBP_DISABLE_STATS)
      // Update the stats.
      if (stats != NULL) {
        stats->lossless_features = 0;
        if (enc->use_predict_) stats->lossless_features |= 1;
        if (enc->use_cross_color_) stats->lossless_features |= 2;
        if (enc->use_subtract_green_) stats->lossless_features |= 4;
        if (enc->use_palette_) stats->lossless_features |= 8;
        stats->histogram_bits = enc->histo_bits_;
        stats->transform_bits = enc->transform_bits_;
        stats->cache_bits = enc->cache_bits_;
        stats->palette_size = enc->palette_size_;
        stats->lossless_size = (int)(best_size - byte_position);
        stats->lossless_hdr_size = hdr_size;
        stats->lossless_data_size = data_size;
      }
#endif
    }
    // Reset the bit writer for the following iteration if any.
    if (num_crunch_configs > 1) VP8LBitWriterReset(&bw_init, bw);
  }
  VP8LBitWriterSwap(&bw_best, bw);

Error:
  VP8LBitWriterWipeOut(&bw_best);
  params->err_ = err;
  // The hook should return false in case of error.
  return (err == VP8_ENC_OK);
}