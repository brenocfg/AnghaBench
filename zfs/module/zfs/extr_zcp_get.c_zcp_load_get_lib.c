#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ zcp_get_prop_info ; 

int
zcp_load_get_lib(lua_State *state)
{
	lua_pushcclosure(state, zcp_get_prop_info.func, 0);
	lua_setfield(state, -2, zcp_get_prop_info.name);

	return (1);
}