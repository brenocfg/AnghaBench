#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ ngx_socket_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_16__ {scalar_t__ status; } ;
struct TYPE_17__ {scalar_t__ header_sent; TYPE_2__ headers_out; TYPE_1__* connection; scalar_t__ filter_finalize; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_18__ {scalar_t__ exit_code; scalar_t__ entered_content_phase; scalar_t__ header_sent; scalar_t__ buffering; TYPE_13__* cur_co_ctx; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_15__ {scalar_t__ fd; int /*<<< orphan*/  log; } ;
struct TYPE_14__ {int /*<<< orphan*/  co_status; int /*<<< orphan*/  co; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_CLIENT_CLOSED_REQUEST ; 
 scalar_t__ NGX_HTTP_CLOSE ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_DEAD ; 
 scalar_t__ NGX_HTTP_NO_CONTENT ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_HTTP_REQUEST_TIME_OUT ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_coroutine_done (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_http_lua_request_cleanup (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_send_chain_link (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_handle_exit(lua_State *L, ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx)
{
    ngx_int_t           rc;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua thread aborting request with status %d",
                   ctx->exit_code);

    ngx_http_lua_cleanup_pending_operation(ctx->cur_co_ctx);

    ngx_http_lua_probe_coroutine_done(r, ctx->cur_co_ctx->co, 1);

    ctx->cur_co_ctx->co_status = NGX_HTTP_LUA_CO_DEAD;

    if (r->filter_finalize) {
        ngx_http_set_ctx(r, ctx, ngx_http_lua_module);
    }

    ngx_http_lua_request_cleanup(ctx, 0);

    if (r->connection->fd == (ngx_socket_t) -1) {  /* fake request */
        return ctx->exit_code;
    }

#if 1
    if (!r->header_sent
        && !ctx->header_sent
        && r->headers_out.status == 0
        && ctx->exit_code >= NGX_HTTP_OK)
    {
        r->headers_out.status = ctx->exit_code;
    }
#endif

    if (ctx->buffering
        && r->headers_out.status
        && ctx->exit_code != NGX_ERROR
        && ctx->exit_code != NGX_HTTP_REQUEST_TIME_OUT
        && ctx->exit_code != NGX_HTTP_CLIENT_CLOSED_REQUEST
        && ctx->exit_code != NGX_HTTP_CLOSE)
    {
        rc = ngx_http_lua_send_chain_link(r, ctx, NULL /* indicate last_buf */);

        if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }

        if (ctx->exit_code >= NGX_HTTP_OK) {
            return NGX_HTTP_OK;
        }

        return ctx->exit_code;
    }

    if ((ctx->exit_code == NGX_OK
         && ctx->entered_content_phase)
        || (ctx->exit_code >= NGX_HTTP_OK
            && ctx->exit_code < NGX_HTTP_SPECIAL_RESPONSE
            && ctx->exit_code != NGX_HTTP_NO_CONTENT))
    {
        rc = ngx_http_lua_send_chain_link(r, ctx, NULL /* indicate last_buf */);

        if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }
    }

#if 1
    if ((r->header_sent || ctx->header_sent)
        && ctx->exit_code > NGX_OK
        && ctx->exit_code != NGX_HTTP_REQUEST_TIME_OUT
        && ctx->exit_code != NGX_HTTP_CLIENT_CLOSED_REQUEST
        && ctx->exit_code != NGX_HTTP_CLOSE)
    {
        if (ctx->entered_content_phase) {
            return NGX_OK;
        }

        return NGX_HTTP_OK;
    }
#endif

    return ctx->exit_code;
}