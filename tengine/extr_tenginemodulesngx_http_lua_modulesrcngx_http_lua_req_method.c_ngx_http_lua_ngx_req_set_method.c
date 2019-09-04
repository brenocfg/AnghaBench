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
struct TYPE_4__ {int method; int /*<<< orphan*/  method_name; } ;
typedef  TYPE_1__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  NGX_HTTP_COPY 142 
#define  NGX_HTTP_DELETE 141 
#define  NGX_HTTP_GET 140 
#define  NGX_HTTP_HEAD 139 
#define  NGX_HTTP_LOCK 138 
#define  NGX_HTTP_MKCOL 137 
#define  NGX_HTTP_MOVE 136 
#define  NGX_HTTP_OPTIONS 135 
#define  NGX_HTTP_PATCH 134 
#define  NGX_HTTP_POST 133 
#define  NGX_HTTP_PROPFIND 132 
#define  NGX_HTTP_PROPPATCH 131 
#define  NGX_HTTP_PUT 130 
#define  NGX_HTTP_TRACE 129 
#define  NGX_HTTP_UNLOCK 128 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_lua_copy_method ; 
 int /*<<< orphan*/  ngx_http_lua_delete_method ; 
 int /*<<< orphan*/  ngx_http_lua_get_method ; 
 TYPE_1__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_head_method ; 
 int /*<<< orphan*/  ngx_http_lua_lock_method ; 
 int /*<<< orphan*/  ngx_http_lua_mkcol_method ; 
 int /*<<< orphan*/  ngx_http_lua_move_method ; 
 int /*<<< orphan*/  ngx_http_lua_options_method ; 
 int /*<<< orphan*/  ngx_http_lua_patch_method ; 
 int /*<<< orphan*/  ngx_http_lua_post_method ; 
 int /*<<< orphan*/  ngx_http_lua_propfind_method ; 
 int /*<<< orphan*/  ngx_http_lua_proppatch_method ; 
 int /*<<< orphan*/  ngx_http_lua_put_method ; 
 int /*<<< orphan*/  ngx_http_lua_trace_method ; 
 int /*<<< orphan*/  ngx_http_lua_unlock_method ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_set_method(lua_State *L)
{
    int                  n;
    int                  method;
    ngx_http_request_t  *r;

    n = lua_gettop(L);
    if (n != 1) {
        return luaL_error(L, "only one argument expected but got %d", n);
    }

    method = luaL_checkint(L, 1);

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "request object not found");
    }

    ngx_http_lua_check_fake_request(L, r);

    switch (method) {
        case NGX_HTTP_GET:
            r->method_name = ngx_http_lua_get_method;
            break;

        case NGX_HTTP_POST:
            r->method_name = ngx_http_lua_post_method;
            break;

        case NGX_HTTP_PUT:
            r->method_name = ngx_http_lua_put_method;
            break;

        case NGX_HTTP_HEAD:
            r->method_name = ngx_http_lua_head_method;
            break;

        case NGX_HTTP_DELETE:
            r->method_name = ngx_http_lua_delete_method;
            break;

        case NGX_HTTP_OPTIONS:
            r->method_name = ngx_http_lua_options_method;
            break;

        case NGX_HTTP_MKCOL:
            r->method_name = ngx_http_lua_mkcol_method;
            break;

        case NGX_HTTP_COPY:
            r->method_name = ngx_http_lua_copy_method;
            break;

        case NGX_HTTP_MOVE:
            r->method_name = ngx_http_lua_move_method;
            break;

        case NGX_HTTP_PROPFIND:
            r->method_name = ngx_http_lua_propfind_method;
            break;

        case NGX_HTTP_PROPPATCH:
            r->method_name = ngx_http_lua_proppatch_method;
            break;

        case NGX_HTTP_LOCK:
            r->method_name = ngx_http_lua_lock_method;
            break;

        case NGX_HTTP_UNLOCK:
            r->method_name = ngx_http_lua_unlock_method;
            break;

        case NGX_HTTP_PATCH:
            r->method_name = ngx_http_lua_patch_method;
            break;

        case NGX_HTTP_TRACE:
            r->method_name = ngx_http_lua_trace_method;
            break;

        default:
            return luaL_error(L, "unsupported HTTP method: %d", method);
    }

    r->method = method;

    return 0;
}