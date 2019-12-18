#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ lua_Debug ;

/* Variables and functions */
 int LUA_MASKCALL ; 
 int LUA_MASKRET ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 int /*<<< orphan*/  hook ; 
 int /*<<< orphan*/  hook_index ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_gethook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_getstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_sethook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void call_ret_hook(lua_State *L) {
	lua_Debug ar;
	
	if (lua_gethook(L)) {
		lua_getstack(L, 0, &ar);
		lua_getinfo(L, "n", &ar);
		
		lua_pushlightuserdata(L, &hook_index);
		lua_rawget(L, LUA_REGISTRYINDEX);
		
		if (lua_type(L, -1) != LUA_TFUNCTION){
			lua_pop(L, 1);
			return;
        }
		
		lua_pushliteral(L, "return");
		lua_pushfstring(L, "[?%s]", ar.name);
		lua_pushliteral(L, "[C#]");
		
		lua_sethook(L, 0, 0, 0);
		lua_call(L, 3, 0);
		lua_sethook(L, hook, LUA_MASKCALL | LUA_MASKRET, 0);
	}
}