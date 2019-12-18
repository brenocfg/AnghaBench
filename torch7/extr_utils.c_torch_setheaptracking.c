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
 int /*<<< orphan*/  THSetGCHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int luaT_checkboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * luaTorchGCFunction ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int torch_setheaptracking(lua_State *L)
{
  int enabled = luaT_checkboolean(L,1);
  lua_getglobal(L, "torch");
  lua_pushboolean(L, enabled);
  lua_setfield(L, -2, "_heaptracking");
  if(enabled) {
    THSetGCHandler(luaTorchGCFunction, L);
  } else {
    THSetGCHandler(NULL, NULL);
  }
  return 0;
}