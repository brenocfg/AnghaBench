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
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_int_t ;
struct TYPE_9__ {scalar_t__ status; } ;
struct TYPE_11__ {TYPE_2__* connection; TYPE_1__ headers_out; scalar_t__ header_sent; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_12__ {int context; int exit_code; int exited; scalar_t__ header_sent; scalar_t__ no_abort; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_DONE ; 
 int NGX_ERROR ; 
 int NGX_HTTP_CLIENT_CLOSED_REQUEST ; 
 int NGX_HTTP_CLOSE ; 
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_BALANCER ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_HEADER_FILTER ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 int NGX_HTTP_OK ; 
 int NGX_HTTP_REQUEST_TIME_OUT ; 
 int NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_ffi_check_context (TYPE_4__*,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,size_t,char*) ; 

int
ngx_http_lua_ffi_exit(ngx_http_request_t *r, int status, u_char *err,
    size_t *errlen)
{
    ngx_http_lua_ctx_t       *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        *errlen = ngx_snprintf(err, *errlen, "no request ctx found") - err;
        return NGX_ERROR;
    }

    if (ngx_http_lua_ffi_check_context(ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                                       | NGX_HTTP_LUA_CONTEXT_ACCESS
                                       | NGX_HTTP_LUA_CONTEXT_CONTENT
                                       | NGX_HTTP_LUA_CONTEXT_TIMER
                                       | NGX_HTTP_LUA_CONTEXT_HEADER_FILTER
                                       | NGX_HTTP_LUA_CONTEXT_BALANCER
                                       | NGX_HTTP_LUA_CONTEXT_SSL_CERT
                                       | NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE
                                       | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH,
                                       err, errlen)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    if (ctx->context & (NGX_HTTP_LUA_CONTEXT_SSL_CERT
                        | NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE
                        | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH))
    {

#if (NGX_HTTP_SSL)

        ctx->exit_code = status;
        ctx->exited = 1;

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua exit with code %d", status);

        if (ctx->context == NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE) {
            return NGX_DONE;
        }

        return NGX_OK;

#else

        return NGX_ERROR;

#endif
    }

    if (ctx->no_abort
        && status != NGX_ERROR
        && status != NGX_HTTP_CLOSE
        && status != NGX_HTTP_REQUEST_TIME_OUT
        && status != NGX_HTTP_CLIENT_CLOSED_REQUEST)
    {
        *errlen = ngx_snprintf(err, *errlen,
                               "attempt to abort with pending subrequests")
                  - err;
        return NGX_ERROR;
    }

    if ((r->header_sent || ctx->header_sent)
        && status >= NGX_HTTP_SPECIAL_RESPONSE
        && status != NGX_HTTP_REQUEST_TIME_OUT
        && status != NGX_HTTP_CLIENT_CLOSED_REQUEST
        && status != NGX_HTTP_CLOSE)
    {
        if (status != (ngx_int_t) r->headers_out.status) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "attempt to "
                          "set status %d via ngx.exit after sending out the "
                          "response status %ui", status,
                          r->headers_out.status);
        }

        status = NGX_HTTP_OK;
    }

    ctx->exit_code = status;
    ctx->exited = 1;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua exit with code %i", ctx->exit_code);

    if (ctx->context & (NGX_HTTP_LUA_CONTEXT_HEADER_FILTER
                        | NGX_HTTP_LUA_CONTEXT_BALANCER))
    {
        return NGX_DONE;
    }

    return NGX_OK;
}