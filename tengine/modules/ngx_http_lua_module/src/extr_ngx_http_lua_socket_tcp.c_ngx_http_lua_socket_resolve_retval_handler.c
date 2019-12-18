#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_27__ ;
typedef  struct TYPE_32__   TYPE_25__ ;
typedef  struct TYPE_31__   TYPE_24__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct TYPE_35__ {TYPE_10__* connection; int /*<<< orphan*/  get; int /*<<< orphan*/ * name; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
typedef  TYPE_3__ ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_36__ {int /*<<< orphan*/  host; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
typedef  TYPE_4__ ngx_http_upstream_resolved_t ;
struct TYPE_37__ {int /*<<< orphan*/  write_event_handler; TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_30__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ ** last; } ;
struct TYPE_38__ {int ft_type; int conn_waiting; int /*<<< orphan*/  write_prepare_retvals; TYPE_8__* write_co_ctx; int /*<<< orphan*/  connect_timeout; void* write_event_handler; void* read_event_handler; TYPE_1__ writer; void* socket_errno; int /*<<< orphan*/ * cleanup; TYPE_4__* resolved; TYPE_3__ peer; } ;
typedef  TYPE_6__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_39__ {scalar_t__ entered_content_phase; TYPE_8__* cur_co_ctx; } ;
typedef  TYPE_7__ ngx_http_lua_ctx_t ;
struct TYPE_40__ {TYPE_6__* data; int /*<<< orphan*/  cleanup; } ;
typedef  TYPE_8__ ngx_http_lua_co_ctx_t ;
struct TYPE_41__ {int /*<<< orphan*/  handler; TYPE_6__* data; } ;
typedef  TYPE_9__ ngx_http_cleanup_t ;
struct TYPE_29__ {TYPE_24__* write; TYPE_25__* read; scalar_t__ fd; int /*<<< orphan*/  log; TYPE_27__* pool; int /*<<< orphan*/  sendfile; TYPE_6__* data; } ;
typedef  TYPE_10__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_34__ {int /*<<< orphan*/  log; int /*<<< orphan*/  sendfile; } ;
struct TYPE_33__ {int /*<<< orphan*/  log; } ;
struct TYPE_32__ {int /*<<< orphan*/  log; void* handler; } ;
struct TYPE_31__ {int /*<<< orphan*/  log; void* handler; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_LUA_SOCKET_FT_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_NOMEM ; 
 int NGX_HTTP_LUA_SOCKET_FT_RESOLVER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_24__*,int /*<<< orphan*/ ) ; 
 TYPE_27__* ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_event_connect_peer (TYPE_3__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_25__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_write_event (TYPE_24__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_run_phases ; 
 TYPE_7__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* ngx_http_lua_cleanup_add (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_lua_coctx_cleanup ; 
 int /*<<< orphan*/  ngx_http_lua_content_wev_handler ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int ngx_http_lua_socket_conn_error_retval_handler (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 void* ngx_http_lua_socket_connected_handler ; 
 void* ngx_http_lua_socket_dummy_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_handle_conn_error (TYPE_5__*,TYPE_6__*,int) ; 
 int ngx_http_lua_socket_prepare_error_retvals (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_cleanup ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_conn_retval_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_get_peer ; 
 void* ngx_http_lua_socket_tcp_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 void* ngx_socket_errno ; 

__attribute__((used)) static int
ngx_http_lua_socket_resolve_retval_handler(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u, lua_State *L)
{
    ngx_http_lua_ctx_t              *ctx;
    ngx_peer_connection_t           *pc;
    ngx_connection_t                *c;
    ngx_http_cleanup_t              *cln;
    ngx_http_upstream_resolved_t    *ur;
    ngx_int_t                        rc;
    ngx_http_lua_co_ctx_t           *coctx;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket resolve retval handler");

    if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_RESOLVER) {
        return 2;
    }

    pc = &u->peer;

    ur = u->resolved;

    if (ur->sockaddr) {
        pc->sockaddr = ur->sockaddr;
        pc->socklen = ur->socklen;
        pc->name = &ur->host;

    } else {
        lua_pushnil(L);
        lua_pushliteral(L, "resolver not working");
        return 2;
    }

    pc->get = ngx_http_lua_socket_tcp_get_peer;

    rc = ngx_event_connect_peer(pc);

    if (rc == NGX_ERROR) {
        u->socket_errno = ngx_socket_errno;
    }

    if (u->cleanup == NULL) {
        cln = ngx_http_lua_cleanup_add(r, 0);
        if (cln == NULL) {
            u->ft_type |= NGX_HTTP_LUA_SOCKET_FT_ERROR;
            lua_pushnil(L);
            lua_pushliteral(L, "no memory");
            return 2;
        }

        cln->handler = ngx_http_lua_socket_tcp_cleanup;
        cln->data = u;
        u->cleanup = &cln->handler;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket connect: %i", rc);

    if (rc == NGX_ERROR) {
        return ngx_http_lua_socket_conn_error_retval_handler(r, u, L);
    }

    if (rc == NGX_BUSY) {
        u->ft_type |= NGX_HTTP_LUA_SOCKET_FT_ERROR;
        lua_pushnil(L);
        lua_pushliteral(L, "no live connection");
        return 2;
    }

    if (rc == NGX_DECLINED) {
        dd("socket errno: %d", (int) ngx_socket_errno);
        u->ft_type |= NGX_HTTP_LUA_SOCKET_FT_ERROR;
        u->socket_errno = ngx_socket_errno;
        return ngx_http_lua_socket_conn_error_retval_handler(r, u, L);
    }

    /* rc == NGX_OK || rc == NGX_AGAIN */

    c = pc->connection;

    c->data = u;

    c->write->handler = ngx_http_lua_socket_tcp_handler;
    c->read->handler = ngx_http_lua_socket_tcp_handler;

    u->write_event_handler = ngx_http_lua_socket_connected_handler;
    u->read_event_handler = ngx_http_lua_socket_connected_handler;

    c->sendfile &= r->connection->sendfile;

    if (c->pool == NULL) {

        /* we need separate pool here to be able to cache SSL connections */

        c->pool = ngx_create_pool(128, r->connection->log);
        if (c->pool == NULL) {
            return ngx_http_lua_socket_prepare_error_retvals(r, u, L,
                                                NGX_HTTP_LUA_SOCKET_FT_NOMEM);
        }
    }

    c->log = r->connection->log;
    c->pool->log = c->log;
    c->read->log = c->log;
    c->write->log = c->log;

    /* init or reinit the ngx_output_chain() and ngx_chain_writer() contexts */

#if 0
    u->writer.out = NULL;
    u->writer.last = &u->writer.out;
#endif

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    coctx = ctx->cur_co_ctx;

    dd("setting data to %p", u);

    if (rc == NGX_OK) {
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua tcp socket connected: fd:%d", (int) c->fd);

        /* We should delete the current write/read event
         * here because the socket object may not be used immediately
         * on the Lua land, thus causing hot spin around level triggered
         * event poll and wasting CPU cycles. */

        if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
            ngx_http_lua_socket_handle_conn_error(r, u,
                                                  NGX_HTTP_LUA_SOCKET_FT_ERROR);
            lua_pushnil(L);
            lua_pushliteral(L, "failed to handle write event");
            return 2;
        }

        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            ngx_http_lua_socket_handle_conn_error(r, u,
                                                  NGX_HTTP_LUA_SOCKET_FT_ERROR);
            lua_pushnil(L);
            lua_pushliteral(L, "failed to handle read event");
            return 2;
        }

        u->read_event_handler = ngx_http_lua_socket_dummy_handler;
        u->write_event_handler = ngx_http_lua_socket_dummy_handler;

        lua_pushinteger(L, 1);
        return 1;
    }

    /* rc == NGX_AGAIN */

    ngx_http_lua_cleanup_pending_operation(coctx);
    coctx->cleanup = ngx_http_lua_coctx_cleanup;
    coctx->data = u;

    ngx_add_timer(c->write, u->connect_timeout);

    u->write_co_ctx = ctx->cur_co_ctx;
    u->conn_waiting = 1;
    u->write_prepare_retvals = ngx_http_lua_socket_tcp_conn_retval_handler;

    dd("setting data to %p", u);

    if (ctx->entered_content_phase) {
        r->write_event_handler = ngx_http_lua_content_wev_handler;

    } else {
        r->write_event_handler = ngx_http_core_run_phases;
    }

    return NGX_AGAIN;
}