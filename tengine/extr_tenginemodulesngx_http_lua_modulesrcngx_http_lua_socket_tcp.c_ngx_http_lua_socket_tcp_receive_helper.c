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
typedef  scalar_t__ ngx_int_t ;
struct TYPE_19__ {int /*<<< orphan*/  write_event_handler; TYPE_2__* connection; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_20__ {int read_waiting; int (* read_prepare_retvals ) (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ;scalar_t__ body_downstream; scalar_t__ raw_downstream; struct TYPE_20__* read_co_ctx; struct TYPE_20__* data; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  read_event_handler; scalar_t__ ft_type; int /*<<< orphan*/  read_timeout; struct TYPE_20__* bufs_in; struct TYPE_20__* buf_in; int /*<<< orphan*/ * buf; int /*<<< orphan*/  buffer; TYPE_1__* conf; struct TYPE_20__* input_filter_ctx; } ;
typedef  TYPE_4__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_21__ {TYPE_4__* downstream; scalar_t__ entered_content_phase; TYPE_4__* cur_co_ctx; int /*<<< orphan*/  free_recv_bufs; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
typedef  TYPE_4__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;
struct TYPE_17__ {int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_run_phases ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_lua_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_coctx_cleanup ; 
 int /*<<< orphan*/  ngx_http_lua_content_wev_handler ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_req_socket_rev_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_read_handler ; 
 scalar_t__ ngx_http_lua_socket_tcp_read (TYPE_3__*,TYPE_4__*) ; 
 int ngx_http_lua_socket_tcp_receive_retval_handler (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngx_http_lua_socket_tcp_receive_helper(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u, lua_State *L)
{
    ngx_int_t                            rc;
    ngx_http_lua_ctx_t                  *ctx;
    ngx_http_lua_co_ctx_t               *coctx;

    u->input_filter_ctx = u;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    if (u->bufs_in == NULL) {
        u->bufs_in =
            ngx_http_lua_chain_get_free_buf(r->connection->log, r->pool,
                                            &ctx->free_recv_bufs,
                                            u->conf->buffer_size);

        if (u->bufs_in == NULL) {
            return luaL_error(L, "no memory");
        }

        u->buf_in = u->bufs_in;
        u->buffer = *u->buf_in->buf;
    }

    dd("tcp receive: buf_in: %p, bufs_in: %p", u->buf_in, u->bufs_in);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket read timeout: %M", u->read_timeout);

    if (u->raw_downstream || u->body_downstream) {
        r->read_event_handler = ngx_http_lua_req_socket_rev_handler;
    }

    u->read_waiting = 0;
    u->read_co_ctx = NULL;

    rc = ngx_http_lua_socket_tcp_read(r, u);

    if (rc == NGX_ERROR) {
        dd("read failed: %d", (int) u->ft_type);
        rc = ngx_http_lua_socket_tcp_receive_retval_handler(r, u, L);
        dd("tcp receive retval returned: %d", (int) rc);
        return rc;
    }

    if (rc == NGX_OK) {

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua tcp socket receive done in a single run");

        return ngx_http_lua_socket_tcp_receive_retval_handler(r, u, L);
    }

    /* rc == NGX_AGAIN */

    u->read_event_handler = ngx_http_lua_socket_read_handler;

    coctx = ctx->cur_co_ctx;

    ngx_http_lua_cleanup_pending_operation(coctx);
    coctx->cleanup = ngx_http_lua_coctx_cleanup;
    coctx->data = u;

    if (ctx->entered_content_phase) {
        r->write_event_handler = ngx_http_lua_content_wev_handler;

    } else {
        r->write_event_handler = ngx_http_core_run_phases;
    }

    u->read_co_ctx = coctx;
    u->read_waiting = 1;
    u->read_prepare_retvals = ngx_http_lua_socket_tcp_receive_retval_handler;

    dd("setting data to %p, coctx:%p", u, coctx);

    if (u->raw_downstream || u->body_downstream) {
        ctx->downstream = u;
    }

    return lua_yield(L, 0);
}