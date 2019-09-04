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
typedef  int /*<<< orphan*/  THCharStorage ;

/* Variables and functions */
 int /*<<< orphan*/ * THMemoryFile_new (char const*) ; 
 int /*<<< orphan*/ * THMemoryFile_newWithStorage (int /*<<< orphan*/ *,char const*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaT_pushudata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * luaT_toudata (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int torch_MemoryFile_new(lua_State *L)
{
  const char *mode;
  THCharStorage *storage = luaT_toudata(L, 1, "torch.CharStorage");
  THFile *self;

  if(storage)
  {
    mode = luaL_optstring(L, 2, "rw");
    self = THMemoryFile_newWithStorage(storage, mode);
  }
  else
  {
    mode = luaL_optstring(L, 1, "rw");
    self = THMemoryFile_new(mode);
  }

  luaT_pushudata(L, self, "torch.MemoryFile");
  return 1;
}