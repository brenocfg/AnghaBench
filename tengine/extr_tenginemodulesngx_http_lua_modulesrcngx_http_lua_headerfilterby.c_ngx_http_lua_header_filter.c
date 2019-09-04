#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_18__ {int filter_need_in_memory; int /*<<< orphan*/  uri; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_19__ {scalar_t__ (* header_filter_handler ) (TYPE_2__*) ;scalar_t__ body_filter_handler; } ;
typedef  TYPE_3__ ngx_http_lua_loc_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  context; int /*<<< orphan*/ * cleanup; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
struct TYPE_21__ {int /*<<< orphan*/  handler; TYPE_4__* data; } ;
typedef  TYPE_5__ ngx_http_cleanup_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CONTEXT_HEADER_FILTER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 TYPE_5__* ngx_http_cleanup_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_lua_create_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_request_cleanup_handler ; 
 scalar_t__ ngx_http_next_header_filter (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_header_filter(ngx_http_request_t *r)
{
    ngx_http_lua_loc_conf_t     *llcf;
    ngx_http_lua_ctx_t          *ctx;
    ngx_int_t                    rc;
    ngx_http_cleanup_t          *cln;
    uint16_t                     old_context;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua header filter for user lua code, uri \"%V\"", &r->uri);

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

    if (llcf->body_filter_handler) {
        r->filter_need_in_memory = 1;
    }

    if (llcf->header_filter_handler == NULL) {
        dd("no header filter handler found");
        return ngx_http_next_header_filter(r);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    dd("ctx = %p", ctx);

    if (ctx == NULL) {
        ctx = ngx_http_lua_create_ctx(r);
        if (ctx == NULL) {
            return NGX_ERROR;
        }
    }

    if (ctx->cleanup == NULL) {
        cln = ngx_http_cleanup_add(r, 0);
        if (cln == NULL) {
            return NGX_ERROR;
        }

        cln->handler = ngx_http_lua_request_cleanup_handler;
        cln->data = ctx;
        ctx->cleanup = &cln->handler;
    }

    old_context = ctx->context;
    ctx->context = NGX_HTTP_LUA_CONTEXT_HEADER_FILTER;

    dd("calling header filter handler");
    rc = llcf->header_filter_handler(r);

    ctx->context = old_context;

    if (rc == NGX_DECLINED) {
        return NGX_OK;
    }

    if (rc == NGX_AGAIN || rc == NGX_ERROR) {
        return rc;
    }

    return ngx_http_next_header_filter(r);
}