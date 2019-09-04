#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* socket_pool; TYPE_2__* request; } ;
typedef  TYPE_4__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_10__ {int /*<<< orphan*/  queue; TYPE_4__* u; } ;
typedef  TYPE_5__ ngx_http_lua_socket_tcp_conn_op_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  cache_connect_op; } ;
struct TYPE_7__ {int /*<<< orphan*/  uri; TYPE_1__* connection; } ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_conn_op_ctx_cleanup(void *data)
{
    ngx_http_lua_socket_tcp_upstream_t     *u;
    ngx_http_lua_socket_tcp_conn_op_ctx_t  *conn_op_ctx = data;

    u = conn_op_ctx->u;
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, u->request->connection->log, 0,
                   "cleanup lua tcp socket conn_op_ctx: \"%V\"",
                   &u->request->uri);

    ngx_queue_insert_head(&u->socket_pool->cache_connect_op,
                          &conn_op_ctx->queue);
}