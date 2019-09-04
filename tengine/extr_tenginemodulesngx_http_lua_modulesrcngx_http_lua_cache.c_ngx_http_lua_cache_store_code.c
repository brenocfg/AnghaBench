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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  code_cache_key ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_cache_store_code(lua_State *L, const char *key)
{
#ifndef OPENRESTY_LUAJIT
    int rc;
#endif

    /*  get code cache table */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          code_cache_key));
    lua_rawget(L, LUA_REGISTRYINDEX);

    dd("Code cache table to store: %p", lua_topointer(L, -1));

    if (!lua_istable(L, -1)) {
        dd("Error: code cache table to load did not exist!!");
        return NGX_ERROR;
    }

    lua_pushvalue(L, -2); /* closure cache closure */
    lua_setfield(L, -2, key); /* closure cache */

    /*  remove cache table, leave closure factory at top of stack */
    lua_pop(L, 1); /* closure */

#ifndef OPENRESTY_LUAJIT
    /*  call closure factory to generate new closure */
    rc = lua_pcall(L, 0, 1, 0);
    if (rc != 0) {
        dd("Error: failed to call closure factory!!");
        return NGX_ERROR;
    }
#endif

    return NGX_OK;
}