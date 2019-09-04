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
typedef  int /*<<< orphan*/ * document ;

/* Variables and functions */
 int get_length (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
document_length(lua_State *L) {
	if (lua_isuserdata(L, 3)) {
		document doc = lua_touserdata(L,3);
		return get_length(doc);
	}
	if (lua_istable(L,3)) {
		int total = 0;
		int s = lua_rawlen(L,3);
		int i;
		for (i=1;i<=s;i++) {
			lua_rawgeti(L, 3, i);
			document doc = lua_touserdata(L,-1);
			if (doc == NULL) {
				lua_pop(L,1);
				return luaL_error(L, "Invalid document at %d", i);
			} else {
				total += get_length(doc);
				lua_pop(L,1);
			}
		}
		return total;
	}
	return luaL_error(L, "Insert need documents");
}