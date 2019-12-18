#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num_segments_; } ;
struct TYPE_12__ {int alpha_; int uv_alpha_; int dq_uv_dc_; int dq_uv_ac_; scalar_t__ dq_y2_ac_; scalar_t__ dq_y2_dc_; scalar_t__ dq_y1_dc_; TYPE_3__* config_; void* base_quant_; TYPE_2__* dqm_; TYPE_1__ segment_hdr_; } ;
typedef  TYPE_4__ VP8Encoder ;
struct TYPE_11__ {int sns_strength; scalar_t__ emulate_jpeg_size; } ;
struct TYPE_10__ {double const alpha_; void* quant_; } ;

/* Variables and functions */
 int MAX_ALPHA ; 
 int MAX_DQ_UV ; 
 int MID_ALPHA ; 
 int MIN_ALPHA ; 
 int MIN_DQ_UV ; 
 int NUM_MB_SEGMENTS ; 
 double QualityToCompression (double const) ; 
 double QualityToJPEGCompression (double const,int) ; 
 int SNS_TO_DQ ; 
 int /*<<< orphan*/  SetupFilterStrength (TYPE_4__* const) ; 
 int /*<<< orphan*/  SetupMatrices (TYPE_4__* const) ; 
 int /*<<< orphan*/  SimplifySegments (TYPE_4__* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* clip (int const,int,int) ; 
 double pow (double const,double const) ; 

void VP8SetSegmentParams(VP8Encoder* const enc, float quality) {
  int i;
  int dq_uv_ac, dq_uv_dc;
  const int num_segments = enc->segment_hdr_.num_segments_;
  const double amp = SNS_TO_DQ * enc->config_->sns_strength / 100. / 128.;
  const double Q = quality / 100.;
  const double c_base = enc->config_->emulate_jpeg_size ?
      QualityToJPEGCompression(Q, enc->alpha_ / 255.) :
      QualityToCompression(Q);
  for (i = 0; i < num_segments; ++i) {
    // We modulate the base coefficient to accommodate for the quantization
    // susceptibility and allow denser segments to be quantized more.
    const double expn = 1. - amp * enc->dqm_[i].alpha_;
    const double c = pow(c_base, expn);
    const int q = (int)(127. * (1. - c));
    assert(expn > 0.);
    enc->dqm_[i].quant_ = clip(q, 0, 127);
  }

  // purely indicative in the bitstream (except for the 1-segment case)
  enc->base_quant_ = enc->dqm_[0].quant_;

  // fill-in values for the unused segments (required by the syntax)
  for (i = num_segments; i < NUM_MB_SEGMENTS; ++i) {
    enc->dqm_[i].quant_ = enc->base_quant_;
  }

  // uv_alpha_ is normally spread around ~60. The useful range is
  // typically ~30 (quite bad) to ~100 (ok to decimate UV more).
  // We map it to the safe maximal range of MAX/MIN_DQ_UV for dq_uv.
  dq_uv_ac = (enc->uv_alpha_ - MID_ALPHA) * (MAX_DQ_UV - MIN_DQ_UV)
                                          / (MAX_ALPHA - MIN_ALPHA);
  // we rescale by the user-defined strength of adaptation
  dq_uv_ac = dq_uv_ac * enc->config_->sns_strength / 100;
  // and make it safe.
  dq_uv_ac = clip(dq_uv_ac, MIN_DQ_UV, MAX_DQ_UV);
  // We also boost the dc-uv-quant a little, based on sns-strength, since
  // U/V channels are quite more reactive to high quants (flat DC-blocks
  // tend to appear, and are unpleasant).
  dq_uv_dc = -4 * enc->config_->sns_strength / 100;
  dq_uv_dc = clip(dq_uv_dc, -15, 15);   // 4bit-signed max allowed

  enc->dq_y1_dc_ = 0;       // TODO(skal): dq-lum
  enc->dq_y2_dc_ = 0;
  enc->dq_y2_ac_ = 0;
  enc->dq_uv_dc_ = dq_uv_dc;
  enc->dq_uv_ac_ = dq_uv_ac;

  SetupFilterStrength(enc);   // initialize segments' filtering, eventually

  if (num_segments > 1) SimplifySegments(enc);

  SetupMatrices(enc);         // finalize quantization matrices
}