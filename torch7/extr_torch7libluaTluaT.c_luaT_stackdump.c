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
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  LUA_TBOOLEAN 132 
#define  LUA_TNUMBER 131 
#define  LUA_TSTRING 130 
#define  LUA_TTABLE 129 
#define  LUA_TUSERDATA 128 
 char* luaT_typename (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_topointer (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 char* lua_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void luaT_stackdump(lua_State *L)
{
  int i;
  const char *tname = NULL;
  int top = lua_gettop(L);
  for(i = 1; i <= top; i++)
  {
    int t = lua_type(L, i);
    printf("%3d. ", i);
    switch(t)
    {
      case LUA_TSTRING:
        printf("'%s'", lua_tostring(L,i));
        break;
      case LUA_TBOOLEAN:
        printf(lua_toboolean(L, i) ? "true" : "false");
        break;
      case LUA_TNUMBER:
        printf("%g", lua_tonumber(L,i));
        break;
      case LUA_TUSERDATA:
        tname = luaT_typename(L, i);
        printf("userdata %p [%s]", lua_topointer(L, i), (tname ? tname : "not a Torch object"));
        break;
      case 10:
        tname = luaT_typename(L, i);
        printf("cdata %p [%s]", lua_topointer(L, i), (tname ? tname : "not a Torch object"));
        break;
      case LUA_TTABLE:
        lua_pushvalue(L, i);
        lua_rawget(L, LUA_REGISTRYINDEX);
        if(lua_isstring(L, -1))
          tname = lua_tostring(L, -1); /*luaT_typenameid(L, lua_tostring(L, -1)); */
        else
          tname = NULL;
        lua_pop(L, 1);
        if(tname)
          printf("metatable [%s]", tname);
        else
        {
          tname = luaT_typename(L, i);
          printf("table %p [%s]", lua_topointer(L, i), (tname ? tname : "not a Torch object"));
        }
        break;
      default:
        printf("Lua object type: %s", lua_typename(L,t));
        break;
    }
    printf("\n");
  }
  printf("---------------------------------------------\n");
}