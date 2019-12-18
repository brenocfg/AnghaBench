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
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  co_ref; } ;
struct TYPE_11__ {scalar_t__ co_op; int /*<<< orphan*/  exec_args; int /*<<< orphan*/  exec_uri; int /*<<< orphan*/  resume_handler; scalar_t__ exited; scalar_t__ exit_code; scalar_t__ entered_content_phase; scalar_t__ entered_access_phase; scalar_t__ entered_rewrite_phase; TYPE_4__ entry_co_ctx; int /*<<< orphan*/ * user_co_ctx; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_lua_finalize_threads (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_wev_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_str_null (int /*<<< orphan*/ *) ; 

void
ngx_http_lua_reset_ctx(ngx_http_request_t *r, lua_State *L,
    ngx_http_lua_ctx_t *ctx)
{
    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua reset ctx");

    ngx_http_lua_finalize_threads(r, ctx, L);

#if 0
    if (ctx->user_co_ctx) {
        /* no way to destroy a list but clean up the whole pool */
        ctx->user_co_ctx = NULL;
    }
#endif

    ngx_memzero(&ctx->entry_co_ctx, sizeof(ngx_http_lua_co_ctx_t));

    ctx->entry_co_ctx.co_ref = LUA_NOREF;

    ctx->entered_rewrite_phase = 0;
    ctx->entered_access_phase = 0;
    ctx->entered_content_phase = 0;

    ctx->exit_code = 0;
    ctx->exited = 0;
    ctx->resume_handler = ngx_http_lua_wev_handler;

    ngx_str_null(&ctx->exec_uri);
    ngx_str_null(&ctx->exec_args);

    ctx->co_op = 0;
}