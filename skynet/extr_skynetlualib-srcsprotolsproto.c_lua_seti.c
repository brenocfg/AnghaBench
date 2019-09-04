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
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 int lua_absindex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
lua_seti(lua_State *L, int index, lua_Integer n) {
	index = lua_absindex(L, index);
	lua_pushinteger(L, n);
	lua_insert(L, -2);
	lua_settable(L, index);
}