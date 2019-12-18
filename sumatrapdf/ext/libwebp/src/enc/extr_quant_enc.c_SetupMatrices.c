#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* q_; } ;
struct TYPE_9__ {int quant_; int lambda_i4_; int lambda_i16_; int lambda_uv_; int lambda_mode_; int lambda_trellis_i4_; int lambda_trellis_i16_; int lambda_trellis_uv_; int tlambda_; int min_disto_; int i4_penalty_; scalar_t__ max_edge_; TYPE_6__ y1_; TYPE_6__ uv_; TYPE_6__ y2_; } ;
typedef  TYPE_3__ VP8SegmentInfo ;
struct TYPE_8__ {int num_segments_; } ;
struct TYPE_10__ {int method_; int const dq_y1_dc_; int const dq_y2_dc_; int const dq_y2_ac_; int const dq_uv_dc_; int const dq_uv_ac_; TYPE_3__* dqm_; TYPE_2__ segment_hdr_; TYPE_1__* config_; } ;
typedef  TYPE_4__ VP8Encoder ;
struct TYPE_7__ {int sns_strength; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckLambdaValue (int*) ; 
 int ExpandMatrix (TYPE_6__*,int) ; 
 size_t clip (int const,int /*<<< orphan*/ ,int) ; 
 void** kAcTable ; 
 int* kAcTable2 ; 
 int* kDcTable ; 

__attribute__((used)) static void SetupMatrices(VP8Encoder* enc) {
  int i;
  const int tlambda_scale =
    (enc->method_ >= 4) ? enc->config_->sns_strength
                        : 0;
  const int num_segments = enc->segment_hdr_.num_segments_;
  for (i = 0; i < num_segments; ++i) {
    VP8SegmentInfo* const m = &enc->dqm_[i];
    const int q = m->quant_;
    int q_i4, q_i16, q_uv;
    m->y1_.q_[0] = kDcTable[clip(q + enc->dq_y1_dc_, 0, 127)];
    m->y1_.q_[1] = kAcTable[clip(q,                  0, 127)];

    m->y2_.q_[0] = kDcTable[ clip(q + enc->dq_y2_dc_, 0, 127)] * 2;
    m->y2_.q_[1] = kAcTable2[clip(q + enc->dq_y2_ac_, 0, 127)];

    m->uv_.q_[0] = kDcTable[clip(q + enc->dq_uv_dc_, 0, 117)];
    m->uv_.q_[1] = kAcTable[clip(q + enc->dq_uv_ac_, 0, 127)];

    q_i4  = ExpandMatrix(&m->y1_, 0);
    q_i16 = ExpandMatrix(&m->y2_, 1);
    q_uv  = ExpandMatrix(&m->uv_, 2);

    m->lambda_i4_          = (3 * q_i4 * q_i4) >> 7;
    m->lambda_i16_         = (3 * q_i16 * q_i16);
    m->lambda_uv_          = (3 * q_uv * q_uv) >> 6;
    m->lambda_mode_        = (1 * q_i4 * q_i4) >> 7;
    m->lambda_trellis_i4_  = (7 * q_i4 * q_i4) >> 3;
    m->lambda_trellis_i16_ = (q_i16 * q_i16) >> 2;
    m->lambda_trellis_uv_  = (q_uv * q_uv) << 1;
    m->tlambda_            = (tlambda_scale * q_i4) >> 5;

    // none of these constants should be < 1
    CheckLambdaValue(&m->lambda_i4_);
    CheckLambdaValue(&m->lambda_i16_);
    CheckLambdaValue(&m->lambda_uv_);
    CheckLambdaValue(&m->lambda_mode_);
    CheckLambdaValue(&m->lambda_trellis_i4_);
    CheckLambdaValue(&m->lambda_trellis_i16_);
    CheckLambdaValue(&m->lambda_trellis_uv_);
    CheckLambdaValue(&m->tlambda_);

    m->min_disto_ = 20 * m->y1_.q_[0];   // quantization-aware min disto
    m->max_edge_  = 0;

    m->i4_penalty_ = 1000 * q_i4 * q_i4;
  }
}