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
 int /*<<< orphan*/  PATTERN_T ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawequal (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int testpattern (lua_State *L, int idx) {
  if (lua_touserdata(L, idx)) {  /* value is a userdata? */
    if (lua_getmetatable(L, idx)) {  /* does it have a metatable? */
      luaL_getmetatable(L, PATTERN_T);
      if (lua_rawequal(L, -1, -2)) {  /* does it have the correct mt? */
        lua_pop(L, 2);  /* remove both metatables */
        return 1;
      }
    }
  }
  return 0;
}