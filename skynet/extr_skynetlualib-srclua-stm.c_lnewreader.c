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
struct boxreader {int /*<<< orphan*/ * lastcopy; int /*<<< orphan*/  obj; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct boxreader* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 

__attribute__((used)) static int
lnewreader(lua_State *L) {
	struct boxreader * box = lua_newuserdata(L, sizeof(*box));
	box->obj = lua_touserdata(L, 1);
	box->lastcopy = NULL;
	lua_pushvalue(L, lua_upvalueindex(1));
	lua_setmetatable(L, -2);

	return 1;
}