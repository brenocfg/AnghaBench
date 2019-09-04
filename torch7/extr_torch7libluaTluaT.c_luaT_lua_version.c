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
 int /*<<< orphan*/  luaL_checkany (int /*<<< orphan*/ *,int) ; 
 char* luaT_cdataname (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaT_iscdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaT_pushmetatable (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 

int luaT_lua_version(lua_State *L)
{
  luaL_checkany(L, 1);

  if(luaT_iscdata(L, 1))
  {
    const char *tname = luaT_cdataname(L, 1, NULL);
    if(tname)
    {
      luaT_pushmetatable(L, tname);
      lua_pushstring(L, "__version");
      lua_rawget(L, -2);
      return 1;
    }
    return 0;
  }
  else if(lua_getmetatable(L, 1))
  {
    lua_pushstring(L, "__version");
    lua_rawget(L, -2);
    return 1;
  }
  return 0;
}