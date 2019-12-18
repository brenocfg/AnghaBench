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
 int /*<<< orphan*/  ngx_http_lua_ngx_req_get_headers ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_header_clear ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_header_set ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_http_version ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_raw_header ; 

void
ngx_http_lua_inject_req_header_api(lua_State *L)
{
    lua_pushcfunction(L, ngx_http_lua_ngx_req_http_version);
    lua_setfield(L, -2, "http_version");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_raw_header);
    lua_setfield(L, -2, "raw_header");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_header_clear);
    lua_setfield(L, -2, "clear_header");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_header_set);
    lua_setfield(L, -2, "set_header");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_get_headers);
    lua_setfield(L, -2, "get_headers");
}