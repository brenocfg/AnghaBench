#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_11__ {int /*<<< orphan*/  flushing_coros; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
struct TYPE_12__ {TYPE_2__* data; scalar_t__ flushing; } ;
typedef  TYPE_4__ ngx_http_lua_co_ctx_t ;
struct TYPE_13__ {scalar_t__ timer_set; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_9__ {TYPE_5__* write; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_del_timer (TYPE_5__*) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static void
ngx_http_lua_flush_cleanup(void *data)
{
    ngx_http_request_t                      *r;
    ngx_event_t                             *wev;
    ngx_http_lua_ctx_t                      *ctx;
    ngx_http_lua_co_ctx_t                   *coctx = data;

    coctx->flushing = 0;

    r = coctx->data;
    if (r == NULL) {
        return;
    }

    wev = r->connection->write;

    if (wev && wev->timer_set) {
        ngx_del_timer(wev);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return;
    }

    ctx->flushing_coros--;
}