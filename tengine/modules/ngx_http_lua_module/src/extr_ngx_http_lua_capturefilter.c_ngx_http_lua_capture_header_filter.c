#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {int filter_need_in_memory; int header_sent; scalar_t__ method; int header_only; TYPE_1__* connection; TYPE_3__* post_subrequest; int /*<<< orphan*/  uri; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_15__ {scalar_t__ handler; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_http_post_subrequest_t ;
struct TYPE_16__ {TYPE_5__* ctx; } ;
typedef  TYPE_4__ ngx_http_lua_post_subrequest_data_t ;
struct TYPE_17__ {int header_sent; scalar_t__ capture; int /*<<< orphan*/ * body; int /*<<< orphan*/ ** last_body; int /*<<< orphan*/  index; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_HEAD ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  dd (char*,TYPE_5__*) ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_next_header_filter (TYPE_2__*) ; 
 scalar_t__ ngx_http_lua_post_subrequest ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_capture_header_filter(ngx_http_request_t *r)
{
    ngx_http_post_subrequest_t      *psr;
    ngx_http_lua_ctx_t              *old_ctx;
    ngx_http_lua_ctx_t              *ctx;

    ngx_http_lua_post_subrequest_data_t      *psr_data;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua capture header filter, uri \"%V\"", &r->uri);

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    dd("old ctx: %p", ctx);

    if (ctx == NULL || ! ctx->capture) {

        psr = r->post_subrequest;

        if (psr != NULL
            && psr->handler == ngx_http_lua_post_subrequest
            && psr->data != NULL)
        {
            /* the lua ctx has been cleared by ngx_http_internal_redirect,
             * resume it from the post_subrequest data
             */
            psr_data = psr->data;

            old_ctx = psr_data->ctx;

            if (ctx == NULL) {
                ctx = old_ctx;
                ngx_http_set_ctx(r, ctx, ngx_http_lua_module);

            } else {
                ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                               "lua restoring ctx with capture %d, index %d",
                               old_ctx->capture, old_ctx->index);

                ctx->capture = old_ctx->capture;
                ctx->index = old_ctx->index;
                ctx->body = NULL;
                ctx->last_body = &ctx->body;
                psr_data->ctx = ctx;
            }
        }
    }

    if (ctx && ctx->capture) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua capturing response body");

        /* force subrequest response body buffer in memory */
        r->filter_need_in_memory = 1;
        r->header_sent = 1;
        ctx->header_sent = 1;

        if (r->method == NGX_HTTP_HEAD) {
            r->header_only = 1;
        }

        return NGX_OK;
    }

    return ngx_http_lua_next_header_filter(r);
}