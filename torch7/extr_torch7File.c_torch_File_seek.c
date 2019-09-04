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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int /*<<< orphan*/  THArgCheck (int,int,char*) ; 
 int /*<<< orphan*/  THFile_seek (int /*<<< orphan*/ *,size_t) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int torch_File_seek(lua_State *L)
{
  THFile *self = luaT_checkudata(L, 1, "torch.File");
  ptrdiff_t position = luaL_checkinteger(L, 2)-1;
  // >= 0 because it has 1 already subtracted
  THArgCheck(position >= 0, 2, "position has to be greater than 0!");
  THFile_seek(self, (size_t)position);
  lua_settop(L, 1);
  return 1;
}