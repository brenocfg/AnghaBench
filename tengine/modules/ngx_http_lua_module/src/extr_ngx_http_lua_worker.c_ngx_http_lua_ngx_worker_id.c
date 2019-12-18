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
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 scalar_t__ NGX_PROCESS_SINGLE ; 
 scalar_t__ NGX_PROCESS_WORKER ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_process ; 
 scalar_t__ ngx_worker ; 

__attribute__((used)) static int
ngx_http_lua_ngx_worker_id(lua_State *L)
{
#if (nginx_version >= 1009001)
    if (ngx_process != NGX_PROCESS_WORKER
        && ngx_process != NGX_PROCESS_SINGLE)
    {
        lua_pushnil(L);
        return 1;
    }

    lua_pushinteger(L, (lua_Integer) ngx_worker);
#else
    lua_pushnil(L);
#endif
    return 1;
}