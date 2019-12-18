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
struct background_worker {int /*<<< orphan*/  threads; int /*<<< orphan*/  nthreads; int /*<<< orphan*/  lock; } ;
struct background_thread {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  Thread ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 struct background_thread* background_thread_Create (struct background_worker*) ; 
 int /*<<< orphan*/  free (struct background_thread*) ; 
 scalar_t__ vlc_clone_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct background_thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool SpawnThread(struct background_worker *worker)
{
    vlc_mutex_assert(&worker->lock);

    struct background_thread *thread = background_thread_Create(worker);
    if (!thread)
        return false;

    if (vlc_clone_detach(NULL, Thread, thread, VLC_THREAD_PRIORITY_LOW))
    {
        free(thread);
        return false;
    }
    worker->nthreads++;
    vlc_list_append(&thread->node, &worker->threads);

    return true;
}