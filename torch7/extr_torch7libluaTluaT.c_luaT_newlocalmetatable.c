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
typedef  scalar_t__ lua_CFunction ;

/* Variables and functions */
 scalar_t__ luaT_lua_newmetatable ; 
 char const* luaT_typenameid (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 void lua_pushcfunction (int /*<<< orphan*/ *,scalar_t__) ; 
 void lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 void lua_pushvalue (int /*<<< orphan*/ *,int) ; 

const char* luaT_newlocalmetatable(lua_State *L, const char *tname, const char *parent_tname,
                                   lua_CFunction constructor, lua_CFunction destructor, lua_CFunction factory, int moduleidx)
{
  lua_pushcfunction(L, luaT_lua_newmetatable);
  lua_pushstring(L, tname);
  (parent_tname ? (void)lua_pushstring(L, parent_tname) : lua_pushnil(L));
  (constructor ? lua_pushcfunction(L, constructor) : lua_pushnil(L));
  (destructor ? lua_pushcfunction(L, destructor) : lua_pushnil(L));
  (factory ? lua_pushcfunction(L, factory) : lua_pushnil(L));
  (moduleidx > 0 ? lua_pushvalue(L, moduleidx) : lua_pushnil(L));
  lua_call(L, 6, 1);
  return luaT_typenameid(L, tname);
}