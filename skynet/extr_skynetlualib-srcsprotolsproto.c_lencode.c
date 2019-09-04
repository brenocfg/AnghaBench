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
struct encode_ud {int tbl_index; scalar_t__ iter_key; scalar_t__ iter_table; scalar_t__ iter_func; scalar_t__ deep; scalar_t__ array_index; int /*<<< orphan*/ * array_tag; struct sproto_type* st; int /*<<< orphan*/ * L; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TNIL ; 
 int /*<<< orphan*/  encode ; 
 void* expand_buffer (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_upvalueindex (int) ; 
 int sproto_encode (struct sproto_type*,void*,int,int /*<<< orphan*/ ,struct encode_ud*) ; 

__attribute__((used)) static int
lencode(lua_State *L) {
	struct encode_ud self;
	void * buffer = lua_touserdata(L, lua_upvalueindex(1));
	int sz = lua_tointeger(L, lua_upvalueindex(2));
	int tbl_index = 2;
	struct sproto_type * st = lua_touserdata(L, 1);
	if (st == NULL) {
		luaL_checktype(L, tbl_index, LUA_TNIL);
		lua_pushstring(L, "");
		return 1;	// response nil
	}
	self.L = L;
	self.st = st;
	self.tbl_index = tbl_index;
	for (;;) {
		int r;
		self.array_tag = NULL;
		self.array_index = 0;
		self.deep = 0;

		lua_settop(L, tbl_index);
		self.iter_func = 0;
		self.iter_table = 0;
		self.iter_key = 0;

		r = sproto_encode(st, buffer, sz, encode, &self);
		if (r<0) {
			buffer = expand_buffer(L, sz, sz*2);
			sz *= 2;
		} else {
			lua_pushlstring(L, buffer, r);
			return 1;
		}
	}
}