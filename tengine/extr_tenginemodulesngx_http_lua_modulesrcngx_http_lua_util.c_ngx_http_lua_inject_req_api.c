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
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_args_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_body_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_header_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_method_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_misc_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_socket_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_time_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_uri_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ngx_http_lua_inject_req_api(ngx_log_t *log, lua_State *L)
{
    /* ngx.req table */

    lua_createtable(L, 0 /* narr */, 24 /* nrec */);    /* .req */

    ngx_http_lua_inject_req_header_api(L);
    ngx_http_lua_inject_req_uri_api(log, L);
    ngx_http_lua_inject_req_args_api(L);
    ngx_http_lua_inject_req_body_api(L);
    ngx_http_lua_inject_req_socket_api(L);
    ngx_http_lua_inject_req_method_api(L);
    ngx_http_lua_inject_req_time_api(L);
    ngx_http_lua_inject_req_misc_api(L);

    lua_setfield(L, -2, "req");
}