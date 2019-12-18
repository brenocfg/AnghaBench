#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hook; int /*<<< orphan*/ * data2; TYPE_2__* data1; } ;
typedef  TYPE_1__ WebPWorker ;
struct TYPE_7__ {scalar_t__ thread_level_; TYPE_1__ alpha_worker_; scalar_t__ alpha_data_size_; int /*<<< orphan*/ * alpha_data_; int /*<<< orphan*/  pic_; int /*<<< orphan*/  has_alpha_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_8__ {int /*<<< orphan*/  (* Init ) (TYPE_1__* const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CompressAlphaJob ; 
 TYPE_4__* WebPGetWorkerInterface () ; 
 int /*<<< orphan*/  WebPInitAlphaProcessing () ; 
 int /*<<< orphan*/  WebPPictureHasTransparency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__* const) ; 

void VP8EncInitAlpha(VP8Encoder* const enc) {
  WebPInitAlphaProcessing();
  enc->has_alpha_ = WebPPictureHasTransparency(enc->pic_);
  enc->alpha_data_ = NULL;
  enc->alpha_data_size_ = 0;
  if (enc->thread_level_ > 0) {
    WebPWorker* const worker = &enc->alpha_worker_;
    WebPGetWorkerInterface()->Init(worker);
    worker->data1 = enc;
    worker->data2 = NULL;
    worker->hook = CompressAlphaJob;
  }
}