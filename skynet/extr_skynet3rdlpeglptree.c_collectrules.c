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
 int /*<<< orphan*/  LUA_MINSTACK ; 
 int /*<<< orphan*/  getfirstrule (int /*<<< orphan*/ *,int,int) ; 
 int getsize (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lp_equal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testpattern (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int collectrules (lua_State *L, int arg, int *totalsize) {
  int n = 1;  /* to count number of rules */
  int postab = lua_gettop(L) + 1;  /* index of position table */
  int size;  /* accumulator for total size */
  lua_newtable(L);  /* create position table */
  getfirstrule(L, arg, postab);
  size = 2 + getsize(L, postab + 2);  /* TGrammar + TRule + rule */
  lua_pushnil(L);  /* prepare to traverse grammar table */
  while (lua_next(L, arg) != 0) {
    if (lua_tonumber(L, -2) == 1 ||
        lp_equal(L, -2, postab + 1)) {  /* initial rule? */
      lua_pop(L, 1);  /* remove value (keep key for lua_next) */
      continue;
    }
    if (!testpattern(L, -1))  /* value is not a pattern? */
      luaL_error(L, "rule '%s' is not a pattern", val2str(L, -2));
    luaL_checkstack(L, LUA_MINSTACK, "grammar has too many rules");
    lua_pushvalue(L, -2);  /* push key (to insert into position table) */
    lua_pushinteger(L, size);
    lua_settable(L, postab);
    size += 1 + getsize(L, -1);  /* update size */
    lua_pushvalue(L, -2);  /* push key (for next lua_next) */
    n++;
  }
  *totalsize = size + 1;  /* TTrue to finish list of rules */
  return n;
}