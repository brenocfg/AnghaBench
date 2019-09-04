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
struct TYPE_3__ {int /*<<< orphan*/  pending_timers; } ;
typedef  TYPE_1__ ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static int
ngx_http_lua_ngx_timer_pending_count(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_http_lua_main_conf_t    *lmcf;

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request");
    }

    lmcf = ngx_http_get_module_main_conf(r, ngx_http_lua_module);

    lua_pushnumber(L, lmcf->pending_timers);

    return 1;
}