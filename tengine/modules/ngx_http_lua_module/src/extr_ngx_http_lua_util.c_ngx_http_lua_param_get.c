#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_4__ {int context; } ;
typedef  TYPE_1__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int NGX_HTTP_LUA_CONTEXT_BODY_FILTER ; 
 int NGX_HTTP_LUA_CONTEXT_SET ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ngx_http_lua_body_filter_param_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int ngx_http_lua_setby_param_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_param_get(lua_State *L)
{
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_request_t          *r;

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return 0;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "ctx not found");
    }

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_SET
                               | NGX_HTTP_LUA_CONTEXT_BODY_FILTER);

    if (ctx->context & (NGX_HTTP_LUA_CONTEXT_SET)) {
        return ngx_http_lua_setby_param_get(L, r);
    }

    /* ctx->context & (NGX_HTTP_LUA_CONTEXT_BODY_FILTER) */

    return ngx_http_lua_body_filter_param_get(L, r);
}