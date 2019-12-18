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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touint64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int uint64_compare(lua_State* L) {
	uint64_t lhs = lua_touint64(L, 1);
	uint64_t rhs = lua_touint64(L, 2);
	lua_pushinteger(L, lhs == rhs ? 0 : (lhs < rhs ? -1 : 1));
	return 1;
}