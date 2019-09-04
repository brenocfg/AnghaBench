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
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

const char* torch_getdefaulttensortype(lua_State *L)
{
  lua_getglobal(L, "torch");
  if(lua_istable(L, -1))
  {
    lua_getfield(L, -1, "Tensor");
    if(lua_istable(L, -1))
    {
      if(lua_getmetatable(L, -1))
      {
        lua_pushstring(L, "__index");
        lua_rawget(L, -2);
        if(lua_istable(L, -1))
        {
          lua_rawget(L, LUA_REGISTRYINDEX);
          if(lua_isstring(L, -1))
          {
            const char *tname = lua_tostring(L, -1);
            lua_pop(L, 4);
            return tname;
          }
        }
        else
        {
          lua_pop(L, 4);
          return NULL;
        }
      }
      else
      {
        lua_pop(L, 2);
        return NULL;
      }
    }
    else
    {
      lua_pop(L, 2);
      return NULL;
    }
  }
  else
  {
    lua_pop(L, 1);
    return NULL;
  }
  return NULL;
}