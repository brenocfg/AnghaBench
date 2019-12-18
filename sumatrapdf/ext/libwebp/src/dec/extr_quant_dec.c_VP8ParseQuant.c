#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* quantizer_; int /*<<< orphan*/  absolute_delta_; scalar_t__ use_segment_; } ;
typedef  TYPE_1__ VP8SegmentHeader ;
struct TYPE_6__ {int* y1_mat_; int* y2_mat_; int* uv_mat_; int uv_quant_; } ;
typedef  TYPE_2__ VP8QuantMatrix ;
struct TYPE_7__ {TYPE_2__* dqm_; TYPE_1__ segment_hdr_; int /*<<< orphan*/  br_; } ;
typedef  TYPE_3__ VP8Decoder ;
typedef  int /*<<< orphan*/  VP8BitReader ;

/* Variables and functions */
 int NUM_MB_SEGMENTS ; 
 scalar_t__ VP8Get (int /*<<< orphan*/ * const,char*) ; 
 int VP8GetSignedValue (int /*<<< orphan*/ * const,int,char*) ; 
 int VP8GetValue (int /*<<< orphan*/ * const,int,char*) ; 
 size_t clip (int,int) ; 
 int* kAcTable ; 
 int* kDcTable ; 

void VP8ParseQuant(VP8Decoder* const dec) {
  VP8BitReader* const br = &dec->br_;
  const int base_q0 = VP8GetValue(br, 7, "global-header");
  const int dqy1_dc = VP8Get(br, "global-header") ?
       VP8GetSignedValue(br, 4, "global-header") : 0;
  const int dqy2_dc = VP8Get(br, "global-header") ?
       VP8GetSignedValue(br, 4, "global-header") : 0;
  const int dqy2_ac = VP8Get(br, "global-header") ?
       VP8GetSignedValue(br, 4, "global-header") : 0;
  const int dquv_dc = VP8Get(br, "global-header") ?
       VP8GetSignedValue(br, 4, "global-header") : 0;
  const int dquv_ac = VP8Get(br, "global-header") ?
       VP8GetSignedValue(br, 4, "global-header") : 0;

  const VP8SegmentHeader* const hdr = &dec->segment_hdr_;
  int i;

  for (i = 0; i < NUM_MB_SEGMENTS; ++i) {
    int q;
    if (hdr->use_segment_) {
      q = hdr->quantizer_[i];
      if (!hdr->absolute_delta_) {
        q += base_q0;
      }
    } else {
      if (i > 0) {
        dec->dqm_[i] = dec->dqm_[0];
        continue;
      } else {
        q = base_q0;
      }
    }
    {
      VP8QuantMatrix* const m = &dec->dqm_[i];
      m->y1_mat_[0] = kDcTable[clip(q + dqy1_dc, 127)];
      m->y1_mat_[1] = kAcTable[clip(q + 0,       127)];

      m->y2_mat_[0] = kDcTable[clip(q + dqy2_dc, 127)] * 2;
      // For all x in [0..284], x*155/100 is bitwise equal to (x*101581) >> 16.
      // The smallest precision for that is '(x*6349) >> 12' but 16 is a good
      // word size.
      m->y2_mat_[1] = (kAcTable[clip(q + dqy2_ac, 127)] * 101581) >> 16;
      if (m->y2_mat_[1] < 8) m->y2_mat_[1] = 8;

      m->uv_mat_[0] = kDcTable[clip(q + dquv_dc, 117)];
      m->uv_mat_[1] = kAcTable[clip(q + dquv_ac, 127)];

      m->uv_quant_ = q + dquv_ac;   // for dithering strength evaluation
    }
  }
}