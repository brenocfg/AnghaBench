#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/ * cleardummy ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int 
codecache(lua_State *L) {
	luaL_Reg l[] = {
		{ "clear", cleardummy },
		{ "mode", cleardummy },
		{ NULL, NULL },
	};
	luaL_newlib(L,l);
	lua_getglobal(L, "loadfile");
	lua_setfield(L, -2, "loadfile");
	return 1;
}