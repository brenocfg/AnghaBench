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
 scalar_t__ lua_isnone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int mallctl_bool (char*,int*) ; 

__attribute__((used)) static int
lprofactive(lua_State *L) {
	bool *pval, active;
	if (lua_isnone(L, 1)) {
		pval = NULL;
	} else {
		active = lua_toboolean(L, 1) ? true : false;
		pval = &active;
	}
	bool ret = mallctl_bool("prof.active", pval);
	lua_pushboolean(L, ret);
	return 1;
}