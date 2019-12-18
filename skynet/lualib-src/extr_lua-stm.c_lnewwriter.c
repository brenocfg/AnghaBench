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
struct boxstm {int /*<<< orphan*/  obj; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_isuserdata (int /*<<< orphan*/ *,int) ; 
 struct boxstm* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 void* skynet_malloc (size_t) ; 
 int /*<<< orphan*/  stm_new (void*,size_t) ; 

__attribute__((used)) static int
lnewwriter(lua_State *L) {
	void * msg;
	size_t sz;
	if (lua_isuserdata(L,1)) {
		msg = lua_touserdata(L, 1);
		sz = (size_t)luaL_checkinteger(L, 2);
	} else {
		const char * tmp = luaL_checklstring(L,1,&sz);
		msg = skynet_malloc(sz);
		memcpy(msg, tmp, sz);
	}
	struct boxstm * box = lua_newuserdata(L, sizeof(*box));
	box->obj = stm_new(msg,sz);
	lua_pushvalue(L, lua_upvalueindex(1));
	lua_setmetatable(L, -2);

	return 1;
}