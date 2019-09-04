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
 int /*<<< orphan*/  luaT_newmetatable (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaT_setfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  torch_DiskFile__ ; 
 int /*<<< orphan*/  torch_DiskFile_free ; 
 int /*<<< orphan*/  torch_DiskFile_new ; 

void torch_DiskFile_init(lua_State *L)
{
  luaT_newmetatable(L, "torch.DiskFile", "torch.File",
                    torch_DiskFile_new, torch_DiskFile_free, NULL);

  luaT_setfuncs(L, torch_DiskFile__, 0);
  lua_pop(L, 1);
}