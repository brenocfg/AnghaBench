#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* q_; } ;
struct TYPE_11__ {int fstrength_; int max_edge_; TYPE_2__ y2_; } ;
typedef  TYPE_4__ VP8SegmentInfo ;
struct TYPE_10__ {int level_; int /*<<< orphan*/  sharpness_; } ;
struct TYPE_12__ {TYPE_3__ filter_hdr_; TYPE_4__* dqm_; TYPE_1__* config_; } ;
typedef  TYPE_5__ VP8Encoder ;
struct TYPE_13__ {double*** lf_stats_; TYPE_5__* enc_; } ;
typedef  TYPE_6__ VP8EncIterator ;
struct TYPE_8__ {scalar_t__ filter_strength; } ;

/* Variables and functions */
 int MAX_LF_LEVELS ; 
 int NUM_MB_SEGMENTS ; 
 int VP8FilterStrengthFromDelta (int /*<<< orphan*/ ,int const) ; 

void VP8AdjustFilterStrength(VP8EncIterator* const it) {
  VP8Encoder* const enc = it->enc_;
#if !defined(WEBP_REDUCE_SIZE)
  if (it->lf_stats_ != NULL) {
    int s;
    for (s = 0; s < NUM_MB_SEGMENTS; s++) {
      int i, best_level = 0;
      // Improvement over filter level 0 should be at least 1e-5 (relatively)
      double best_v = 1.00001 * (*it->lf_stats_)[s][0];
      for (i = 1; i < MAX_LF_LEVELS; i++) {
        const double v = (*it->lf_stats_)[s][i];
        if (v > best_v) {
          best_v = v;
          best_level = i;
        }
      }
      enc->dqm_[s].fstrength_ = best_level;
    }
    return;
  }
#endif  // !defined(WEBP_REDUCE_SIZE)
  if (enc->config_->filter_strength > 0) {
    int max_level = 0;
    int s;
    for (s = 0; s < NUM_MB_SEGMENTS; s++) {
      VP8SegmentInfo* const dqm = &enc->dqm_[s];
      // this '>> 3' accounts for some inverse WHT scaling
      const int delta = (dqm->max_edge_ * dqm->y2_.q_[1]) >> 3;
      const int level =
          VP8FilterStrengthFromDelta(enc->filter_hdr_.sharpness_, delta);
      if (level > dqm->fstrength_) {
        dqm->fstrength_ = level;
      }
      if (max_level < dqm->fstrength_) {
        max_level = dqm->fstrength_;
      }
    }
    enc->filter_hdr_.level_ = max_level;
  }
}