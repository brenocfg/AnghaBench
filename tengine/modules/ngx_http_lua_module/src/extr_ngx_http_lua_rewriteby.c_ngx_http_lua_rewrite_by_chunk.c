#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_29__ {int /*<<< orphan*/  write_event_handler; scalar_t__ header_sent; TYPE_7__* connection; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_30__ {scalar_t__ check_client_abort; } ;
typedef  TYPE_3__ ngx_http_lua_loc_conf_t ;
struct TYPE_28__ {int co_ref; int co_top; int /*<<< orphan*/ * co; } ;
struct TYPE_31__ {int entered_rewrite_phase; int /*<<< orphan*/  eof; int /*<<< orphan*/  context; int /*<<< orphan*/ * cleanup; TYPE_1__* cur_co_ctx; TYPE_1__ entry_co_ctx; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
struct TYPE_32__ {int /*<<< orphan*/  handler; TYPE_4__* data; } ;
typedef  TYPE_5__ ngx_http_cleanup_t ;
struct TYPE_33__ {int /*<<< orphan*/  active; } ;
typedef  TYPE_6__ ngx_event_t ;
struct TYPE_34__ {int /*<<< orphan*/  requests; TYPE_6__* read; int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 scalar_t__ NGX_HTTP_OK ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_add_event (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_block_reading ; 
 TYPE_5__* ngx_http_cleanup_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_run_phases ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_finalize_request (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_lua_get_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/ * ngx_http_lua_new_thread (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ngx_http_lua_rd_check_broken_connection ; 
 int /*<<< orphan*/  ngx_http_lua_request_cleanup_handler ; 
 int /*<<< orphan*/  ngx_http_lua_reset_ctx (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ ngx_http_lua_run_posted_threads (TYPE_7__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_run_thread (int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_send_chain_link (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_set_req (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_rewrite_by_chunk(lua_State *L, ngx_http_request_t *r)
{
    int                      co_ref;
    lua_State               *co;
    ngx_int_t                rc;
    ngx_uint_t               nreqs;
    ngx_event_t             *rev;
    ngx_connection_t        *c;
    ngx_http_lua_ctx_t      *ctx;
    ngx_http_cleanup_t      *cln;

    ngx_http_lua_loc_conf_t     *llcf;

    /*  {{{ new coroutine to handle request */
    co = ngx_http_lua_new_thread(r, L, &co_ref);

    if (co == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "lua: failed to create new coroutine to handle request");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    /*  move code closure to new coroutine */
    lua_xmove(L, co, 1);

#ifndef OPENRESTY_LUAJIT
    /*  set closure's env table to new coroutine's globals table */
    ngx_http_lua_get_globals_table(co);
    lua_setfenv(co, -2);
#endif

    /*  save nginx request in coroutine globals table */
    ngx_http_lua_set_req(co, r);

    /*  {{{ initialize request context */
    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    dd("ctx = %p", ctx);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_http_lua_reset_ctx(r, L, ctx);

    ctx->entered_rewrite_phase = 1;

    ctx->cur_co_ctx = &ctx->entry_co_ctx;
    ctx->cur_co_ctx->co = co;
    ctx->cur_co_ctx->co_ref = co_ref;
#ifdef NGX_LUA_USE_ASSERT
    ctx->cur_co_ctx->co_top = 1;
#endif

    /*  }}} */

    /*  {{{ register request cleanup hooks */
    if (ctx->cleanup == NULL) {
        cln = ngx_http_cleanup_add(r, 0);
        if (cln == NULL) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        cln->handler = ngx_http_lua_request_cleanup_handler;
        cln->data = ctx;
        ctx->cleanup = &cln->handler;
    }
    /*  }}} */

    ctx->context = NGX_HTTP_LUA_CONTEXT_REWRITE;

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

    if (llcf->check_client_abort) {
        r->read_event_handler = ngx_http_lua_rd_check_broken_connection;

#if (NGX_HTTP_V2)
        if (!r->stream) {
#endif

        rev = r->connection->read;

        if (!rev->active) {
            if (ngx_add_event(rev, NGX_READ_EVENT, 0) != NGX_OK) {
                return NGX_ERROR;
            }
        }

#if (NGX_HTTP_V2)
        }
#endif

    } else {
        r->read_event_handler = ngx_http_block_reading;
    }

    c = r->connection;
    nreqs = c->requests;

    rc = ngx_http_lua_run_thread(L, r, ctx, 0);

    if (rc == NGX_ERROR || rc > NGX_OK) {
        return rc;
    }

    if (rc == NGX_AGAIN) {
        rc = ngx_http_lua_run_posted_threads(c, L, r, ctx, nreqs);

    } else if (rc == NGX_DONE) {
        ngx_http_lua_finalize_request(r, NGX_DONE);
        rc = ngx_http_lua_run_posted_threads(c, L, r, ctx, nreqs);
    }

    if (rc == NGX_OK || rc == NGX_DECLINED) {
        if (r->header_sent) {
            dd("header already sent");

            /* response header was already generated in rewrite_by_lua*,
             * so it is no longer safe to proceed to later phases
             * which may generate responses again */

            if (!ctx->eof) {
                dd("eof not yet sent");

                rc = ngx_http_lua_send_chain_link(r, ctx, NULL
                                                  /* indicate last_buf */);
                if (rc == NGX_ERROR || rc > NGX_OK) {
                    return rc;
                }
            }

            return NGX_HTTP_OK;
        }

        r->write_event_handler = ngx_http_core_run_phases;
        ctx->entered_rewrite_phase = 0;

        return NGX_DECLINED;
    }

    return rc;
}