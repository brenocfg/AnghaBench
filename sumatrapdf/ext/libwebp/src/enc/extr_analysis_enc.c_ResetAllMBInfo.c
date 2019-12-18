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
struct TYPE_5__ {int mb_w_; int mb_h_; scalar_t__ percent_; int /*<<< orphan*/  pic_; scalar_t__ uv_alpha_; scalar_t__ alpha_; TYPE_1__* dqm_; int /*<<< orphan*/ * mb_info_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_4__ {scalar_t__ beta_; scalar_t__ alpha_; } ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultMBInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPReportProgress (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void ResetAllMBInfo(VP8Encoder* const enc) {
  int n;
  for (n = 0; n < enc->mb_w_ * enc->mb_h_; ++n) {
    DefaultMBInfo(&enc->mb_info_[n]);
  }
  // Default susceptibilities.
  enc->dqm_[0].alpha_ = 0;
  enc->dqm_[0].beta_ = 0;
  // Note: we can't compute this alpha_ / uv_alpha_ -> set to default value.
  enc->alpha_ = 0;
  enc->uv_alpha_ = 0;
  WebPReportProgress(enc->pic_, enc->percent_ + 20, &enc->percent_);
}