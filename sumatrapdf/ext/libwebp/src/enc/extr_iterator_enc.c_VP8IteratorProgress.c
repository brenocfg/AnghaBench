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
struct TYPE_5__ {int /*<<< orphan*/  percent_; TYPE_3__* pic_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_6__ {int count_down0_; int count_down_; int percent0_; TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;
struct TYPE_7__ {int /*<<< orphan*/ * progress_hook; } ;

/* Variables and functions */
 int WebPReportProgress (TYPE_3__*,int const,int /*<<< orphan*/ *) ; 

int VP8IteratorProgress(const VP8EncIterator* const it, int delta) {
  VP8Encoder* const enc = it->enc_;
  if (delta && enc->pic_->progress_hook != NULL) {
    const int done = it->count_down0_ - it->count_down_;
    const int percent = (it->count_down0_ <= 0)
                      ? it->percent0_
                      : it->percent0_ + delta * done / it->count_down0_;
    return WebPReportProgress(enc->pic_, percent, &enc->percent_);
  }
  return 1;
}