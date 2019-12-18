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
 int /*<<< orphan*/  ngx_http_lua_ngx_timer_at ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_timer_every ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_timer_pending_count ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_timer_running_count ; 

void
ngx_http_lua_inject_timer_api(lua_State *L)
{
    lua_createtable(L, 0 /* narr */, 4 /* nrec */);    /* ngx.timer. */

    lua_pushcfunction(L, ngx_http_lua_ngx_timer_at);
    lua_setfield(L, -2, "at");

    lua_pushcfunction(L, ngx_http_lua_ngx_timer_every);
    lua_setfield(L, -2, "every");

    lua_pushcfunction(L, ngx_http_lua_ngx_timer_running_count);
    lua_setfield(L, -2, "running_count");

    lua_pushcfunction(L, ngx_http_lua_ngx_timer_pending_count);
    lua_setfield(L, -2, "pending_count");

    lua_setfield(L, -2, "timer");
}