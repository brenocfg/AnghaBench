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
 int /*<<< orphan*/  luaT_setfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  torch_updateerrorhandlers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_utils__ ; 

void torch_utils_init(lua_State *L)
{
  torch_updateerrorhandlers(L);
  luaT_setfuncs(L, torch_utils__, 0);
}