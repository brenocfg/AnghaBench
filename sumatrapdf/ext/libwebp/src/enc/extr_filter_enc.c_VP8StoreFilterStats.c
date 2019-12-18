#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* dqm_; } ;
typedef  TYPE_3__ VP8Encoder ;
struct TYPE_10__ {int /*<<< orphan*/  yuv_out2_; int /*<<< orphan*/  yuv_in_; int /*<<< orphan*/ *** lf_stats_; int /*<<< orphan*/  yuv_out_; TYPE_2__* mb_; TYPE_3__* enc_; } ;
typedef  TYPE_4__ VP8EncIterator ;
struct TYPE_8__ {int segment_; int type_; scalar_t__ skip_; } ;
struct TYPE_7__ {int fstrength_; int quant_; } ;

/* Variables and functions */
 int /*<<< orphan*/  DoFilter (TYPE_4__* const,int const) ; 
 scalar_t__ GetMBSSIM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const MAX_LF_LEVELS ; 

void VP8StoreFilterStats(VP8EncIterator* const it) {
#if !defined(WEBP_REDUCE_SIZE)
  int d;
  VP8Encoder* const enc = it->enc_;
  const int s = it->mb_->segment_;
  const int level0 = enc->dqm_[s].fstrength_;

  // explore +/-quant range of values around level0
  const int delta_min = -enc->dqm_[s].quant_;
  const int delta_max = enc->dqm_[s].quant_;
  const int step_size = (delta_max - delta_min >= 4) ? 4 : 1;

  if (it->lf_stats_ == NULL) return;

  // NOTE: Currently we are applying filter only across the sublock edges
  // There are two reasons for that.
  // 1. Applying filter on macro block edges will change the pixels in
  // the left and top macro blocks. That will be hard to restore
  // 2. Macro Blocks on the bottom and right are not yet compressed. So we
  // cannot apply filter on the right and bottom macro block edges.
  if (it->mb_->type_ == 1 && it->mb_->skip_) return;

  // Always try filter level  zero
  (*it->lf_stats_)[s][0] += GetMBSSIM(it->yuv_in_, it->yuv_out_);

  for (d = delta_min; d <= delta_max; d += step_size) {
    const int level = level0 + d;
    if (level <= 0 || level >= MAX_LF_LEVELS) {
      continue;
    }
    DoFilter(it, level);
    (*it->lf_stats_)[s][level] += GetMBSSIM(it->yuv_in_, it->yuv_out2_);
  }
#else  // defined(WEBP_REDUCE_SIZE)
  (void)it;
#endif  // !defined(WEBP_REDUCE_SIZE)
}