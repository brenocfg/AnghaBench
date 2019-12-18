#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int (* Reset ) (int /*<<< orphan*/ *) ;int (* Sync ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* End ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Execute ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Launch ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ WebPWorkerInterface ;
struct TYPE_15__ {int num_segments_; } ;
struct TYPE_17__ {int method_; int mb_h_; int const mb_w_; scalar_t__ thread_level_; int alpha_; int uv_alpha_; TYPE_2__ segment_hdr_; TYPE_1__* config_; } ;
typedef  TYPE_4__ VP8Encoder ;
struct TYPE_18__ {int const alpha; int const uv_alpha; int /*<<< orphan*/  alphas; int /*<<< orphan*/  worker; } ;
struct TYPE_14__ {scalar_t__ emulate_jpeg_size; } ;
typedef  TYPE_5__ SegmentJob ;

/* Variables and functions */
 int /*<<< orphan*/  AssignSegments (TYPE_4__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitSegmentJob (TYPE_4__* const,TYPE_5__*,int const,int const) ; 
 int /*<<< orphan*/  MergeJobs (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ResetAllMBInfo (TYPE_4__* const) ; 
 TYPE_3__* WebPGetWorkerInterface () ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int stub4 (int /*<<< orphan*/ *) ; 
 int stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *) ; 
 int stub8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *) ; 

int VP8EncAnalyze(VP8Encoder* const enc) {
  int ok = 1;
  const int do_segments =
      enc->config_->emulate_jpeg_size ||   // We need the complexity evaluation.
      (enc->segment_hdr_.num_segments_ > 1) ||
      (enc->method_ <= 1);  // for method 0 - 1, we need preds_[] to be filled.
  if (do_segments) {
    const int last_row = enc->mb_h_;
    // We give a little more than a half work to the main thread.
    const int split_row = (9 * last_row + 15) >> 4;
    const int total_mb = last_row * enc->mb_w_;
#ifdef WEBP_USE_THREAD
    const int kMinSplitRow = 2;  // minimal rows needed for mt to be worth it
    const int do_mt = (enc->thread_level_ > 0) && (split_row >= kMinSplitRow);
#else
    const int do_mt = 0;
#endif
    const WebPWorkerInterface* const worker_interface =
        WebPGetWorkerInterface();
    SegmentJob main_job;
    if (do_mt) {
      SegmentJob side_job;
      // Note the use of '&' instead of '&&' because we must call the functions
      // no matter what.
      InitSegmentJob(enc, &main_job, 0, split_row);
      InitSegmentJob(enc, &side_job, split_row, last_row);
      // we don't need to call Reset() on main_job.worker, since we're calling
      // WebPWorkerExecute() on it
      ok &= worker_interface->Reset(&side_job.worker);
      // launch the two jobs in parallel
      if (ok) {
        worker_interface->Launch(&side_job.worker);
        worker_interface->Execute(&main_job.worker);
        ok &= worker_interface->Sync(&side_job.worker);
        ok &= worker_interface->Sync(&main_job.worker);
      }
      worker_interface->End(&side_job.worker);
      if (ok) MergeJobs(&side_job, &main_job);  // merge results together
    } else {
      // Even for single-thread case, we use the generic Worker tools.
      InitSegmentJob(enc, &main_job, 0, last_row);
      worker_interface->Execute(&main_job.worker);
      ok &= worker_interface->Sync(&main_job.worker);
    }
    worker_interface->End(&main_job.worker);
    if (ok) {
      enc->alpha_ = main_job.alpha / total_mb;
      enc->uv_alpha_ = main_job.uv_alpha / total_mb;
      AssignSegments(enc, main_job.alphas);
    }
  } else {   // Use only one default segment.
    ResetAllMBInfo(enc);
  }
  return ok;
}