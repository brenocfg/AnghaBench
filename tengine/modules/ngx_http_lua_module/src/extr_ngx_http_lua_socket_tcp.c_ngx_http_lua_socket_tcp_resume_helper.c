#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int ngx_int_t ;
struct TYPE_26__ {TYPE_8__* connection; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_27__ {int (* write_prepare_retvals ) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ;int (* read_prepare_retvals ) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_13__* socket_pool; int /*<<< orphan*/  conn_closed; struct TYPE_27__* u; } ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_upstream_t ;
typedef  int (* ngx_http_lua_socket_tcp_retval_handler ) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_conn_op_ctx_t ;
struct TYPE_28__ {scalar_t__ entered_content_phase; TYPE_7__* cur_co_ctx; int /*<<< orphan*/  resume_handler; } ;
typedef  TYPE_6__ ngx_http_lua_ctx_t ;
struct TYPE_29__ {int /*<<< orphan*/  co; TYPE_2__* data; } ;
typedef  TYPE_7__ ngx_http_lua_co_ctx_t ;
struct TYPE_30__ {int /*<<< orphan*/  log; int /*<<< orphan*/  requests; } ;
typedef  TYPE_8__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_25__ {int /*<<< orphan*/  connections; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
 int NGX_DONE ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
#define  SOCKET_OP_CONNECT 131 
#define  SOCKET_OP_READ 130 
#define  SOCKET_OP_RESUME_CONN 129 
#define  SOCKET_OP_WRITE 128 
 int /*<<< orphan*/  dd (char*,TYPE_7__*) ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_finalize_request (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_lua_vm (TYPE_1__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int ngx_http_lua_run_posted_threads (TYPE_8__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int ngx_http_lua_run_thread (int /*<<< orphan*/ *,TYPE_1__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_resume_conn_op (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_http_lua_wev_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int (*) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ),TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_tcp_resume_helper(ngx_http_request_t *r, int socket_op)
{
    int                                    nret;
    lua_State                             *vm;
    ngx_int_t                              rc;
    ngx_uint_t                             nreqs;
    ngx_connection_t                      *c;
    ngx_http_lua_ctx_t                    *ctx;
    ngx_http_lua_co_ctx_t                 *coctx;
    ngx_http_lua_socket_tcp_conn_op_ctx_t *conn_op_ctx;

    ngx_http_lua_socket_tcp_retval_handler  prepare_retvals;

    ngx_http_lua_socket_tcp_upstream_t      *u;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ctx->resume_handler = ngx_http_lua_wev_handler;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp operation done, resuming lua thread");

    coctx = ctx->cur_co_ctx;

    dd("coctx: %p", coctx);

    switch (socket_op) {

    case SOCKET_OP_RESUME_CONN:
        conn_op_ctx = coctx->data;
        u = conn_op_ctx->u;
        prepare_retvals = u->write_prepare_retvals;
        break;

    case SOCKET_OP_CONNECT:
    case SOCKET_OP_WRITE:
        u = coctx->data;
        prepare_retvals = u->write_prepare_retvals;
        break;

    case SOCKET_OP_READ:
        u = coctx->data;
        prepare_retvals = u->read_prepare_retvals;
        break;

    default:
        /* impossible to reach here */
        return NGX_ERROR;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket calling prepare retvals handler %p, "
                   "u:%p", prepare_retvals, u);

    nret = prepare_retvals(r, u, ctx->cur_co_ctx->co);
    if (socket_op == SOCKET_OP_CONNECT
        && nret > 1
        && !u->conn_closed
        && u->socket_pool != NULL)
    {
        u->socket_pool->connections--;
        ngx_http_lua_socket_tcp_resume_conn_op(u->socket_pool);
    }

    if (nret == NGX_AGAIN) {
        return NGX_DONE;
    }

    c = r->connection;
    vm = ngx_http_lua_get_lua_vm(r, ctx);
    nreqs = c->requests;

    rc = ngx_http_lua_run_thread(vm, r, ctx, nret);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua run thread returned %d", rc);

    if (rc == NGX_AGAIN) {
        return ngx_http_lua_run_posted_threads(c, vm, r, ctx, nreqs);
    }

    if (rc == NGX_DONE) {
        ngx_http_lua_finalize_request(r, NGX_DONE);
        return ngx_http_lua_run_posted_threads(c, vm, r, ctx, nreqs);
    }

    if (ctx->entered_content_phase) {
        ngx_http_lua_finalize_request(r, rc);
        return NGX_DONE;
    }

    return rc;
}