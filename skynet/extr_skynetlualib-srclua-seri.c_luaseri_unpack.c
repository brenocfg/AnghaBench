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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  type ;
struct read_block {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_MINSTACK ; 
 scalar_t__ LUA_TSTRING ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_value (int /*<<< orphan*/ *,struct read_block*,int,int) ; 
 int* rb_read (struct read_block*,int) ; 
 int /*<<< orphan*/  rball_init (struct read_block*,void*,int) ; 

int
luaseri_unpack(lua_State *L) {
	if (lua_isnoneornil(L,1)) {
		return 0;
	}
	void * buffer;
	int len;
	if (lua_type(L,1) == LUA_TSTRING) {
		size_t sz;
		 buffer = (void *)lua_tolstring(L,1,&sz);
		len = (int)sz;
	} else {
		buffer = lua_touserdata(L,1);
		len = luaL_checkinteger(L,2);
	}
	if (len == 0) {
		return 0;
	}
	if (buffer == NULL) {
		return luaL_error(L, "deserialize null pointer");
	}

	lua_settop(L,1);
	struct read_block rb;
	rball_init(&rb, buffer, len);

	int i;
	for (i=0;;i++) {
		if (i%8==7) {
			luaL_checkstack(L,LUA_MINSTACK,NULL);
		}
		uint8_t type = 0;
		uint8_t *t = rb_read(&rb, sizeof(type));
		if (t==NULL)
			break;
		type = *t;
		push_value(L, &rb, type & 0x7, type>>3);
	}

	// Need not free buffer

	return lua_gettop(L) - 1;
}