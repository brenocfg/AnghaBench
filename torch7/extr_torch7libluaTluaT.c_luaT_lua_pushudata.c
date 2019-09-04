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
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaT_iscdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaT_pushudata (int /*<<< orphan*/ *,void*,char const*) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_topointer (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 

int luaT_lua_pushudata(lua_State *L)
{
  void *udata = NULL;
  const char *tname = luaL_checkstring(L, 2);

  if(lua_type(L, 1) == 10)
    udata = *((void**)lua_topointer(L, 1));
  else if(luaT_iscdata(L, 1))
    udata = ((void**)lua_topointer(L, 1))[4];
  else if(lua_isnumber(L, 1))
    udata = (void*)(uintptr_t)lua_tonumber(L, 1);
  else
    luaL_argerror(L, 1, "expecting number or cdata");

  luaT_pushudata(L, udata, tname);

  return 1;
}