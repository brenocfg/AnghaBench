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
struct sproto {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 struct sproto* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sproto_dump (struct sproto*) ; 

__attribute__((used)) static int
ldumpproto(lua_State *L) {
	struct sproto * sp = lua_touserdata(L, 1);
	if (sp == NULL) {
		return luaL_argerror(L, 1, "Need a sproto_type object");
	}
	sproto_dump(sp);

	return 0;
}