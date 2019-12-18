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
 int /*<<< orphan*/  dd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_param_get ; 
 int /*<<< orphan*/  ngx_http_lua_param_set ; 

__attribute__((used)) static void
ngx_http_lua_inject_arg_api(lua_State *L)
{
    lua_pushliteral(L, "arg");
    lua_newtable(L);    /*  .arg table aka {} */

    lua_createtable(L, 0 /* narr */, 2 /* nrec */);    /*  the metatable */

    lua_pushcfunction(L, ngx_http_lua_param_get);
    lua_setfield(L, -2, "__index");

    lua_pushcfunction(L, ngx_http_lua_param_set);
    lua_setfield(L, -2, "__newindex");

    lua_setmetatable(L, -2);    /*  tie the metatable to param table */

    dd("top: %d, type -1: %s", lua_gettop(L), luaL_typename(L, -1));

    lua_rawset(L, -3);    /*  set ngx.arg table */
}