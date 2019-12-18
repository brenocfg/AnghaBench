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
struct task {int /*<<< orphan*/  node; } ;
struct background_worker {int /*<<< orphan*/  queue_wait; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void QueuePush(struct background_worker *worker, struct task *task)
{
    vlc_mutex_assert(&worker->lock);
    vlc_list_append(&task->node, &worker->queue);
    vlc_cond_signal(&worker->queue_wait);
}