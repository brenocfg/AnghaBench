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
struct background_worker {int dummy; } ;
struct background_thread {int probe; int cancel; struct background_worker* owner; int /*<<< orphan*/ * task; int /*<<< orphan*/  probe_cancel_wait; } ;

/* Variables and functions */
 struct background_thread* malloc (int) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct background_thread *
background_thread_Create(struct background_worker *owner)
{
    struct background_thread *thread = malloc(sizeof(*thread));
    if (!thread)
        return NULL;

    vlc_cond_init(&thread->probe_cancel_wait);
    thread->probe = false;
    thread->cancel = false;
    thread->task = NULL;
    thread->owner = owner;
    return thread;
}