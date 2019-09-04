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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  luaT_pushmetatable (int /*<<< orphan*/ *,char const*) ; 
 void** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 

void luaT_pushudata(lua_State *L, void *udata, const char *tname)
{
  if(udata)
  {
    void **udata_p = lua_newuserdata(L, sizeof(void*));
    *udata_p = udata;
    if(!luaT_pushmetatable(L, tname))
      luaL_error(L, "Torch internal problem: cannot find metatable for type <%s>", tname);
    lua_setmetatable(L, -2);
  }
  else
    lua_pushnil(L);
}