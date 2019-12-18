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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 

int luaT_getfieldcheckboolean(lua_State *L, int ud, const char *field)
{
  lua_getfield(L, ud, field);
  if(lua_isnil(L, -1))
    luaL_error(L, "bad argument #%d (field %s does not exist)", ud, field);
  if(!lua_isboolean(L, -1))
    luaL_error(L, "bad argument #%d (field %s is not a boolean)", ud, field);
  return lua_toboolean(L, -1);
}