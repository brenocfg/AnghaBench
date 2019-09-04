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
 int /*<<< orphan*/  ngx_http_lua_ngx_req_append_body ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_body_finish ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_discard_body ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_get_body_data ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_get_body_file ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_init_body ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_read_body ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_set_body_data ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_req_set_body_file ; 

void
ngx_http_lua_inject_req_body_api(lua_State *L)
{
    lua_pushcfunction(L, ngx_http_lua_ngx_req_read_body);
    lua_setfield(L, -2, "read_body");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_discard_body);
    lua_setfield(L, -2, "discard_body");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_get_body_data);
    lua_setfield(L, -2, "get_body_data");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_get_body_file);
    lua_setfield(L, -2, "get_body_file");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_set_body_data);
    lua_setfield(L, -2, "set_body_data");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_set_body_file);
    lua_setfield(L, -2, "set_body_file");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_init_body);
    lua_setfield(L, -2, "init_body");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_append_body);
    lua_setfield(L, -2, "append_body");

    lua_pushcfunction(L, ngx_http_lua_ngx_req_body_finish);
    lua_setfield(L, -2, "finish_body");
}