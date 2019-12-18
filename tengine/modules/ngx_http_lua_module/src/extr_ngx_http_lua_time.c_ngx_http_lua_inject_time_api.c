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
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_cookie_time ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_http_time ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_localtime ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_now ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_parse_http_time ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_time ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_today ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_update_time ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_utctime ; 

void
ngx_http_lua_inject_time_api(lua_State *L)
{
    lua_pushcfunction(L, ngx_http_lua_ngx_utctime);
    lua_setfield(L, -2, "utctime");

    lua_pushcfunction(L, ngx_http_lua_ngx_time);
    lua_setfield(L, -2, "get_now_ts"); /* deprecated */

    lua_pushcfunction(L, ngx_http_lua_ngx_localtime);
    lua_setfield(L, -2, "get_now"); /* deprecated */

    lua_pushcfunction(L, ngx_http_lua_ngx_localtime);
    lua_setfield(L, -2, "localtime");

    lua_pushcfunction(L, ngx_http_lua_ngx_time);
    lua_setfield(L, -2, "time");

    lua_pushcfunction(L, ngx_http_lua_ngx_now);
    lua_setfield(L, -2, "now");

    lua_pushcfunction(L, ngx_http_lua_ngx_update_time);
    lua_setfield(L, -2, "update_time");

    lua_pushcfunction(L, ngx_http_lua_ngx_today);
    lua_setfield(L, -2, "get_today"); /* deprecated */

    lua_pushcfunction(L, ngx_http_lua_ngx_today);
    lua_setfield(L, -2, "today");

    lua_pushcfunction(L, ngx_http_lua_ngx_cookie_time);
    lua_setfield(L, -2, "cookie_time");

    lua_pushcfunction(L, ngx_http_lua_ngx_http_time);
    lua_setfield(L, -2, "http_time");

    lua_pushcfunction(L, ngx_http_lua_ngx_parse_http_time);
    lua_setfield(L, -2, "parse_http_time");
}