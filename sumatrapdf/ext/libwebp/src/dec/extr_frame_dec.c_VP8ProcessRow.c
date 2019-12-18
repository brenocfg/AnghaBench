#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ status_; } ;
typedef  TYPE_1__ WebPWorker ;
struct TYPE_12__ {scalar_t__ mb_y_; int filter_row_; scalar_t__ id_; int /*<<< orphan*/ * f_info_; int /*<<< orphan*/ * mb_data_; int /*<<< orphan*/  io_; } ;
typedef  TYPE_2__ VP8ThreadContext ;
typedef  int /*<<< orphan*/  VP8MBData ;
typedef  int /*<<< orphan*/  VP8Io ;
typedef  int /*<<< orphan*/  VP8FInfo ;
struct TYPE_13__ {scalar_t__ filter_type_; scalar_t__ mb_y_; scalar_t__ tl_mb_y_; scalar_t__ br_mb_y_; int mt_method_; scalar_t__ cache_id_; scalar_t__ num_caches_; int /*<<< orphan*/ * f_info_; int /*<<< orphan*/ * mb_data_; TYPE_1__ worker_; TYPE_2__ thread_ctx_; } ;
typedef  TYPE_3__ VP8Decoder ;
struct TYPE_14__ {int (* Sync ) (TYPE_1__* const) ;int /*<<< orphan*/  (* Launch ) (TYPE_1__* const) ;} ;

/* Variables and functions */
 int FinishRow (TYPE_3__* const,int /*<<< orphan*/ * const) ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  ReconstructRow (TYPE_3__* const,TYPE_2__* const) ; 
 TYPE_6__* WebPGetWorkerInterface () ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (TYPE_1__* const) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__* const) ; 

int VP8ProcessRow(VP8Decoder* const dec, VP8Io* const io) {
  int ok = 1;
  VP8ThreadContext* const ctx = &dec->thread_ctx_;
  const int filter_row =
      (dec->filter_type_ > 0) &&
      (dec->mb_y_ >= dec->tl_mb_y_) && (dec->mb_y_ <= dec->br_mb_y_);
  if (dec->mt_method_ == 0) {
    // ctx->id_ and ctx->f_info_ are already set
    ctx->mb_y_ = dec->mb_y_;
    ctx->filter_row_ = filter_row;
    ReconstructRow(dec, ctx);
    ok = FinishRow(dec, io);
  } else {
    WebPWorker* const worker = &dec->worker_;
    // Finish previous job *before* updating context
    ok &= WebPGetWorkerInterface()->Sync(worker);
    assert(worker->status_ == OK);
    if (ok) {   // spawn a new deblocking/output job
      ctx->io_ = *io;
      ctx->id_ = dec->cache_id_;
      ctx->mb_y_ = dec->mb_y_;
      ctx->filter_row_ = filter_row;
      if (dec->mt_method_ == 2) {  // swap macroblock data
        VP8MBData* const tmp = ctx->mb_data_;
        ctx->mb_data_ = dec->mb_data_;
        dec->mb_data_ = tmp;
      } else {
        // perform reconstruction directly in main thread
        ReconstructRow(dec, ctx);
      }
      if (filter_row) {            // swap filter info
        VP8FInfo* const tmp = ctx->f_info_;
        ctx->f_info_ = dec->f_info_;
        dec->f_info_ = tmp;
      }
      // (reconstruct)+filter in parallel
      WebPGetWorkerInterface()->Launch(worker);
      if (++dec->cache_id_ == dec->num_caches_) {
        dec->cache_id_ = 0;
      }
    }
  }
  return ok;
}