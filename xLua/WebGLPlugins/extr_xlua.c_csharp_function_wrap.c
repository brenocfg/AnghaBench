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
typedef  int (* lua_CFunction ) (int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  call_ret_hook (int /*<<< orphan*/ *) ; 
 int lua_error (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_gethook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tocfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 

__attribute__((used)) static int csharp_function_wrap(lua_State *L) {
	lua_CFunction fn = (lua_CFunction)lua_tocfunction(L, lua_upvalueindex(1));
    int ret = fn(L);    
    
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