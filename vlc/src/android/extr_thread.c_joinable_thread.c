#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlc_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  finished; int /*<<< orphan*/  data; void* (* entry ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  finish_joinable_thread ; 
 void* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* thread ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *joinable_thread(void *data)
{
    vlc_thread_t th = data;
    void *ret;

    vlc_cleanup_push(finish_joinable_thread, th);
    thread = th;
    ret = th->entry(th->data);
    vlc_cleanup_pop();
    vlc_sem_post(&th->finished);

    return ret;
}