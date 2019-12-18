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
typedef  scalar_t__ vlc_tick_t ;
struct task {scalar_t__ timeout; int /*<<< orphan*/  entity; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pf_stop ) (int /*<<< orphan*/ ,void*) ;scalar_t__ (* pf_probe ) (int /*<<< orphan*/ ,void*) ;scalar_t__ (* pf_start ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ;} ;
struct background_worker {int /*<<< orphan*/  owner; TYPE_1__ conf; int /*<<< orphan*/  lock; } ;
struct background_thread {int cancel; int probe; int /*<<< orphan*/  probe_cancel_wait; struct task* task; struct background_worker* owner; } ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 struct task* QueueTake (struct background_worker*,int) ; 
 int /*<<< orphan*/  RemoveThread (struct background_thread*) ; 
 int /*<<< orphan*/  TerminateTask (struct background_thread*,struct task*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void* Thread( void* data )
{
    struct background_thread *thread = data;
    struct background_worker *worker = thread->owner;

    for (;;)
    {
        vlc_mutex_lock(&worker->lock);
        struct task *task = QueueTake(worker, 5000);
        if (!task)
        {
            vlc_mutex_unlock(&worker->lock);
            /* terminate this thread */
            break;
        }

        thread->task = task;
        thread->cancel = false;
        thread->probe = false;
        vlc_tick_t deadline;
        if (task->timeout > 0)
            deadline = vlc_tick_now() + task->timeout;
        else
            deadline = INT64_MAX; /* no deadline */
        vlc_mutex_unlock(&worker->lock);

        void *handle;
        if (worker->conf.pf_start(worker->owner, task->entity, &handle))
        {
            TerminateTask(thread, task);
            continue;
        }

        for (;;)
        {
            vlc_mutex_lock(&worker->lock);
            bool timeout = false;
            while (!timeout && !thread->probe && !thread->cancel)
                /* any non-zero return value means timeout */
                timeout = vlc_cond_timedwait(&thread->probe_cancel_wait,
                                             &worker->lock, deadline) != 0;

            bool cancel = thread->cancel;
            thread->cancel = false;
            thread->probe = false;
            vlc_mutex_unlock(&worker->lock);

            if (timeout || cancel
                    || worker->conf.pf_probe(worker->owner, handle))
            {
                worker->conf.pf_stop(worker->owner, handle);
                TerminateTask(thread, task);
                break;
            }
        }
    }

    RemoveThread(thread);

    return NULL;
}