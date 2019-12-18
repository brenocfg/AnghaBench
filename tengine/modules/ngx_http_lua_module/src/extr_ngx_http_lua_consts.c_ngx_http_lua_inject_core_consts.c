#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

void
ngx_http_lua_inject_core_consts(lua_State *L)
{
    /* {{{ core constants */
    lua_pushinteger(L, NGX_OK);
    lua_setfield(L, -2, "OK");

    lua_pushinteger(L, NGX_AGAIN);
    lua_setfield(L, -2, "AGAIN");

    lua_pushinteger(L, NGX_DONE);
    lua_setfield(L, -2, "DONE");

    lua_pushinteger(L, NGX_DECLINED);
    lua_setfield(L, -2, "DECLINED");

    lua_pushinteger(L, NGX_ERROR);
    lua_setfield(L, -2, "ERROR");

    lua_pushlightuserdata(L, NULL);
    lua_setfield(L, -2, "null");
    /* }}} */
}