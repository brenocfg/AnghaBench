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
struct channel_box {int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  METANAME ; 
 int /*<<< orphan*/  channel_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 struct channel_box* luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lwrite(lua_State *L) {
	struct channel_box *cb = luaL_checkudata(L,1, METANAME);
	size_t sz;
	const char * str = luaL_checklstring(L, 2, &sz);
	channel_write(cb->c, str, sz);
	return 0;
}