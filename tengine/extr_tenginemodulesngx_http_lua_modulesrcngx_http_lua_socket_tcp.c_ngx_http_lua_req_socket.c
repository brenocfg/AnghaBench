#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_22__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {TYPE_10__* connection; int /*<<< orphan*/  log_error; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_peer_connection_t ;
struct TYPE_25__ {scalar_t__ content_length_n; } ;
struct TYPE_28__ {TYPE_4__* request_body; TYPE_1__ headers_in; int /*<<< orphan*/  pool; scalar_t__ discard_body; TYPE_10__* connection; struct TYPE_28__* main; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_29__ {scalar_t__ rest; } ;
typedef  TYPE_4__ ngx_http_request_body_t ;
struct TYPE_30__ {int raw_downstream; int body_downstream; TYPE_2__ peer; int /*<<< orphan*/ * cleanup; int /*<<< orphan*/  ft_type; TYPE_6__* conf; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  read_timeout; TYPE_3__* request; } ;
typedef  TYPE_5__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_31__ {int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  read_timeout; } ;
typedef  TYPE_6__ ngx_http_lua_loc_conf_t ;
struct TYPE_32__ {TYPE_5__* downstream; TYPE_8__* cur_co_ctx; } ;
typedef  TYPE_7__ ngx_http_lua_ctx_t ;
struct TYPE_33__ {TYPE_5__* data; } ;
typedef  TYPE_8__ ngx_http_lua_co_ctx_t ;
struct TYPE_34__ {int /*<<< orphan*/  handler; TYPE_5__* data; } ;
typedef  TYPE_9__ ngx_http_cleanup_t ;
struct TYPE_24__ {TYPE_22__* write; TYPE_22__* read; int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_26__ {scalar_t__ timer_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_ERROR_ERR ; 
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  SOCKET_CTX_INDEX ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  downstream_udata_metatable_key ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 TYPE_5__* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_22__*) ; 
 TYPE_7__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 TYPE_9__* ngx_http_lua_cleanup_add (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_cleanup ; 
 scalar_t__ ngx_http_lua_test_expect (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_req_socket_metatable_key ; 
 int /*<<< orphan*/  req_socket_metatable_key ; 

__attribute__((used)) static int
ngx_http_lua_req_socket(lua_State *L)
{
    int                              n, raw;
    ngx_peer_connection_t           *pc;
    ngx_http_lua_loc_conf_t         *llcf;
    ngx_connection_t                *c;
    ngx_http_request_t              *r;
    ngx_http_lua_ctx_t              *ctx;
    ngx_http_request_body_t         *rb;
    ngx_http_cleanup_t              *cln;
    ngx_http_lua_co_ctx_t           *coctx;

    ngx_http_lua_socket_tcp_upstream_t  *u;

    n = lua_gettop(L);
    if (n == 0) {
        raw = 0;

    } else if (n == 1) {
        raw = lua_toboolean(L, 1);
        lua_pop(L, 1);

    } else {
        return luaL_error(L, "expecting zero arguments, but got %d",
                          lua_gettop(L));
    }

    r = ngx_http_lua_get_req(L);

    if (r != r->main) {
        return luaL_error(L, "attempt to read the request body in a "
                          "subrequest");
    }

#if (NGX_HTTP_SPDY)
    if (r->spdy_stream) {
        return luaL_error(L, "spdy not supported yet");
    }
#endif

#if (NGX_HTTP_V2)
    if (r->stream) {
        return luaL_error(L, "http v2 not supported yet");
    }
#endif

#if nginx_version >= 1003009
    if (!raw && r->headers_in.chunked) {
        lua_pushnil(L);
        lua_pushliteral(L, "chunked request bodies not supported yet");
        return 2;
    }
#endif

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no ctx found");
    }

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                               | NGX_HTTP_LUA_CONTEXT_ACCESS
                               | NGX_HTTP_LUA_CONTEXT_CONTENT);

    c = r->connection;

    if (raw) {
#if !defined(nginx_version) || nginx_version < 1003013
        lua_pushnil(L);
        lua_pushliteral(L, "nginx version too old");
        return 2;
#else
        if (r->request_body) {
            if (r->request_body->rest > 0) {
                lua_pushnil(L);
                lua_pushliteral(L, "pending request body reading in some "
                                "other thread");
                return 2;
            }

        } else {
            rb = ngx_pcalloc(r->pool, sizeof(ngx_http_request_body_t));
            if (rb == NULL) {
                return luaL_error(L, "no memory");
            }
            r->request_body = rb;
        }

        if (c->buffered & NGX_HTTP_LOWLEVEL_BUFFERED) {
            lua_pushnil(L);
            lua_pushliteral(L, "pending data to write");
            return 2;
        }

        if (ctx->buffering) {
            lua_pushnil(L);
            lua_pushliteral(L, "http 1.0 buffering");
            return 2;
        }

        if (!r->header_sent) {
            /* prevent other parts of nginx from sending out
             * the response header */
            r->header_sent = 1;
        }

        ctx->header_sent = 1;

        dd("ctx acquired raw req socket: %d", ctx->acquired_raw_req_socket);

        if (ctx->acquired_raw_req_socket) {
            lua_pushnil(L);
            lua_pushliteral(L, "duplicate call");
            return 2;
        }

        ctx->acquired_raw_req_socket = 1;
        r->keepalive = 0;
        r->lingering_close = 1;
#endif

    } else {
        /* request body reader */

        if (r->request_body) {
            lua_pushnil(L);
            lua_pushliteral(L, "request body already exists");
            return 2;
        }

        if (r->discard_body) {
            lua_pushnil(L);
            lua_pushliteral(L, "request body discarded");
            return 2;
        }

        dd("req content length: %d", (int) r->headers_in.content_length_n);

        if (r->headers_in.content_length_n <= 0) {
            lua_pushnil(L);
            lua_pushliteral(L, "no body");
            return 2;
        }

        if (ngx_http_lua_test_expect(r) != NGX_OK) {
            lua_pushnil(L);
            lua_pushliteral(L, "test expect failed");
            return 2;
        }

        /* prevent other request body reader from running */

        rb = ngx_pcalloc(r->pool, sizeof(ngx_http_request_body_t));
        if (rb == NULL) {
            return luaL_error(L, "no memory");
        }

        rb->rest = r->headers_in.content_length_n;

        r->request_body = rb;
    }

    lua_createtable(L, 2 /* narr */, 3 /* nrec */); /* the object */

    if (raw) {
        lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                              raw_req_socket_metatable_key));

    } else {
        lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                              req_socket_metatable_key));
    }

    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_setmetatable(L, -2);

    u = lua_newuserdata(L, sizeof(ngx_http_lua_socket_tcp_upstream_t));
    if (u == NULL) {
        return luaL_error(L, "no memory");
    }

#if 1
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          downstream_udata_metatable_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_setmetatable(L, -2);
#endif

    lua_rawseti(L, 1, SOCKET_CTX_INDEX);

    ngx_memzero(u, sizeof(ngx_http_lua_socket_tcp_upstream_t));

    if (raw) {
        u->raw_downstream = 1;

    } else {
        u->body_downstream = 1;
    }

    coctx = ctx->cur_co_ctx;

    u->request = r;

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

    u->conf = llcf;

    u->read_timeout = u->conf->read_timeout;
    u->connect_timeout = u->conf->connect_timeout;
    u->send_timeout = u->conf->send_timeout;

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

    pc = &u->peer;

    pc->log = c->log;
    pc->log_error = NGX_ERROR_ERR;

    pc->connection = c;

    dd("setting data to %p", u);

    coctx->data = u;
    ctx->downstream = u;

    if (c->read->timer_set) {
        ngx_del_timer(c->read);
    }

    if (raw) {
        if (c->write->timer_set) {
            ngx_del_timer(c->write);
        }
    }

    lua_settop(L, 1);
    return 1;
}