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
 int /*<<< orphan*/  ngx_http_lua_ngx_location_capture ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_location_capture_multi ; 

void
ngx_http_lua_inject_subrequest_api(lua_State *L)
{
    lua_createtable(L, 0 /* narr */, 2 /* nrec */); /* .location */

    lua_pushcfunction(L, ngx_http_lua_ngx_location_capture);
    lua_setfield(L, -2, "capture");

    lua_pushcfunction(L, ngx_http_lua_ngx_location_capture_multi);
    lua_setfield(L, -2, "capture_multi");

    lua_setfield(L, -2, "location");
}