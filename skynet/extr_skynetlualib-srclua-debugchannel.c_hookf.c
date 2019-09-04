#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  currentline; scalar_t__ event; } ;
typedef  TYPE_1__ lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  HOOKKEY ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  lua_pushthread (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgetp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hookf (lua_State *L, lua_Debug *ar) {
  static const char *const hooknames[] =
    {"call", "return", "line", "count", "tail call"};
  lua_rawgetp(L, LUA_REGISTRYINDEX, &HOOKKEY);
  lua_pushthread(L);
  if (lua_rawget(L, -2) == LUA_TFUNCTION) {  /* is there a hook function? */
    lua_pushstring(L, hooknames[(int)ar->event]);  /* push event name */
    if (ar->currentline >= 0)
      lua_pushinteger(L, ar->currentline);  /* push current line */
    else lua_pushnil(L);
    lua_call(L, 2, 1);  /* call hook function */
	int yield = lua_toboolean(L, -1);
	lua_pop(L,1);
	if (yield) {
		lua_yield(L, 0);
	}
  }
}