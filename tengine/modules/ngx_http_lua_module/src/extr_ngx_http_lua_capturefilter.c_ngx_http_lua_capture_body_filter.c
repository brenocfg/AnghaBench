#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_int_t ;
struct TYPE_14__ {int data; scalar_t__ len; } ;
struct TYPE_12__ {int /*<<< orphan*/  pool; struct TYPE_12__* main; TYPE_4__ uri; TYPE_1__* connection; struct TYPE_12__* parent; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_13__ {int seen_last_for_subreq; int /*<<< orphan*/  last_body; scalar_t__ run_post_subrequest; int /*<<< orphan*/  capture; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_OK ; 
 int /*<<< orphan*/  dd (char*,int,int) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ngx_http_lua_add_copy_chain (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ngx_http_lua_discard_bufs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int ngx_http_lua_next_body_filter (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_capture_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    int                              rc;
    ngx_int_t                        eof;
    ngx_http_lua_ctx_t              *ctx;
    ngx_http_lua_ctx_t              *pr_ctx;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua capture body filter, uri \"%V\"", &r->uri);

    if (in == NULL) {
        return ngx_http_lua_next_body_filter(r, NULL);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    if (!ctx || !ctx->capture) {
        dd("no ctx or no capture %.*s", (int) r->uri.len, r->uri.data);

        return ngx_http_lua_next_body_filter(r, in);
    }

    if (ctx->run_post_subrequest) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua body filter skipped because post subrequest "
                       "already run");
        return NGX_OK;
    }

    if (r->parent == NULL) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua body filter skipped because no parent request "
                       "found");

        return NGX_ERROR;
    }

    pr_ctx = ngx_http_get_module_ctx(r->parent, ngx_http_lua_module);
    if (pr_ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua capture body filter capturing response body, uri "
                   "\"%V\"", &r->uri);

    rc = ngx_http_lua_add_copy_chain(r, pr_ctx, &ctx->last_body, in, &eof);
    if (rc != NGX_OK) {
        return NGX_ERROR;
    }

    dd("add copy chain eof: %d, sr: %d", (int) eof, r != r->main);

    if (eof) {
        ctx->seen_last_for_subreq = 1;
    }

    ngx_http_lua_discard_bufs(r->pool, in);

    return NGX_OK;
}