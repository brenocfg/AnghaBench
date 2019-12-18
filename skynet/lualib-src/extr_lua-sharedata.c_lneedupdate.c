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
struct ctrl {scalar_t__ update; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,scalar_t__) ; 
 struct ctrl* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lneedupdate(lua_State *L) {
	struct ctrl * c = lua_touserdata(L, 1);
	if (c->update) {
		lua_pushlightuserdata(L, c->update);
		lua_getuservalue(L, 1);
		return 2;
	}
	return 0;
}