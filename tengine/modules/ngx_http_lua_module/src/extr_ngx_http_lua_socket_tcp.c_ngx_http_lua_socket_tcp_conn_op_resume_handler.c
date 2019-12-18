#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_queue_t ;
struct TYPE_21__ {TYPE_9__* connection; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_22__ {int /*<<< orphan*/  write_prepare_retvals; TYPE_6__* write_co_ctx; TYPE_4__* socket_pool; TYPE_1__* request; } ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_23__ {int /*<<< orphan*/ * cleanup; int /*<<< orphan*/  queue; TYPE_2__* u; } ;
typedef  TYPE_3__ ngx_http_lua_socket_tcp_conn_op_ctx_t ;
struct TYPE_24__ {scalar_t__ backlog; scalar_t__ connections; scalar_t__ size; int /*<<< orphan*/  cache_connect_op; int /*<<< orphan*/  wait_connect_op; int /*<<< orphan*/  key; } ;
typedef  TYPE_4__ ngx_http_lua_socket_pool_t ;
struct TYPE_25__ {int /*<<< orphan*/  (* resume_handler ) (TYPE_1__*) ;scalar_t__ entered_content_phase; TYPE_6__* cur_co_ctx; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
struct TYPE_26__ {scalar_t__ co_ref; TYPE_3__* data; int /*<<< orphan*/ * cleanup; } ;
typedef  TYPE_6__ ngx_http_lua_co_ctx_t ;
struct TYPE_27__ {int /*<<< orphan*/  handler; TYPE_3__* data; } ;
typedef  TYPE_7__ ngx_http_cleanup_t ;
struct TYPE_28__ {TYPE_3__* data; } ;
typedef  TYPE_8__ ngx_event_t ;
struct TYPE_29__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 TYPE_19__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_core_run_phases (TYPE_1__*) ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_assert (int) ; 
 TYPE_7__* ngx_http_lua_cleanup_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_is_thread (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_conn_op_ctx_cleanup ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_conn_op_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_conn_op_resume_retval_handler ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_queue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_conn_op_resume_handler(ngx_event_t *ev)
{
    ngx_queue_t                             *q;
    ngx_connection_t                        *c;
    ngx_http_lua_ctx_t                      *ctx;
    ngx_http_request_t                      *r;
    ngx_http_cleanup_t                      *cln;
    ngx_http_lua_co_ctx_t                   *coctx;
    ngx_http_lua_socket_pool_t              *spool;
    ngx_http_lua_socket_tcp_upstream_t      *u;
    ngx_http_lua_socket_tcp_conn_op_ctx_t   *conn_op_ctx;

    conn_op_ctx = ev->data;
    u = conn_op_ctx->u;
    r = u->request;
    spool = u->socket_pool;

    if (ngx_queue_empty(&spool->wait_connect_op)) {
#if (NGX_DEBUG)
        ngx_http_lua_assert(!(spool->backlog >= 0
                              && spool->connections > spool->size));

#else
        if (spool->backlog >= 0 && spool->connections > spool->size) {
            ngx_log_error(NGX_LOG_ERR, ngx_cycle->log, 0,
                          "lua tcp socket connections count mismatched for "
                          "connection pool \"%s\", connections: %i, size: %i",
                          spool->key, spool->connections, spool->size);
            spool->connections = spool->size;
        }
#endif

        return;
    }

    q = ngx_queue_head(&spool->wait_connect_op);
    ngx_queue_remove(q);

    coctx = u->write_co_ctx;
    coctx->cleanup = NULL;
    /* note that we store conn_op_ctx in coctx->data instead of u */
    coctx->data = conn_op_ctx;
    /* clear ngx_http_lua_tcp_queue_conn_op_cleanup */
    u->write_co_ctx = NULL;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        ngx_queue_insert_head(&spool->cache_connect_op,
                              &conn_op_ctx->queue);
        return;
    }

    ctx->cur_co_ctx = coctx;

    ngx_http_lua_assert(coctx && (!ngx_http_lua_is_thread(ctx)
                        || coctx->co_ref >= 0));

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket waking up the current request");

    u->write_prepare_retvals =
        ngx_http_lua_socket_tcp_conn_op_resume_retval_handler;

    c = r->connection;

    if (ctx->entered_content_phase) {
        (void) ngx_http_lua_socket_tcp_conn_op_resume(r);

    } else {
        cln = ngx_http_lua_cleanup_add(r, 0);
        if (cln != NULL) {
            cln->handler = ngx_http_lua_socket_tcp_conn_op_ctx_cleanup;
            cln->data = conn_op_ctx;
            conn_op_ctx->cleanup = &cln->handler;
        }

        ctx->resume_handler = ngx_http_lua_socket_tcp_conn_op_resume;
        ngx_http_core_run_phases(r);
    }

    ngx_http_run_posted_requests(c);
}