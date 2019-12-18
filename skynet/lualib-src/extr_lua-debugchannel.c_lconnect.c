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
struct channel {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 struct channel* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  new_channel (int /*<<< orphan*/ *,struct channel*) ; 

__attribute__((used)) static int
lconnect(lua_State *L) {
	struct channel *c = lua_touserdata(L, 1);
	if (c == NULL)
		return luaL_error(L, "Invalid channel pointer");
	new_channel(L, c);

	return 1;
}