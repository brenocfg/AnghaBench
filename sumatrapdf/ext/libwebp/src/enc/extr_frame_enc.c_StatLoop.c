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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  VP8RDLevel ;
struct TYPE_13__ {int method_; int do_search_; int const percent_; int mb_w_; int mb_h_; int max_i4_header_bits_; int /*<<< orphan*/  pic_; int /*<<< orphan*/  proba_; TYPE_1__* config_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_14__ {int /*<<< orphan*/  do_size_search; int /*<<< orphan*/  dq; int /*<<< orphan*/  q; int /*<<< orphan*/  last_q; int /*<<< orphan*/  value; int /*<<< orphan*/  last_value; } ;
struct TYPE_12__ {int pass; } ;
typedef  TYPE_3__ PassStats ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeNextQ (TYPE_3__*) ; 
 scalar_t__ DQ_LIMIT ; 
 int /*<<< orphan*/  FinalizeSkipProba (TYPE_2__* const) ; 
 int /*<<< orphan*/  FinalizeTokenProbas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitPassStats (TYPE_2__* const,TYPE_3__*) ; 
 scalar_t__ OneStatPass (TYPE_2__* const,int /*<<< orphan*/  const,int,int const,TYPE_3__*) ; 
 scalar_t__ const PARTITION0_SIZE_LIMIT ; 
 int /*<<< orphan*/  RD_OPT_BASIC ; 
 int /*<<< orphan*/  RD_OPT_NONE ; 
 int /*<<< orphan*/  ResetTokenStats (TYPE_2__* const) ; 
 int /*<<< orphan*/  VP8CalculateLevelCosts (int /*<<< orphan*/ *) ; 
 int WebPReportProgress (int /*<<< orphan*/ ,int const,int const*) ; 
 scalar_t__ fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int StatLoop(VP8Encoder* const enc) {
  const int method = enc->method_;
  const int do_search = enc->do_search_;
  const int fast_probe = ((method == 0 || method == 3) && !do_search);
  int num_pass_left = enc->config_->pass;
  const int task_percent = 20;
  const int percent_per_pass =
      (task_percent + num_pass_left / 2) / num_pass_left;
  const int final_percent = enc->percent_ + task_percent;
  const VP8RDLevel rd_opt =
      (method >= 3 || do_search) ? RD_OPT_BASIC : RD_OPT_NONE;
  int nb_mbs = enc->mb_w_ * enc->mb_h_;
  PassStats stats;

  InitPassStats(enc, &stats);
  ResetTokenStats(enc);

  // Fast mode: quick analysis pass over few mbs. Better than nothing.
  if (fast_probe) {
    if (method == 3) {  // we need more stats for method 3 to be reliable.
      nb_mbs = (nb_mbs > 200) ? nb_mbs >> 1 : 100;
    } else {
      nb_mbs = (nb_mbs > 200) ? nb_mbs >> 2 : 50;
    }
  }

  while (num_pass_left-- > 0) {
    const int is_last_pass = (fabs(stats.dq) <= DQ_LIMIT) ||
                             (num_pass_left == 0) ||
                             (enc->max_i4_header_bits_ == 0);
    const uint64_t size_p0 =
        OneStatPass(enc, rd_opt, nb_mbs, percent_per_pass, &stats);
    if (size_p0 == 0) return 0;
#if (DEBUG_SEARCH > 0)
    printf("#%d value:%.1lf -> %.1lf   q:%.2f -> %.2f\n",
           num_pass_left, stats.last_value, stats.value, stats.last_q, stats.q);
#endif
    if (enc->max_i4_header_bits_ > 0 && size_p0 > PARTITION0_SIZE_LIMIT) {
      ++num_pass_left;
      enc->max_i4_header_bits_ >>= 1;  // strengthen header bit limitation...
      continue;                        // ...and start over
    }
    if (is_last_pass) {
      break;
    }
    // If no target size: just do several pass without changing 'q'
    if (do_search) {
      ComputeNextQ(&stats);
      if (fabs(stats.dq) <= DQ_LIMIT) break;
    }
  }
  if (!do_search || !stats.do_size_search) {
    // Need to finalize probas now, since it wasn't done during the search.
    FinalizeSkipProba(enc);
    FinalizeTokenProbas(&enc->proba_);
  }
  VP8CalculateLevelCosts(&enc->proba_);  // finalize costs
  return WebPReportProgress(enc->pic_, final_percent, &enc->percent_);
}