#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  (* write_event_handler ) (TYPE_2__*) ;TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_14__ {TYPE_5__* write_co_ctx; scalar_t__ write_waiting; int /*<<< orphan*/  write_event_handler; } ;
typedef  TYPE_3__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_15__ {TYPE_5__* cur_co_ctx; int /*<<< orphan*/  resume_handler; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
struct TYPE_16__ {scalar_t__ co_ref; int /*<<< orphan*/ * cleanup; } ;
typedef  TYPE_5__ ngx_http_lua_co_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_is_thread (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_dummy_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_write_resume ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_http_lua_socket_handle_write_success(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u)
{
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_lua_co_ctx_t       *coctx;

#if 1
    u->write_event_handler = ngx_http_lua_socket_dummy_handler;
#endif

    if (u->write_waiting) {
        u->write_waiting = 0;

        coctx = u->write_co_ctx;
        coctx->cleanup = NULL;
        u->write_co_ctx = NULL;

        ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
        if (ctx == NULL) {
            return;
        }

        ctx->resume_handler = ngx_http_lua_socket_tcp_write_resume;
        ctx->cur_co_ctx = coctx;

        ngx_http_lua_assert(coctx && (!ngx_http_lua_is_thread(ctx)
                            || coctx->co_ref >= 0));

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua tcp socket waking up the current request (read)");

        r->write_event_handler(r);
    }
}