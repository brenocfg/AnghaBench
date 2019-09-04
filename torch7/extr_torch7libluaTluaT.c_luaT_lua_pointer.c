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
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaT_iscdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaT_pushpointer (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaT_typename (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isthread (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isuserdata (int /*<<< orphan*/ *,int) ; 
 void* lua_topointer (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 void** lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 

int luaT_lua_pointer(lua_State *L)
{
  if(lua_type(L, 1) == 10) /* luajit cdata */
  {
    /* we want the pointer holded by cdata */
    /* not the pointer on the cdata object */
    const void* ptr = *((void**)lua_topointer(L, 1));
    luaT_pushpointer(L, ptr);
    return 1;
  }
  else if (luaT_iscdata(L, 1)) /* luaffi cdata */
  {
    void** ptr = (void**)lua_touserdata(L, 1);
    luaT_pushpointer(L, ptr[4]);
    return 1;
  }
  else if(lua_isuserdata(L, 1))
  {
    void **ptr;
    luaL_argcheck(L, luaT_typename(L, 1), 1, "Torch object expected");
    ptr = lua_touserdata(L, 1);
    luaT_pushpointer(L, *ptr);
    return 1;
  }
  else if(lua_istable(L, 1) || lua_isthread(L, 1) || lua_isfunction(L, 1))
  {
    const void* ptr = lua_topointer(L, 1);
    luaT_pushpointer(L, ptr);
    return 1;
  }
  else if(lua_isstring(L, 1))
  {
    const char* ptr = lua_tostring(L, 1);
    luaT_pushpointer(L, ptr);
    return 1;
  }
  else
    luaL_error(L, "Torch object, table, thread, cdata or function expected");

  return 0;
}