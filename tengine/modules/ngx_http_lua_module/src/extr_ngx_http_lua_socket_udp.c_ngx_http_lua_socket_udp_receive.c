#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_22__ {int /*<<< orphan*/  write_event_handler; TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_20__ {int /*<<< orphan*/ * connection; } ;
struct TYPE_23__ {int waiting; size_t read_timeout; size_t recv_buf_size; int (* prepare_retvals ) (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ;TYPE_7__* co_ctx; int /*<<< orphan*/  read_event_handler; scalar_t__ ft_type; TYPE_3__* request; TYPE_1__ udp_connection; } ;
typedef  TYPE_4__ ngx_http_lua_socket_udp_upstream_t ;
struct TYPE_24__ {scalar_t__ log_socket_errors; } ;
typedef  TYPE_5__ ngx_http_lua_loc_conf_t ;
struct TYPE_25__ {scalar_t__ entered_content_phase; TYPE_7__* cur_co_ctx; } ;
typedef  TYPE_6__ ngx_http_lua_ctx_t ;
struct TYPE_26__ {TYPE_4__* data; int /*<<< orphan*/  cleanup; } ;
typedef  TYPE_7__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  SOCKET_CTX_INDEX ; 
 int /*<<< orphan*/  UDP_MAX_DATAGRAM_SIZE ; 
 int /*<<< orphan*/  dd (char*,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ luaL_optnumber (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_run_phases ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_lua_content_wev_handler ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_socket_udp_read (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_read_handler ; 
 int ngx_http_lua_socket_udp_receive_retval_handler (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_udp_socket_cleanup ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 size_t ngx_min (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngx_http_lua_socket_udp_receive(lua_State *L)
{
    ngx_http_request_t                  *r;
    ngx_http_lua_socket_udp_upstream_t  *u;
    ngx_int_t                            rc;
    ngx_http_lua_ctx_t                  *ctx;
    ngx_http_lua_co_ctx_t               *coctx;
    size_t                               size;
    int                                  nargs;
    ngx_http_lua_loc_conf_t             *llcf;

    nargs = lua_gettop(L);
    if (nargs != 1 && nargs != 2) {
        return luaL_error(L, "expecting 1 or 2 arguments "
                          "(including the object), but got %d", nargs);
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua udp socket calling receive() method");

    luaL_checktype(L, 1, LUA_TTABLE);

    lua_rawgeti(L, 1, SOCKET_CTX_INDEX);
    u = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (u == NULL || u->udp_connection.connection == NULL) {
        llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

        if (llcf->log_socket_errors) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "attempt to receive data on a closed socket: u:%p, "
                          "c:%p", u, u ? u->udp_connection.connection : NULL);
        }

        lua_pushnil(L);
        lua_pushliteral(L, "closed");
        return 2;
    }

    if (u->request != r) {
        return luaL_error(L, "bad request");
    }

    if (u->ft_type) {
        u->ft_type = 0;
    }

#if 1
    if (u->waiting) {
        lua_pushnil(L);
        lua_pushliteral(L, "socket busy");
        return 2;
    }
#endif

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua udp socket read timeout: %M", u->read_timeout);

    size = (size_t) luaL_optnumber(L, 2, UDP_MAX_DATAGRAM_SIZE);
    size = ngx_min(size, UDP_MAX_DATAGRAM_SIZE);

    u->recv_buf_size = size;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua udp socket receive buffer size: %uz", u->recv_buf_size);

    rc = ngx_http_lua_socket_udp_read(r, u);

    if (rc == NGX_ERROR) {
        dd("read failed: %d", (int) u->ft_type);
        rc = ngx_http_lua_socket_udp_receive_retval_handler(r, u, L);
        dd("udp receive retval returned: %d", (int) rc);
        return rc;
    }

    if (rc == NGX_OK) {

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua udp socket receive done in a single run");

        return ngx_http_lua_socket_udp_receive_retval_handler(r, u, L);
    }

    /* n == NGX_AGAIN */

    u->read_event_handler = ngx_http_lua_socket_udp_read_handler;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    coctx = ctx->cur_co_ctx;

    ngx_http_lua_cleanup_pending_operation(coctx);
    coctx->cleanup = ngx_http_lua_udp_socket_cleanup;
    coctx->data = u;

    if (ctx->entered_content_phase) {
        r->write_event_handler = ngx_http_lua_content_wev_handler;

    } else {
        r->write_event_handler = ngx_http_core_run_phases;
    }

    u->co_ctx = coctx;
    u->waiting = 1;
    u->prepare_retvals = ngx_http_lua_socket_udp_receive_retval_handler;

    return lua_yield(L, 0);
}