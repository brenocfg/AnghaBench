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
struct background_worker {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BackgroundWorkerCancelLocked (struct background_worker*,void*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void background_worker_Cancel( struct background_worker* worker, void* id )
{
    vlc_mutex_lock(&worker->lock);
    BackgroundWorkerCancelLocked(worker, id);
    vlc_mutex_unlock(&worker->lock);
}