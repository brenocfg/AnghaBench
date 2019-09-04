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
 int /*<<< orphan*/  BSON_ARRAY ; 
 int /*<<< orphan*/  BSON_DOCUMENT ; 
 scalar_t__ LUA_TNIL ; 
 int MAX_DEPTH ; 
 int /*<<< orphan*/  append_key (struct bson*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ is_rawarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_getmetafield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 size_t lua_rawlen (int /*<<< orphan*/ *,int) ; 
 size_t lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pack_array (int /*<<< orphan*/ *,struct bson*,int,size_t) ; 
 int /*<<< orphan*/  pack_meta_dict (int /*<<< orphan*/ *,struct bson*,int) ; 
 int /*<<< orphan*/  pack_simple_dict (int /*<<< orphan*/ *,struct bson*,int) ; 

__attribute__((used)) static void
append_table(struct bson *bs, lua_State *L, const char *key, size_t sz, int depth) {
	if (depth > MAX_DEPTH) {
		luaL_error(L, "Too depth while encoding bson");
	}
	luaL_checkstack(L, 16, NULL);	// reserve enough stack space to pack table
	if (luaL_getmetafield(L, -1, "__len") != LUA_TNIL) {
		lua_pushvalue(L, -2);
		lua_call(L, 1, 1);
		if (!lua_isinteger(L, -1)) {
			luaL_error(L, "__len should return integer");
		}
		size_t len = lua_tointeger(L, -1);
		lua_pop(L, 1);
		append_key(bs, L, BSON_ARRAY, key, sz);
		pack_array(L, bs, depth, len);
	} else if (luaL_getmetafield(L, -1, "__pairs") != LUA_TNIL) {
		append_key(bs, L, BSON_DOCUMENT, key, sz);
		pack_meta_dict(L, bs, depth);
	} else if (is_rawarray(L)) {
		append_key(bs, L, BSON_ARRAY, key, sz);
		pack_array(L, bs, depth, lua_rawlen(L, -1));
	} else {
		append_key(bs, L, BSON_DOCUMENT, key, sz);
		pack_simple_dict(L, bs, depth);
	}
}