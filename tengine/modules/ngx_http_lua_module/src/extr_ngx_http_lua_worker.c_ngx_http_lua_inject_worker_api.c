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
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_worker_count ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_worker_exiting ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_worker_id ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_worker_pid ; 

void
ngx_http_lua_inject_worker_api(lua_State *L)
{
    lua_createtable(L, 0 /* narr */, 4 /* nrec */);    /* ngx.worker. */

    lua_pushcfunction(L, ngx_http_lua_ngx_worker_exiting);
    lua_setfield(L, -2, "exiting");

    lua_pushcfunction(L, ngx_http_lua_ngx_worker_pid);
    lua_setfield(L, -2, "pid");

    lua_pushcfunction(L, ngx_http_lua_ngx_worker_id);
    lua_setfield(L, -2, "id");

    lua_pushcfunction(L, ngx_http_lua_ngx_worker_count);
    lua_setfield(L, -2, "count");

    lua_setfield(L, -2, "worker");
}