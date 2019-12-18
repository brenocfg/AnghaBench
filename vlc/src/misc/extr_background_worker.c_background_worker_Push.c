#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_threads; } ;
struct background_worker {scalar_t__ uncompleted; scalar_t__ nthreads; int /*<<< orphan*/  lock; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  QueuePush (struct background_worker*,struct task*) ; 
 int /*<<< orphan*/  SpawnThread (struct background_worker*) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 struct task* task_Create (struct background_worker*,void*,void*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int background_worker_Push( struct background_worker* worker, void* entity,
                        void* id, int timeout )
{
    struct task *task = task_Create(worker, id, entity, timeout);
    if (unlikely(!task))
        return VLC_ENOMEM;

    vlc_mutex_lock(&worker->lock);
    QueuePush(worker, task);
    if (++worker->uncompleted > worker->nthreads
            && worker->nthreads < worker->conf.max_threads)
        SpawnThread(worker);
    vlc_mutex_unlock(&worker->lock);

    return VLC_SUCCESS;
}