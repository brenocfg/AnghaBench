#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {scalar_t__ read_event_handler; void* write_event_handler; int /*<<< orphan*/  ctx; TYPE_1__* connection; scalar_t__ filter_finalize; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_23__ {scalar_t__ len; } ;
struct TYPE_24__ {char* data; scalar_t__ len; } ;
struct TYPE_22__ {char* entered_content_phase; TYPE_4__ exec_args; TYPE_5__ exec_uri; TYPE_15__* cur_co_ctx; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;
struct TYPE_19__ {int /*<<< orphan*/  co_status; int /*<<< orphan*/  co; } ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_DEAD ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/  dd (char*,int,char*) ; 
 void* ngx_http_block_reading ; 
 scalar_t__ ngx_http_internal_redirect (TYPE_2__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_15__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_coroutine_done (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_http_lua_rd_check_broken_connection ; 
 int /*<<< orphan*/  ngx_http_lua_request_cleanup (TYPE_3__*,int) ; 
 int ngx_http_max_module ; 
 scalar_t__ ngx_http_named_location (TYPE_2__*,TYPE_5__*) ; 
 void* ngx_http_request_empty_handler ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_memzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_handle_exec(lua_State *L, ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx)
{
    ngx_int_t               rc;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua thread initiated internal redirect to %V",
                   &ctx->exec_uri);

    ngx_http_lua_cleanup_pending_operation(ctx->cur_co_ctx);

    ngx_http_lua_probe_coroutine_done(r, ctx->cur_co_ctx->co, 1);

    ctx->cur_co_ctx->co_status = NGX_HTTP_LUA_CO_DEAD;

    if (r->filter_finalize) {
        ngx_http_set_ctx(r, ctx, ngx_http_lua_module);
    }

    ngx_http_lua_request_cleanup(ctx, 1 /* forcible */);

    if (ctx->exec_uri.data[0] == '@') {
        if (ctx->exec_args.len > 0) {
            ngx_log_error(NGX_LOG_WARN, r->connection->log, 0,
                          "query strings %V ignored when exec'ing "
                          "named location %V",
                          &ctx->exec_args, &ctx->exec_uri);
        }

        r->write_event_handler = ngx_http_request_empty_handler;

#if 1
        if (r->read_event_handler == ngx_http_lua_rd_check_broken_connection) {
            /* resume the read event handler */

            r->read_event_handler = ngx_http_block_reading;
        }
#endif

#if 1
        /* clear the modules contexts */
        ngx_memzero(r->ctx, sizeof(void *) * ngx_http_max_module);
#endif

        rc = ngx_http_named_location(r, &ctx->exec_uri);
        if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }

#if 0
        if (!ctx->entered_content_phase) {
            /* XXX ensure the main request ref count
             * is decreased because the current
             * request will be quit */
            r->main->count--;
            dd("XXX decrement main count: c:%d", (int) r->main->count);
        }
#endif

        return NGX_DONE;
    }

    dd("internal redirect to %.*s", (int) ctx->exec_uri.len,
       ctx->exec_uri.data);

    r->write_event_handler = ngx_http_request_empty_handler;

    if (r->read_event_handler == ngx_http_lua_rd_check_broken_connection) {
        /* resume the read event handler */

        r->read_event_handler = ngx_http_block_reading;
    }

    rc = ngx_http_internal_redirect(r, &ctx->exec_uri, &ctx->exec_args);

    dd("internal redirect returned %d when in content phase? "
       "%d", (int) rc, ctx->entered_content_phase);

    if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

#if 0
    if (!ctx->entered_content_phase) {
        /* XXX ensure the main request ref count
         * is decreased because the current
         * request will be quit */
        dd("XXX decrement main count");
        r->main->count--;
    }
#endif

    return NGX_DONE;
}