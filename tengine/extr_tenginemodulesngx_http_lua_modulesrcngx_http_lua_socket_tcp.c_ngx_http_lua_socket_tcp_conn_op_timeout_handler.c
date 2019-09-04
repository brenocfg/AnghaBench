#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_9__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_21__ {int /*<<< orphan*/  write_prepare_retvals; TYPE_1__* socket_pool; TYPE_7__* write_co_ctx; TYPE_2__* request; } ;
typedef  TYPE_3__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_22__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  port; int /*<<< orphan*/  host; TYPE_3__* u; } ;
typedef  TYPE_4__ ngx_http_lua_socket_tcp_conn_op_ctx_t ;
struct TYPE_23__ {scalar_t__ log_socket_errors; } ;
typedef  TYPE_5__ ngx_http_lua_loc_conf_t ;
struct TYPE_24__ {int /*<<< orphan*/  (* resume_handler ) (TYPE_2__*) ;scalar_t__ entered_content_phase; TYPE_7__* cur_co_ctx; } ;
typedef  TYPE_6__ ngx_http_lua_ctx_t ;
struct TYPE_25__ {scalar_t__ co_ref; TYPE_4__* data; int /*<<< orphan*/ * cleanup; } ;
typedef  TYPE_7__ ngx_http_lua_co_ctx_t ;
struct TYPE_26__ {TYPE_4__* data; } ;
typedef  TYPE_8__ ngx_event_t ;
struct TYPE_27__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_19__ {int /*<<< orphan*/  connections; int /*<<< orphan*/  cache_connect_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_http_core_run_phases (TYPE_2__*) ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_is_thread (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_conn_op_resume (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_conn_op_timeout_retval_handler ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_conn_op_timeout_handler(ngx_event_t *ev)
{
    ngx_http_lua_socket_tcp_upstream_t      *u;
    ngx_http_lua_ctx_t                      *ctx;
    ngx_connection_t                        *c;
    ngx_http_request_t                      *r;
    ngx_http_lua_co_ctx_t                   *coctx;
    ngx_http_lua_loc_conf_t                 *llcf;
    ngx_http_lua_socket_tcp_conn_op_ctx_t   *conn_op_ctx;

    conn_op_ctx = ev->data;
    ngx_queue_remove(&conn_op_ctx->queue);

    u = conn_op_ctx->u;
    r = u->request;

    coctx = u->write_co_ctx;
    coctx->cleanup = NULL;
    /* note that we store conn_op_ctx in coctx->data instead of u */
    coctx->data = conn_op_ctx;
    u->write_co_ctx = NULL;

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

    if (llcf->log_socket_errors) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "lua tcp socket queued connect timed out,"
                      " when trying to connect to %V:%ud",
                      &conn_op_ctx->host, conn_op_ctx->port);
    }

    ngx_queue_insert_head(&u->socket_pool->cache_connect_op,
                          &conn_op_ctx->queue);
    u->socket_pool->connections--;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return;
    }

    ctx->cur_co_ctx = coctx;

    ngx_http_lua_assert(coctx && (!ngx_http_lua_is_thread(ctx)
                        || coctx->co_ref >= 0));

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket waking up the current request");

    u->write_prepare_retvals =
        ngx_http_lua_socket_tcp_conn_op_timeout_retval_handler;

    c = r->connection;

    if (ctx->entered_content_phase) {
        (void) ngx_http_lua_socket_tcp_conn_op_resume(r);

    } else {
        ctx->resume_handler = ngx_http_lua_socket_tcp_conn_op_resume;
        ngx_http_core_run_phases(r);
    }

    ngx_http_run_posted_requests(c);
}