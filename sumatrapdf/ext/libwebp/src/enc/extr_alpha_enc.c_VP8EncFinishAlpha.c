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
typedef  int /*<<< orphan*/  WebPWorker ;
struct TYPE_4__ {scalar_t__ thread_level_; scalar_t__ percent_; int /*<<< orphan*/  pic_; int /*<<< orphan*/  alpha_worker_; scalar_t__ has_alpha_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_5__ {int /*<<< orphan*/  (* Sync ) (int /*<<< orphan*/ * const) ;} ;

/* Variables and functions */
 TYPE_2__* WebPGetWorkerInterface () ; 
 int WebPReportProgress (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ * const) ; 

int VP8EncFinishAlpha(VP8Encoder* const enc) {
  if (enc->has_alpha_) {
    if (enc->thread_level_ > 0) {
      WebPWorker* const worker = &enc->alpha_worker_;
      if (!WebPGetWorkerInterface()->Sync(worker)) return 0;  // error
    }
  }
  return WebPReportProgress(enc->pic_, enc->percent_ + 20, &enc->percent_);
}