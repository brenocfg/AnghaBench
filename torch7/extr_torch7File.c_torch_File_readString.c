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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int /*<<< orphan*/  THFile_readStringRaw (int /*<<< orphan*/ *,char const*,char**) ; 
 int /*<<< orphan*/  THFree (char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int torch_File_readString(lua_State *L)
{
  THFile *self = luaT_checkudata(L, 1, "torch.File");
  const char *format = luaL_checkstring(L, 2);
  char *str;
  ptrdiff_t size;

  size = THFile_readStringRaw(self, format, &str);
  lua_pushlstring(L, str, size);
  THFree(str);

  return 1;
}