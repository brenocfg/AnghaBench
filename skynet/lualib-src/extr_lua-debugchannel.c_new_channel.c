#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct channel_box {struct channel* c; } ;
struct channel {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/  METANAME ; 
 struct channel* channel_connect (struct channel*) ; 
 struct channel* channel_new () ; 
 int /*<<< orphan*/ * lread ; 
 int /*<<< orphan*/  lrelease ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct channel_box* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lwrite ; 

__attribute__((used)) static struct channel *
new_channel(lua_State *L, struct channel *c) {
	if (c == NULL) {
		c = channel_new();
	} else {
		c = channel_connect(c);
	}
	if (c == NULL) {
		luaL_error(L, "new channel failed");
		// never go here
	}
	struct channel_box * cb = lua_newuserdata(L, sizeof(*cb));
	cb->c = c;
	if (luaL_newmetatable(L, METANAME)) {
		luaL_Reg l[]={
			{ "read", lread },
			{ "write", lwrite },
			{ NULL, NULL },
		};
		luaL_newlib(L,l);
		lua_setfield(L, -2, "__index");
		lua_pushcfunction(L, lrelease);
		lua_setfield(L, -2, "__gc");
	}
	lua_setmetatable(L, -2);
	return c;
}