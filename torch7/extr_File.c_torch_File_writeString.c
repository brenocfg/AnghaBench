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
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TSTRING ; 
 int /*<<< orphan*/  THFile_writeStringRaw (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 

__attribute__((used)) static int torch_File_writeString(lua_State *L)
{
  THFile *self = luaT_checkudata(L, 1, "torch.File");
  const char *str = NULL;
  size_t size;

  luaL_checktype(L, 2, LUA_TSTRING);
  str = lua_tolstring(L, 2, &size);
  lua_pushnumber(L, THFile_writeStringRaw(self, str, size));
  return 1;
}