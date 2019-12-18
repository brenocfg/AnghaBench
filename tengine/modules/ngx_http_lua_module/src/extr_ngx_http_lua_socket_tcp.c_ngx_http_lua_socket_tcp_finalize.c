#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_3__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_25__ {int /*<<< orphan*/ * connection; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_23__ {int conn_closed; TYPE_6__* socket_pool; TYPE_7__ peer; TYPE_2__ ssl_name; TYPE_1__* resolved; scalar_t__ body_downstream; scalar_t__ raw_downstream; int /*<<< orphan*/ ** cleanup; } ;
typedef  TYPE_5__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_24__ {scalar_t__ connections; } ;
typedef  TYPE_6__ ngx_http_lua_socket_pool_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;
struct TYPE_19__ {int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_free (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_free_pool (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_close_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_finalize_read_part (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_finalize_write_part (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_resume_conn_op (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_finalize(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u)
{
    ngx_connection_t               *c;
    ngx_http_lua_socket_pool_t     *spool;

    dd("request: %p, u: %p, u->cleanup: %p", r, u, u->cleanup);

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua finalize socket");

    if (u->cleanup) {
        *u->cleanup = NULL;
        ngx_http_lua_cleanup_free(r, u->cleanup);
        u->cleanup = NULL;
    }

    ngx_http_lua_socket_tcp_finalize_read_part(r, u);
    ngx_http_lua_socket_tcp_finalize_write_part(r, u);

    if (u->raw_downstream || u->body_downstream) {
        u->peer.connection = NULL;
        return;
    }

    if (u->resolved && u->resolved->ctx) {
        ngx_resolve_name_done(u->resolved->ctx);
        u->resolved->ctx = NULL;
    }

    if (u->peer.free) {
        u->peer.free(&u->peer, u->peer.data, 0);
    }

#if (NGX_HTTP_SSL)
    if (u->ssl_name.data) {
        ngx_free(u->ssl_name.data);
        u->ssl_name.data = NULL;
        u->ssl_name.len = 0;
    }
#endif

    c = u->peer.connection;
    if (c) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua close socket connection");

        ngx_http_lua_socket_tcp_close_connection(c);
        u->peer.connection = NULL;
        u->conn_closed = 1;

        spool = u->socket_pool;
        if (spool == NULL) {
            return;
        }

        spool->connections--;

        if (spool->connections == 0) {
            ngx_http_lua_socket_free_pool(r->connection->log, spool);
            return;
        }

        ngx_http_lua_socket_tcp_resume_conn_op(spool);
    }
}