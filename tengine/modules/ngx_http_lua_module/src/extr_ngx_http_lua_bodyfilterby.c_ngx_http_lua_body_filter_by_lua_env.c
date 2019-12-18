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
struct TYPE_3__ {int /*<<< orphan*/ * body_filter_chain; } ;
typedef  TYPE_1__ ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ngx_http_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_create_new_globals_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_http_lua_get_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_set_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_body_filter_by_lua_env(lua_State *L, ngx_http_request_t *r,
    ngx_chain_t *in)
{
    ngx_http_lua_main_conf_t    *lmcf;

    ngx_http_lua_set_req(L, r);

    lmcf = ngx_http_get_module_main_conf(r, ngx_http_lua_module);
    lmcf->body_filter_chain = in;

#ifndef OPENRESTY_LUAJIT
    /**
     * we want to create empty environment for current script
     *
     * setmetatable({}, {__index = _G})
     *
     * if a function or symbol is not defined in our env, __index will lookup
     * in the global env.
     *
     * all variables created in the script-env will be thrown away at the end
     * of the script run.
     * */
    ngx_http_lua_create_new_globals_table(L, 0 /* narr */, 1 /* nrec */);

    /*  {{{ make new env inheriting main thread's globals table */
    lua_createtable(L, 0, 1 /* nrec */);    /*  the metatable for the new
                                                env */
    ngx_http_lua_get_globals_table(L);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);    /*  setmetatable({}, {__index = _G}) */
    /*  }}} */

    lua_setfenv(L, -2);    /*  set new running env for the code closure */
#endif /* OPENRESTY_LUAJIT */
}