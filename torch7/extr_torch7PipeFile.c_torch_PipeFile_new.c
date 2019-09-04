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
 int /*<<< orphan*/ * THPipeFile_new (char const*,char const*,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int luaT_optboolean (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaT_pushudata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int torch_PipeFile_new(lua_State *L)
{
  const char *name = luaL_checkstring(L, 1);
  const char *mode = luaL_optstring(L, 2, "r");
  int isQuiet = luaT_optboolean(L, 3, 0);
  THFile *self = THPipeFile_new(name, mode, isQuiet);

  luaT_pushudata(L, self, "torch.PipeFile");
  return 1;
}