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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TSTRING ; 
 int /*<<< orphan*/  NGX_LUA_EXCEPTION_THROW (int) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_log_stderr (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *) ; 
 int ngx_quit ; 

int
ngx_http_lua_atpanic(lua_State *L)
{
#ifdef NGX_LUA_ABORT_AT_PANIC
    abort();
#else
    u_char                  *s = NULL;
    size_t                   len = 0;

    if (lua_type(L, -1) == LUA_TSTRING) {
        s = (u_char *) lua_tolstring(L, -1, &len);
    }

    if (s == NULL) {
        s = (u_char *) "unknown reason";
        len = sizeof("unknown reason") - 1;
    }

    ngx_log_stderr(0, "lua atpanic: Lua VM crashed, reason: %*s", len, s);
    ngx_quit = 1;

    /*  restore nginx execution */
    NGX_LUA_EXCEPTION_THROW(1);

    /* impossible to reach here */
#endif
}