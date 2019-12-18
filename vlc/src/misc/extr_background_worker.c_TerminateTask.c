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
struct task {int dummy; } ;
struct background_worker {scalar_t__ uncompleted; int /*<<< orphan*/  lock; } ;
struct background_thread {int /*<<< orphan*/ * task; struct background_worker* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  task_Destroy (struct background_worker*,struct task*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void TerminateTask(struct background_thread *thread, struct task *task)
{
    struct background_worker *worker = thread->owner;
    task_Destroy(worker, task);

    vlc_mutex_lock(&worker->lock);
    thread->task = NULL;
    worker->uncompleted--;
    assert(worker->uncompleted >= 0);
    vlc_mutex_unlock(&worker->lock);
}