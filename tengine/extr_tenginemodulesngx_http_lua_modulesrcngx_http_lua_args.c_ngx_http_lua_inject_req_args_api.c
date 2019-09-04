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
 int /*<<< orphan*/  ngx_http_lua_ngx_req_get_post_args ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_get_uri_args ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_set_uri_args ; 

void
ngx_http_lua_inject_req_args_api(lua_State *L)
{
    lua_pushcfunction(L, ngx_http_lua_ngx_req_set_uri_args);
    lua_setfield(L, -2, "set_uri_args");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_get_uri_args);
    lua_setfield(L, -2, "get_uri_args");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_get_uri_args);
    lua_setfield(L, -2, "get_query_args"); /* deprecated */

    lua_pushcfunction(L, ngx_http_lua_ngx_req_get_post_args);
    lua_setfield(L, -2, "get_post_args");
}