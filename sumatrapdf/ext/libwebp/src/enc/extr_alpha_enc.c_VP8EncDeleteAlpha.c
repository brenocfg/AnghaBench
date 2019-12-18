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
struct TYPE_4__ {scalar_t__ thread_level_; scalar_t__ has_alpha_; scalar_t__ alpha_data_size_; int /*<<< orphan*/ * alpha_data_; int /*<<< orphan*/  alpha_worker_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_5__ {int (* Sync ) (int /*<<< orphan*/ * const) ;int /*<<< orphan*/  (* End ) (int /*<<< orphan*/ * const) ;} ;

/* Variables and functions */
 TYPE_2__* WebPGetWorkerInterface () ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ * const) ; 

int VP8EncDeleteAlpha(VP8Encoder* const enc) {
  int ok = 1;
  if (enc->thread_level_ > 0) {
    WebPWorker* const worker = &enc->alpha_worker_;
    // finish anything left in flight
    ok = WebPGetWorkerInterface()->Sync(worker);
    // still need to end the worker, even if !ok
    WebPGetWorkerInterface()->End(worker);
  }
  WebPSafeFree(enc->alpha_data_);
  enc->alpha_data_ = NULL;
  enc->alpha_data_size_ = 0;
  enc->has_alpha_ = 0;
  return ok;
}