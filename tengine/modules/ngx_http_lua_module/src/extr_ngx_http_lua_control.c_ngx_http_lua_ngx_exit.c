#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_9__ {scalar_t__ status; } ;
struct TYPE_11__ {TYPE_2__* connection; TYPE_1__ headers_out; scalar_t__ header_sent; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_12__ {int context; scalar_t__ exit_code; int exited; scalar_t__ header_sent; scalar_t__ no_abort; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_CLIENT_CLOSED_REQUEST ; 
 scalar_t__ NGX_HTTP_CLOSE ; 
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_BALANCER ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_HEADER_FILTER ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_HTTP_REQUEST_TIME_OUT ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_exit(lua_State *L)
{
    ngx_int_t                    rc;
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting one argument");
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request object found");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                               | NGX_HTTP_LUA_CONTEXT_ACCESS
                               | NGX_HTTP_LUA_CONTEXT_CONTENT
                               | NGX_HTTP_LUA_CONTEXT_TIMER
                               | NGX_HTTP_LUA_CONTEXT_HEADER_FILTER
                               | NGX_HTTP_LUA_CONTEXT_BALANCER
                               | NGX_HTTP_LUA_CONTEXT_SSL_CERT
                               | NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE
                               | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH);

    rc = (ngx_int_t) luaL_checkinteger(L, 1);

    if (ctx->context & (NGX_HTTP_LUA_CONTEXT_SSL_CERT
                        | NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE
                        | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH))
    {

#if (NGX_HTTP_SSL)

        ctx->exit_code = rc;
        ctx->exited = 1;

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua exit with code %i", rc);

        if (ctx->context == NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE) {
            return 0;
        }

        return lua_yield(L, 0);

#else

        return luaL_error(L, "no SSL support");

#endif
    }

    if (ctx->no_abort
        && rc != NGX_ERROR
        && rc != NGX_HTTP_CLOSE
        && rc != NGX_HTTP_REQUEST_TIME_OUT
        && rc != NGX_HTTP_CLIENT_CLOSED_REQUEST)
    {
        return luaL_error(L, "attempt to abort with pending subrequests");
    }

    if ((r->header_sent || ctx->header_sent)
        && rc >= NGX_HTTP_SPECIAL_RESPONSE
        && rc != NGX_HTTP_REQUEST_TIME_OUT
        && rc != NGX_HTTP_CLIENT_CLOSED_REQUEST
        && rc != NGX_HTTP_CLOSE)
    {
        if (rc != (ngx_int_t) r->headers_out.status) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "attempt to "
                          "set status %i via ngx.exit after sending out the "
                          "response status %ui", rc, r->headers_out.status);
        }

        rc = NGX_HTTP_OK;
    }

    dd("setting exit code: %d", (int) rc);

    ctx->exit_code = rc;
    ctx->exited = 1;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua exit with code %i", ctx->exit_code);

    if (ctx->context & (NGX_HTTP_LUA_CONTEXT_HEADER_FILTER
                        | NGX_HTTP_LUA_CONTEXT_BALANCER))
    {
        return 0;
    }

    dd("calling yield");
    return lua_yield(L, 0);
}