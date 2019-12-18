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
struct TYPE_8__ {int /*<<< orphan*/ * block_count; int /*<<< orphan*/  coded_size; int /*<<< orphan*/ ** residual_bytes; int /*<<< orphan*/ * segment_quant; int /*<<< orphan*/ * segment_level; } ;
typedef  TYPE_2__ WebPAuxStats ;
struct TYPE_9__ {int /*<<< orphan*/  percent_; TYPE_4__* pic_; int /*<<< orphan*/ * block_count_; int /*<<< orphan*/  coded_size_; int /*<<< orphan*/ ** residual_bytes_; TYPE_1__* dqm_; } ;
typedef  TYPE_3__ VP8Encoder ;
struct TYPE_10__ {TYPE_2__* stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  quant_; int /*<<< orphan*/  fstrength_; } ;

/* Variables and functions */
 int /*<<< orphan*/  FinalizePSNR (TYPE_3__* const) ; 
 int NUM_MB_SEGMENTS ; 
 int /*<<< orphan*/  WebPReportProgress (TYPE_4__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void StoreStats(VP8Encoder* const enc) {
#if !defined(WEBP_DISABLE_STATS)
  WebPAuxStats* const stats = enc->pic_->stats;
  if (stats != NULL) {
    int i, s;
    for (i = 0; i < NUM_MB_SEGMENTS; ++i) {
      stats->segment_level[i] = enc->dqm_[i].fstrength_;
      stats->segment_quant[i] = enc->dqm_[i].quant_;
      for (s = 0; s <= 2; ++s) {
        stats->residual_bytes[s][i] = enc->residual_bytes_[s][i];
      }
    }
    FinalizePSNR(enc);
    stats->coded_size = enc->coded_size_;
    for (i = 0; i < 3; ++i) {
      stats->block_count[i] = enc->block_count_[i];
    }
  }
#else  // defined(WEBP_DISABLE_STATS)
  WebPReportProgress(enc->pic_, 100, &enc->percent_);  // done!
#endif  // !defined(WEBP_DISABLE_STATS)
}