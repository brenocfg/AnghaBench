#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  condition_; int /*<<< orphan*/  mutex_; int /*<<< orphan*/  thread_; } ;
typedef  TYPE_1__ WebPWorkerImpl ;
struct TYPE_7__ {scalar_t__ status_; int /*<<< orphan*/ * impl_; } ;
typedef  TYPE_2__ WebPWorker ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeState (TYPE_2__* const,scalar_t__) ; 
 scalar_t__ NOT_OK ; 
 int /*<<< orphan*/  WebPSafeFree (TYPE_1__* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void End(WebPWorker* const worker) {
#ifdef WEBP_USE_THREAD
  if (worker->impl_ != NULL) {
    WebPWorkerImpl* const impl = (WebPWorkerImpl*)worker->impl_;
    ChangeState(worker, NOT_OK);
    pthread_join(impl->thread_, NULL);
    pthread_mutex_destroy(&impl->mutex_);
    pthread_cond_destroy(&impl->condition_);
    WebPSafeFree(impl);
    worker->impl_ = NULL;
  }
#else
  worker->status_ = NOT_OK;
  assert(worker->impl_ == NULL);
#endif
  assert(worker->status_ == NOT_OK);
}