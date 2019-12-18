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
struct background_worker {scalar_t__ nthreads; int /*<<< orphan*/  lock; int /*<<< orphan*/  nothreads_wait; } ;
struct background_thread {int /*<<< orphan*/  node; struct background_worker* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  background_thread_Destroy (struct background_thread*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RemoveThread(struct background_thread *thread)
{
    struct background_worker *worker = thread->owner;

    vlc_mutex_lock(&worker->lock);

    vlc_list_remove(&thread->node);
    worker->nthreads--;
    assert(worker->nthreads >= 0);
    if (!worker->nthreads)
        vlc_cond_signal(&worker->nothreads_wait);

    vlc_mutex_unlock(&worker->lock);

    background_thread_Destroy(thread);
}