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
 scalar_t__ LUA_TTABLE ; 
 int TAB_L ; 
 int TAB_R ; 
 int TAB_W ; 
 scalar_t__ checkfield (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void checktab (lua_State *L, int arg, int what) {
  if (lua_type(L, arg) != LUA_TTABLE) {  /* is it not a table? */
    int n = 1;  /* number of elements to pop */
    if (lua_getmetatable(L, arg) &&  /* must have metatable */
        (!(what & TAB_R) || checkfield(L, "__index", ++n)) &&
        (!(what & TAB_W) || checkfield(L, "__newindex", ++n)) &&
        (!(what & TAB_L) || checkfield(L, "__len", ++n))) {
      lua_pop(L, n);  /* pop metatable and tested metamethods */
    }
    else
      luaL_checktype(L, arg, LUA_TTABLE);  /* force an error */
  }
}