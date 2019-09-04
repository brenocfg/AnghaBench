#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_queue_t ;
struct TYPE_5__ {int /*<<< orphan*/  wait_count; } ;
typedef  TYPE_1__ ngx_http_lua_sema_t ;
struct TYPE_7__ {scalar_t__ timer_set; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cleanup; int /*<<< orphan*/  sem_wait_queue; TYPE_3__ sleep; TYPE_1__* data; } ;
typedef  TYPE_2__ ngx_http_lua_co_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_4__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_sema_cleanup(void *data)
{
    ngx_http_lua_co_ctx_t          *coctx = data;
    ngx_queue_t                    *q;
    ngx_http_lua_sema_t            *sem;

    sem = coctx->data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "http lua semaphore cleanup");

    if (coctx->sleep.timer_set) {
        ngx_del_timer(&coctx->sleep);
    }

    q = &coctx->sem_wait_queue;

    ngx_queue_remove(q);
    sem->wait_count--;
    coctx->cleanup = NULL;
}