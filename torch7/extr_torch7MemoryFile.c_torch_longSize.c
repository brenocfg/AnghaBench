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
 int /*<<< orphan*/  THMemoryFile_longSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int torch_longSize(lua_State *L)
{
  THFile *self = luaT_checkudata(L, 1, "torch.MemoryFile");
  THMemoryFile_longSize(self, lua_tointeger(L, 2));
  lua_settop(L, 1);
  return 1;
}