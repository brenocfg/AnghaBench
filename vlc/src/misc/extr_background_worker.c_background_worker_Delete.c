#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct background_worker {int closing; int /*<<< orphan*/  lock; int /*<<< orphan*/  nothreads_wait; scalar_t__ nthreads; int /*<<< orphan*/  queue_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  BackgroundWorkerCancelLocked (struct background_worker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  background_worker_Destroy (struct background_worker*) ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void background_worker_Delete( struct background_worker* worker )
{
    vlc_mutex_lock(&worker->lock);

    worker->closing = true;
    BackgroundWorkerCancelLocked(worker, NULL);
    /* closing is now true, this will wake up any QueueTake() */
    vlc_cond_broadcast(&worker->queue_wait);

    while (worker->nthreads)
        vlc_cond_wait(&worker->nothreads_wait, &worker->lock);

    vlc_mutex_unlock(&worker->lock);

    /* no threads use the worker anymore, we can destroy it */
    background_worker_Destroy(worker);
}