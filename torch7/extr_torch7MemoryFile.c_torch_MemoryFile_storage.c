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
 int /*<<< orphan*/  THCharStorage_retain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THMemoryFile_storage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaT_pushudata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int torch_MemoryFile_storage(lua_State *L)
{
  THFile *self = luaT_checkudata(L, 1, "torch.MemoryFile");
  THCharStorage_retain(THMemoryFile_storage(self));
  luaT_pushudata(L, THMemoryFile_storage(self), "torch.CharStorage");
  return 1;
}