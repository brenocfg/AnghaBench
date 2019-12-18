#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int resource_count; int /*<<< orphan*/  sem_event; int /*<<< orphan*/  wait_queue; } ;
typedef  TYPE_1__ ngx_http_lua_sema_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_OK ; 
 TYPE_4__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ngx_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_queue_empty (int /*<<< orphan*/ *) ; 

int
ngx_http_lua_ffi_sema_post(ngx_http_lua_sema_t *sem, int n)
{
    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "http lua semaphore post: %p, n: %d, resources: %d",
                   sem, n, sem->resource_count);

    sem->resource_count += n;

    if (!ngx_queue_empty(&sem->wait_queue)) {
        /* we need the extra paranthese around the first argument of
         * ngx_post_event() just to work around macro issues in nginx
         * cores older than nginx 1.7.12 (exclusive).
         */
        ngx_post_event((&sem->sem_event), &ngx_posted_events);
    }

    return NGX_OK;
}