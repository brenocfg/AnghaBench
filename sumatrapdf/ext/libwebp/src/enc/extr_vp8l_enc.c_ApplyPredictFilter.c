#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPEncodingError ;
typedef  int /*<<< orphan*/  VP8LHashChain ;
struct TYPE_5__ {int transform_bits_; int /*<<< orphan*/ * refs_; int /*<<< orphan*/  hash_chain_; int /*<<< orphan*/  transform_data_; TYPE_1__* config_; int /*<<< orphan*/  argb_scratch_; int /*<<< orphan*/  argb_; scalar_t__ use_palette_; } ;
typedef  TYPE_2__ VP8LEncoder ;
typedef  int /*<<< orphan*/  VP8LBitWriter ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;
struct TYPE_4__ {int near_lossless; int /*<<< orphan*/  exact; } ;

/* Variables and functions */
 int /*<<< orphan*/  EncodeImageNoHuffman (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int const,int,int) ; 
 int const PREDICTOR_TRANSFORM ; 
 int const TRANSFORM_PRESENT ; 
 int /*<<< orphan*/  VP8LPutBits (int /*<<< orphan*/ * const,int const,int) ; 
 int /*<<< orphan*/  VP8LResidualImage (int,int,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int) ; 
 int VP8LSubSampleSize (int,int const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static WebPEncodingError ApplyPredictFilter(const VP8LEncoder* const enc,
                                            int width, int height,
                                            int quality, int low_effort,
                                            int used_subtract_green,
                                            VP8LBitWriter* const bw) {
  const int pred_bits = enc->transform_bits_;
  const int transform_width = VP8LSubSampleSize(width, pred_bits);
  const int transform_height = VP8LSubSampleSize(height, pred_bits);
  // we disable near-lossless quantization if palette is used.
  const int near_lossless_strength = enc->use_palette_ ? 100
                                   : enc->config_->near_lossless;

  VP8LResidualImage(width, height, pred_bits, low_effort, enc->argb_,
                    enc->argb_scratch_, enc->transform_data_,
                    near_lossless_strength, enc->config_->exact,
                    used_subtract_green);
  VP8LPutBits(bw, TRANSFORM_PRESENT, 1);
  VP8LPutBits(bw, PREDICTOR_TRANSFORM, 2);
  assert(pred_bits >= 2);
  VP8LPutBits(bw, pred_bits - 2, 3);
  return EncodeImageNoHuffman(
      bw, enc->transform_data_, (VP8LHashChain*)&enc->hash_chain_,
      (VP8LBackwardRefs*)&enc->refs_[0],  // cast const away
      (VP8LBackwardRefs*)&enc->refs_[1], transform_width, transform_height,
      quality, low_effort);
}