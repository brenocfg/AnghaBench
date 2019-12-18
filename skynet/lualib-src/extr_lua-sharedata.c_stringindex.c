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
struct context {int string_index; int /*<<< orphan*/ * L; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
stringindex(struct context *ctx, const char * str, size_t sz) {
	lua_State *L = ctx->L;
	lua_pushlstring(L, str, sz);
	lua_pushvalue(L, -1);
	lua_rawget(L, 1);
	int index;
	// stringmap(1) str index
	if (lua_isnil(L, -1)) {
		index = ++ctx->string_index;
		lua_pop(L, 1);
		lua_pushinteger(L, index);
		lua_rawset(L, 1);
	} else {
		index = lua_tointeger(L, -1);
		lua_pop(L, 2);
	}
	return index;
}