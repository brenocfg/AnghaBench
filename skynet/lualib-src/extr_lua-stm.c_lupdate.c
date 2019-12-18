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
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 void* skynet_malloc (size_t) ; 
 int /*<<< orphan*/  stm_update (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
lupdate(lua_State *L) {
	struct boxstm * box = lua_touserdata(L, 1);
	void * msg;
	size_t sz;
	if (lua_isuserdata(L, 2)) {
		msg = lua_touserdata(L, 2);
		sz = (size_t)luaL_checkinteger(L, 3);
	} else {
		const char * tmp = luaL_checklstring(L,2,&sz);
		msg = skynet_malloc(sz);
		memcpy(msg, tmp, sz);
	}
	stm_update(box->obj, msg, sz);

	return 0;
}