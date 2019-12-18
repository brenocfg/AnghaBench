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
struct TYPE_4__ {int event; char* what; scalar_t__ linedefined; int /*<<< orphan*/  short_src; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  hook_index ; 
 int /*<<< orphan*/ * hooknames ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hook(lua_State *L, lua_Debug *ar)
{
	int event;
	
	lua_pushlightuserdata(L, &hook_index);
	lua_rawget(L, LUA_REGISTRYINDEX);

	event = ar->event;
	lua_pushstring(L, hooknames[event]);
  
	lua_getinfo(L, "nS", ar);
	if (*(ar->what) == 'C') {
		lua_pushfstring(L, "[?%s]", ar->name);
	} else {
		lua_pushfstring(L, "%s:%d", ar->short_src, ar->linedefined > 0 ? ar->linedefined : 0);
	}

	lua_call(L, 2, 0);
}