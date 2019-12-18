#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_3__ {int context; } ;
typedef  TYPE_1__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  NGX_HTTP_LUA_CONTEXT_ACCESS 140 
#define  NGX_HTTP_LUA_CONTEXT_BALANCER 139 
#define  NGX_HTTP_LUA_CONTEXT_BODY_FILTER 138 
#define  NGX_HTTP_LUA_CONTEXT_CONTENT 137 
#define  NGX_HTTP_LUA_CONTEXT_HEADER_FILTER 136 
#define  NGX_HTTP_LUA_CONTEXT_INIT_WORKER 135 
#define  NGX_HTTP_LUA_CONTEXT_LOG 134 
#define  NGX_HTTP_LUA_CONTEXT_REWRITE 133 
#define  NGX_HTTP_LUA_CONTEXT_SET 132 
#define  NGX_HTTP_LUA_CONTEXT_SSL_CERT 131 
#define  NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH 130 
#define  NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE 129 
#define  NGX_HTTP_LUA_CONTEXT_TIMER 128 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static int
ngx_http_lua_ngx_get_phase(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;

    r = ngx_http_lua_get_req(L);

    /* If we have no request object, assume we are called from the "init"
     * phase. */

    if (r == NULL) {
        lua_pushliteral(L, "init");
        return 1;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    switch (ctx->context) {
    case NGX_HTTP_LUA_CONTEXT_INIT_WORKER:
        lua_pushliteral(L, "init_worker");
        break;

    case NGX_HTTP_LUA_CONTEXT_SET:
        lua_pushliteral(L, "set");
        break;

    case NGX_HTTP_LUA_CONTEXT_REWRITE:
        lua_pushliteral(L, "rewrite");
        break;

    case NGX_HTTP_LUA_CONTEXT_ACCESS:
        lua_pushliteral(L, "access");
        break;

    case NGX_HTTP_LUA_CONTEXT_CONTENT:
        lua_pushliteral(L, "content");
        break;

    case NGX_HTTP_LUA_CONTEXT_LOG:
        lua_pushliteral(L, "log");
        break;

    case NGX_HTTP_LUA_CONTEXT_HEADER_FILTER:
        lua_pushliteral(L, "header_filter");
        break;

    case NGX_HTTP_LUA_CONTEXT_BODY_FILTER:
        lua_pushliteral(L, "body_filter");
        break;

    case NGX_HTTP_LUA_CONTEXT_TIMER:
        lua_pushliteral(L, "timer");
        break;

    case NGX_HTTP_LUA_CONTEXT_BALANCER:
        lua_pushliteral(L, "balancer");
        break;

    case NGX_HTTP_LUA_CONTEXT_SSL_CERT:
        lua_pushliteral(L, "ssl_cert");
        break;

    case NGX_HTTP_LUA_CONTEXT_SSL_SESS_STORE:
        lua_pushliteral(L, "ssl_session_store");
        break;

    case NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH:
        lua_pushliteral(L, "ssl_session_fetch");
        break;

    default:
        return luaL_error(L, "unknown phase: %#x", (int) ctx->context);
    }

    return 1;
}