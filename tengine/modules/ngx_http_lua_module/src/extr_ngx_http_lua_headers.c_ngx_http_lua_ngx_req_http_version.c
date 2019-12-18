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
struct TYPE_4__ {int http_version; } ;
typedef  TYPE_1__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  NGX_HTTP_VERSION_10 131 
#define  NGX_HTTP_VERSION_11 130 
#define  NGX_HTTP_VERSION_20 129 
#define  NGX_HTTP_VERSION_9 128 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_http_version(lua_State *L)
{
    ngx_http_request_t          *r;

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request object found");
    }

    ngx_http_lua_check_fake_request(L, r);

    switch (r->http_version) {
    case NGX_HTTP_VERSION_9:
        lua_pushnumber(L, 0.9);
        break;

    case NGX_HTTP_VERSION_10:
        lua_pushnumber(L, 1.0);
        break;

    case NGX_HTTP_VERSION_11:
        lua_pushnumber(L, 1.1);
        break;

#ifdef NGX_HTTP_VERSION_20
    case NGX_HTTP_VERSION_20:
        lua_pushnumber(L, 2.0);
        break;
#endif

    default:
        lua_pushnil(L);
        break;
    }

    return 1;
}