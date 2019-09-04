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
struct bson {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TNIL ; 
 scalar_t__ luaL_getmetafield (int /*<<< orphan*/ *,int,char*) ; 
 void* lua_newuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 struct bson* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_meta_dict (int /*<<< orphan*/ *,struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_simple_dict (int /*<<< orphan*/ *,struct bson*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
encode_bson(lua_State *L) {
	struct bson *b = lua_touserdata(L, 2);
	lua_settop(L, 1);
	if (luaL_getmetafield(L, -1, "__pairs") != LUA_TNIL) {
		pack_meta_dict(L, b, 0);
	} else {
		pack_simple_dict(L, b, 0);
	}
	void * ud = lua_newuserdata(L, b->size);
	memcpy(ud, b->ptr, b->size);
	return 1;
}