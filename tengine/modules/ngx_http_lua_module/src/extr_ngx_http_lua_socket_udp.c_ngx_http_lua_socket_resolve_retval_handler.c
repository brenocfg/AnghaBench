#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {int /*<<< orphan*/  host; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
typedef  TYPE_4__ ngx_http_upstream_resolved_t ;
struct TYPE_27__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_28__ {TYPE_11__* connection; int /*<<< orphan*/  server; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
typedef  TYPE_6__ ngx_http_lua_udp_connection_t ;
struct TYPE_29__ {int ft_type; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/ * cleanup; int /*<<< orphan*/  socket_errno; TYPE_4__* resolved; TYPE_6__ udp_connection; } ;
typedef  TYPE_7__ ngx_http_lua_socket_udp_upstream_t ;
struct TYPE_30__ {TYPE_9__* cur_co_ctx; } ;
typedef  TYPE_8__ ngx_http_lua_ctx_t ;
struct TYPE_31__ {TYPE_7__* data; } ;
typedef  TYPE_9__ ngx_http_lua_co_ctx_t ;
struct TYPE_21__ {int /*<<< orphan*/  handler; TYPE_7__* data; } ;
typedef  TYPE_10__ ngx_http_cleanup_t ;
struct TYPE_22__ {int /*<<< orphan*/  log; TYPE_3__* write; TYPE_2__* read; int /*<<< orphan*/  pool; TYPE_7__* data; } ;
typedef  TYPE_11__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_25__ {int /*<<< orphan*/  log; int /*<<< orphan*/ * handler; } ;
struct TYPE_24__ {int /*<<< orphan*/  log; scalar_t__ resolver; int /*<<< orphan*/  handler; } ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_SOCKET_FT_ERROR ; 
 int NGX_HTTP_LUA_SOCKET_FT_RESOLVER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 TYPE_10__* ngx_http_cleanup_add (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_dummy_handler ; 
 int ngx_http_lua_socket_error_retval_handler (TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_cleanup ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_handler ; 
 scalar_t__ ngx_http_lua_udp_connect (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 

__attribute__((used)) static int
ngx_http_lua_socket_resolve_retval_handler(ngx_http_request_t *r,
    ngx_http_lua_socket_udp_upstream_t *u, lua_State *L)
{
    ngx_http_lua_ctx_t              *ctx;
    ngx_http_lua_co_ctx_t           *coctx;
    ngx_connection_t                *c;
    ngx_http_cleanup_t              *cln;
    ngx_http_upstream_resolved_t    *ur;
    ngx_int_t                        rc;
    ngx_http_lua_udp_connection_t   *uc;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua udp socket resolve retval handler");

    if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_RESOLVER) {
        return 2;
    }

    uc = &u->udp_connection;

    ur = u->resolved;

    if (ur->sockaddr) {
        uc->sockaddr = ur->sockaddr;
        uc->socklen = ur->socklen;
        uc->server = ur->host;

    } else {
        lua_pushnil(L);
        lua_pushliteral(L, "resolver not working");
        return 2;
    }

    rc = ngx_http_lua_udp_connect(uc);

    if (rc != NGX_OK) {
        u->socket_errno = ngx_socket_errno;
    }

    if (u->cleanup == NULL) {
        cln = ngx_http_cleanup_add(r, 0);
        if (cln == NULL) {
            u->ft_type |= NGX_HTTP_LUA_SOCKET_FT_ERROR;
            lua_pushnil(L);
            lua_pushliteral(L, "no memory");
            return 2;
        }

        cln->handler = ngx_http_lua_socket_udp_cleanup;
        cln->data = u;
        u->cleanup = &cln->handler;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua udp socket connect: %i", rc);

    if (rc != NGX_OK) {
        return ngx_http_lua_socket_error_retval_handler(r, u, L);
    }

    /* rc == NGX_OK */

    c = uc->connection;

    c->data = u;

    c->write->handler = NULL;
    c->read->handler = ngx_http_lua_socket_udp_handler;
    c->read->resolver = 0;

    c->pool = r->pool;
    c->log = r->connection->log;
    c->read->log = c->log;
    c->write->log = c->log;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    coctx = ctx->cur_co_ctx;

    coctx->data = u;

    u->read_event_handler = ngx_http_lua_socket_dummy_handler;

    lua_pushinteger(L, 1);
    return 1;
}