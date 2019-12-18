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
struct bson {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int /*<<< orphan*/  append_one (struct bson*,int /*<<< orphan*/ *,char const*,size_t,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pack_dict_data(lua_State *L, struct bson *b, int depth, int kt) {
	const char * key = NULL;
	size_t sz;
	switch(kt) {
	case LUA_TNUMBER:
		luaL_error(L, "Bson dictionary's key can't be number");
		break;
	case LUA_TSTRING:
		key = lua_tolstring(L,-2,&sz);
		append_one(b, L, key, sz, depth);
		lua_pop(L,1);
		break;
	default:
		luaL_error(L, "Invalid key type : %s", lua_typename(L, kt));
		return;
	}
}