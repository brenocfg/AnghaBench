#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int mb_w_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_11__ {int /*<<< orphan*/  (* Init ) (TYPE_3__*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  hook; int /*<<< orphan*/ * data2; TYPE_2__* data1; } ;
struct TYPE_9__ {int delta_progress; scalar_t__ uv_alpha; scalar_t__ alpha; int /*<<< orphan*/  alphas; int /*<<< orphan*/  it; TYPE_3__ worker; } ;
typedef  TYPE_2__ SegmentJob ;

/* Variables and functions */
 int /*<<< orphan*/  DoSegmentsJob ; 
 int /*<<< orphan*/  VP8IteratorInit (TYPE_1__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8IteratorSetCountDown (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP8IteratorSetRow (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* WebPGetWorkerInterface () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void InitSegmentJob(VP8Encoder* const enc, SegmentJob* const job,
                           int start_row, int end_row) {
  WebPGetWorkerInterface()->Init(&job->worker);
  job->worker.data1 = job;
  job->worker.data2 = &job->it;
  job->worker.hook = DoSegmentsJob;
  VP8IteratorInit(enc, &job->it);
  VP8IteratorSetRow(&job->it, start_row);
  VP8IteratorSetCountDown(&job->it, (end_row - start_row) * enc->mb_w_);
  memset(job->alphas, 0, sizeof(job->alphas));
  job->alpha = 0;
  job->uv_alpha = 0;
  // only one of both jobs can record the progress, since we don't
  // expect the user's hook to be multi-thread safe
  job->delta_progress = (start_row == 0) ? 20 : 0;
}