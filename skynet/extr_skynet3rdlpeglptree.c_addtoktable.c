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
 int USHRT_MAX ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int addtoktable (lua_State *L, int idx) {
  if (lua_isnil(L, idx))  /* nil value? */
    return 0;
  else {
    int n;
    lua_getuservalue(L, -1);  /* get ktable from pattern */
    n = lua_rawlen(L, -1);
    if (n >= USHRT_MAX)
      luaL_error(L, "too many Lua values in pattern");
    lua_pushvalue(L, idx);  /* element to be added */
    lua_rawseti(L, -2, ++n);
    lua_pop(L, 1);  /* remove 'ktable' */
    return n;
  }
}