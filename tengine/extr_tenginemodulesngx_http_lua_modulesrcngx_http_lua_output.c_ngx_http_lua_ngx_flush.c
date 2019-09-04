#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_22__ {TYPE_1__* connection; int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  header_sent; scalar_t__ header_only; struct TYPE_22__* main; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_23__ {TYPE_4__* cur_co_ctx; scalar_t__ entered_content_phase; int /*<<< orphan*/  flushing_coros; int /*<<< orphan*/  seen_body_data; int /*<<< orphan*/  header_sent; scalar_t__ buffering; scalar_t__ eof; scalar_t__ acquired_raw_req_socket; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
struct TYPE_24__ {int flushing; TYPE_2__* data; int /*<<< orphan*/  cleanup; } ;
typedef  TYPE_4__ ngx_http_lua_co_ctx_t ;
struct TYPE_25__ {int /*<<< orphan*/  send_lowat; int /*<<< orphan*/  send_timeout; } ;
typedef  TYPE_5__ ngx_http_core_loc_conf_t ;
struct TYPE_26__ {scalar_t__ delayed; scalar_t__ timer_set; } ;
typedef  TYPE_6__ ngx_event_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_21__ {int buffered; int /*<<< orphan*/  log; TYPE_6__* write; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TBOOLEAN ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_LOWLEVEL_BUFFERED ; 
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,unsigned int,...) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 unsigned int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_6__*) ; 
 scalar_t__ ngx_handle_write_event (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_core_run_phases ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_content_wev_handler ; 
 int /*<<< orphan*/  ngx_http_lua_flush_cleanup ; 
 int /*<<< orphan*/ * ngx_http_lua_get_flush_chain (TYPE_2__*,TYPE_3__*) ; 
 TYPE_2__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_send_chain_link (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,scalar_t__) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_flush(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;
    ngx_chain_t                 *cl;
    ngx_int_t                    rc;
    int                          n;
    unsigned                     wait = 0;
    ngx_event_t                 *wev;
    ngx_http_core_loc_conf_t    *clcf;
    ngx_http_lua_co_ctx_t       *coctx;

    n = lua_gettop(L);
    if (n > 1) {
        return luaL_error(L, "attempt to pass %d arguments, but accepted 0 "
                          "or 1", n);
    }

    r = ngx_http_lua_get_req(L);

    if (n == 1 && r == r->main) {
        luaL_checktype(L, 1, LUA_TBOOLEAN);
        wait = lua_toboolean(L, 1);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                               | NGX_HTTP_LUA_CONTEXT_ACCESS
                               | NGX_HTTP_LUA_CONTEXT_CONTENT);

    if (ctx->acquired_raw_req_socket) {
        lua_pushnil(L);
        lua_pushliteral(L, "raw request socket acquired");
        return 2;
    }

    coctx = ctx->cur_co_ctx;
    if (coctx == NULL) {
        return luaL_error(L, "no co ctx found");
    }

    if (r->header_only) {
        lua_pushnil(L);
        lua_pushliteral(L, "header only");
        return 2;
    }

    if (ctx->eof) {
        lua_pushnil(L);
        lua_pushliteral(L, "seen eof");
        return 2;
    }

    if (ctx->buffering) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua http 1.0 buffering makes ngx.flush() a no-op");

        lua_pushnil(L);
        lua_pushliteral(L, "buffering");
        return 2;
    }

#if 1
    if ((!r->header_sent && !ctx->header_sent)
        || (!ctx->seen_body_data && !wait))
    {
        lua_pushnil(L);
        lua_pushliteral(L, "nothing to flush");
        return 2;
    }
#endif

    cl = ngx_http_lua_get_flush_chain(r, ctx);
    if (cl == NULL) {
        return luaL_error(L, "no memory");
    }

    rc = ngx_http_lua_send_chain_link(r, ctx, cl);

    dd("send chain: %d", (int) rc);

    if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        lua_pushnil(L);
        lua_pushliteral(L, "nginx output filter error");
        return 2;
    }

    dd("wait:%d, rc:%d, buffered:0x%x", wait, (int) rc,
       r->connection->buffered);

    wev = r->connection->write;

    if (wait && (r->connection->buffered & NGX_HTTP_LOWLEVEL_BUFFERED
                 || wev->delayed))
    {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua flush requires waiting: buffered 0x%uxd, "
                       "delayed:%d", (unsigned) r->connection->buffered,
                       wev->delayed);

        coctx->flushing = 1;
        ctx->flushing_coros++;

        if (ctx->entered_content_phase) {
            /* mimic ngx_http_set_write_handler */
            r->write_event_handler = ngx_http_lua_content_wev_handler;

        } else {
            r->write_event_handler = ngx_http_core_run_phases;
        }

        clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

        if (!wev->delayed) {
            ngx_add_timer(wev, clcf->send_timeout);
        }

        if (ngx_handle_write_event(wev, clcf->send_lowat) != NGX_OK) {
            if (wev->timer_set) {
                wev->delayed = 0;
                ngx_del_timer(wev);
            }

            lua_pushnil(L);
            lua_pushliteral(L, "connection broken");
            return 2;
        }

        ngx_http_lua_cleanup_pending_operation(ctx->cur_co_ctx);
        coctx->cleanup = ngx_http_lua_flush_cleanup;
        coctx->data = r;

        return lua_yield(L, 0);
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua flush asynchronously");

    lua_pushinteger(L, 1);
    return 1;
}