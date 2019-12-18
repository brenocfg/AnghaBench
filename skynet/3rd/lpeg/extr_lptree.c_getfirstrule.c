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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testpattern (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void getfirstrule (lua_State *L, int arg, int postab) {
  lua_rawgeti(L, arg, 1);  /* access first element */
  if (lua_isstring(L, -1)) {  /* is it the name of initial rule? */
    lua_pushvalue(L, -1);  /* duplicate it to use as key */
    lua_gettable(L, arg);  /* get associated rule */
  }
  else {
    lua_pushinteger(L, 1);  /* key for initial rule */
    lua_insert(L, -2);  /* put it before rule */
  }
  if (!testpattern(L, -1)) {  /* initial rule not a pattern? */
    if (lua_isnil(L, -1))
      luaL_error(L, "grammar has no initial rule");
    else
      luaL_error(L, "initial rule '%s' is not a pattern", lua_tostring(L, -2));
  }
  lua_pushvalue(L, -2);  /* push key */
  lua_pushinteger(L, 1);  /* push rule position (after TGrammar) */
  lua_settable(L, postab);  /* insert pair at position table */
}