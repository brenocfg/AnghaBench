#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_14__ {int /*<<< orphan*/  args; int /*<<< orphan*/  uri; TYPE_6__* connection; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* resume_handler ) (TYPE_1__*) ;scalar_t__ entered_content_phase; TYPE_3__* cur_co_ctx; } ;
typedef  TYPE_2__ ngx_http_lua_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/ * cleanup; TYPE_1__* data; } ;
typedef  TYPE_3__ ngx_http_lua_co_ctx_t ;
struct TYPE_17__ {TYPE_1__* current_request; } ;
typedef  TYPE_4__ ngx_http_log_ctx_t ;
struct TYPE_18__ {TYPE_3__* data; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_19__ {scalar_t__ fd; TYPE_7__* log; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_20__ {TYPE_4__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_core_run_phases (TYPE_1__*) ; 
 TYPE_2__* ngx_http_get_module_ctx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_sleep_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ngx_http_lua_sleep_handler(ngx_event_t *ev)
{
    ngx_connection_t        *c;
    ngx_http_request_t      *r;
    ngx_http_lua_ctx_t      *ctx;
    ngx_http_log_ctx_t      *log_ctx;
    ngx_http_lua_co_ctx_t   *coctx;

    coctx = ev->data;

    r = coctx->data;
    c = r->connection;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    if (ctx == NULL) {
        return;
    }

    if (c->fd != (ngx_socket_t) -1) {  /* not a fake connection */
        log_ctx = c->log->data;
        log_ctx->current_request = r;
    }

    coctx->cleanup = NULL;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "lua sleep timer expired: \"%V?%V\"", &r->uri, &r->args);

    ctx->cur_co_ctx = coctx;

    if (ctx->entered_content_phase) {
        (void) ngx_http_lua_sleep_resume(r);

    } else {
        ctx->resume_handler = ngx_http_lua_sleep_resume;
        ngx_http_core_run_phases(r);
    }

    ngx_http_run_posted_requests(c);
}