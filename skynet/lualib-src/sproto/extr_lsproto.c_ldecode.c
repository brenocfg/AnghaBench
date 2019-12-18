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
struct sproto_type {int dummy; } ;
struct decode_ud {int mainindex_tag; int /*<<< orphan*/  result_index; scalar_t__ key_index; scalar_t__ deep; int /*<<< orphan*/ * array_tag; scalar_t__ array_index; int /*<<< orphan*/ * L; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  decode ; 
 void* getbuffer (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sproto_type* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int sproto_decode (struct sproto_type*,void const*,int,int /*<<< orphan*/ ,struct decode_ud*) ; 

__attribute__((used)) static int
ldecode(lua_State *L) {
	struct sproto_type * st = lua_touserdata(L, 1);
	const void * buffer;
	struct decode_ud self;
	size_t sz;
	int r;
	if (st == NULL) {
		// return nil
		return 0;
	}
	sz = 0;
	buffer = getbuffer(L, 2, &sz);
	if (!lua_istable(L, -1)) {
		lua_newtable(L);
	}
	self.L = L;
	self.result_index = lua_gettop(L);
	self.array_index = 0;
	self.array_tag = NULL;
	self.deep = 0;
	self.mainindex_tag = -1;
	self.key_index = 0;
	r = sproto_decode(st, buffer, (int)sz, decode, &self);
	if (r < 0) {
		return luaL_error(L, "decode error");
	}
	lua_settop(L, self.result_index);
	lua_pushinteger(L, r);
	return 2;
}