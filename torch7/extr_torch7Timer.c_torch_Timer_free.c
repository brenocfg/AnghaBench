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
typedef  int /*<<< orphan*/  Timer ;

/* Variables and functions */
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaT_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int torch_Timer_free(lua_State *L)
{
  Timer *timer = luaT_checkudata(L, 1, "torch.Timer");
  luaT_free(L, timer);
  return 0;
}