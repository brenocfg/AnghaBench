#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int complete; int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;scalar_t__ active; int /*<<< orphan*/  log; } ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_2__ event; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ngx_thread_task_t ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_8__ {TYPE_1__* first; TYPE_1__** last; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memory_barrier () ; 
 int /*<<< orphan*/  ngx_spinlock (int /*<<< orphan*/ *,int,int) ; 
 TYPE_5__ ngx_thread_pool_done ; 
 int /*<<< orphan*/  ngx_thread_pool_done_lock ; 
 int /*<<< orphan*/  ngx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_thread_pool_handler(ngx_event_t *ev)
{
    ngx_event_t        *event;
    ngx_thread_task_t  *task;

    ngx_log_debug0(NGX_LOG_DEBUG_CORE, ev->log, 0, "thread pool handler");

    ngx_spinlock(&ngx_thread_pool_done_lock, 1, 2048);

    task = ngx_thread_pool_done.first;
    ngx_thread_pool_done.first = NULL;
    ngx_thread_pool_done.last = &ngx_thread_pool_done.first;

    ngx_memory_barrier();

    ngx_unlock(&ngx_thread_pool_done_lock);

    while (task) {
        ngx_log_debug1(NGX_LOG_DEBUG_CORE, ev->log, 0,
                       "run completion handler for task #%ui", task->id);

        event = &task->event;
        task = task->next;

        event->complete = 1;
        event->active = 0;

        event->handler(event);
    }
}