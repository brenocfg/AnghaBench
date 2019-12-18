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
 int /*<<< orphan*/  call_ret_hook (int /*<<< orphan*/ *) ; 
 int g_csharp_wrapper_caller (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_error (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_gethook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/  xlua_tointeger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csharp_function_wrapper_wrapper(lua_State *L) {
    int ret = 0;
	
	if (g_csharp_wrapper_caller == NULL) {
		return luaL_error(L, "g_csharp_wrapper_caller not set");
	}
	
	ret = g_csharp_wrapper_caller(L, xlua_tointeger(L, lua_upvalueindex(1)), lua_gettop(L));    
    
    if (lua_toboolean(L, lua_upvalueindex(2)))
    {
        lua_pushboolean(L, 0);
        lua_replace(L, lua_upvalueindex(2));
        return lua_error(L);
    }
    
	if (lua_gethook(L)) {
		call_ret_hook(L);
	}
	
    return ret;
}