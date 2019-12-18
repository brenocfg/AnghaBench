#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_socket_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_7__ {int destroyed; scalar_t__ fd; TYPE_5__* write; TYPE_5__* read; int /*<<< orphan*/ * pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_connection_t ;
struct TYPE_9__ {TYPE_1__** files; } ;
struct TYPE_8__ {int closed; scalar_t__ timer_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_6__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_free_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 

void
ngx_http_lua_close_fake_connection(ngx_connection_t *c)
{
    ngx_pool_t          *pool;
    ngx_connection_t    *saved_c = NULL;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http lua close fake http connection %p", c);

    c->destroyed = 1;

    pool = c->pool;

    if (c->read->timer_set) {
        ngx_del_timer(c->read);
    }

    if (c->write->timer_set) {
        ngx_del_timer(c->write);
    }

    c->read->closed = 1;
    c->write->closed = 1;

    /* we temporarily use a valid fd (0) to make ngx_free_connection happy */

    c->fd = 0;

    if (ngx_cycle->files) {
        saved_c = ngx_cycle->files[0];
    }

    ngx_free_connection(c);

    c->fd = (ngx_socket_t) -1;

    if (ngx_cycle->files) {
        ngx_cycle->files[0] = saved_c;
    }

    if (pool) {
        ngx_destroy_pool(pool);
    }
}