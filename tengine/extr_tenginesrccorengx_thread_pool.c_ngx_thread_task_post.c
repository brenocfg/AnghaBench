#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int active; } ;
struct TYPE_9__ {scalar_t__ id; struct TYPE_9__* next; TYPE_1__ event; } ;
typedef  TYPE_3__ ngx_thread_task_t ;
struct TYPE_8__ {TYPE_3__** last; } ;
struct TYPE_10__ {scalar_t__ waiting; scalar_t__ max_queue; int /*<<< orphan*/  name; int /*<<< orphan*/  log; int /*<<< orphan*/  mtx; TYPE_2__ queue; int /*<<< orphan*/  cond; } ;
typedef  TYPE_4__ ngx_thread_pool_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 scalar_t__ ngx_thread_cond_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_thread_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_thread_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_thread_pool_task_id ; 

ngx_int_t
ngx_thread_task_post(ngx_thread_pool_t *tp, ngx_thread_task_t *task)
{
    if (task->event.active) {
        ngx_log_error(NGX_LOG_ALERT, tp->log, 0,
                      "task #%ui already active", task->id);
        return NGX_ERROR;
    }

    if (ngx_thread_mutex_lock(&tp->mtx, tp->log) != NGX_OK) {
        return NGX_ERROR;
    }

    if (tp->waiting >= tp->max_queue) {
        (void) ngx_thread_mutex_unlock(&tp->mtx, tp->log);

        ngx_log_error(NGX_LOG_ERR, tp->log, 0,
                      "thread pool \"%V\" queue overflow: %i tasks waiting",
                      &tp->name, tp->waiting);
        return NGX_ERROR;
    }

    task->event.active = 1;

    task->id = ngx_thread_pool_task_id++;
    task->next = NULL;

    if (ngx_thread_cond_signal(&tp->cond, tp->log) != NGX_OK) {
        (void) ngx_thread_mutex_unlock(&tp->mtx, tp->log);
        return NGX_ERROR;
    }

    *tp->queue.last = task;
    tp->queue.last = &task->next;

    tp->waiting++;

    (void) ngx_thread_mutex_unlock(&tp->mtx, tp->log);

    ngx_log_debug2(NGX_LOG_DEBUG_CORE, tp->log, 0,
                   "task #%ui added to thread pool \"%V\"",
                   task->id, &tp->name);

    return NGX_OK;
}