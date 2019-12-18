#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hook; void* data2; TYPE_3__* data1; } ;
typedef  TYPE_2__ WebPWorker ;
struct TYPE_8__ {int /*<<< orphan*/  io_; } ;
struct TYPE_10__ {scalar_t__ mt_method_; scalar_t__ filter_type_; scalar_t__ num_caches_; TYPE_1__ thread_ctx_; TYPE_2__ worker_; scalar_t__ cache_id_; } ;
typedef  TYPE_3__ VP8Decoder ;
struct TYPE_11__ {int /*<<< orphan*/  (* Reset ) (TYPE_2__* const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FinishRow ; 
 scalar_t__ MT_CACHE_LINES ; 
 scalar_t__ ST_CACHE_LINES ; 
 int VP8SetError (TYPE_3__* const,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VP8_STATUS_OUT_OF_MEMORY ; 
 TYPE_5__* WebPGetWorkerInterface () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__* const) ; 

__attribute__((used)) static int InitThreadContext(VP8Decoder* const dec) {
  dec->cache_id_ = 0;
  if (dec->mt_method_ > 0) {
    WebPWorker* const worker = &dec->worker_;
    if (!WebPGetWorkerInterface()->Reset(worker)) {
      return VP8SetError(dec, VP8_STATUS_OUT_OF_MEMORY,
                         "thread initialization failed.");
    }
    worker->data1 = dec;
    worker->data2 = (void*)&dec->thread_ctx_.io_;
    worker->hook = FinishRow;
    dec->num_caches_ =
      (dec->filter_type_ > 0) ? MT_CACHE_LINES : MT_CACHE_LINES - 1;
  } else {
    dec->num_caches_ = ST_CACHE_LINES;
  }
  return 1;
}