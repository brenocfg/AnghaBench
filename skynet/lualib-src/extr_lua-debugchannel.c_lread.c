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
struct command {int /*<<< orphan*/  sz; } ;
struct channel_box {int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  METANAME ; 
 struct command* channel_read (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  free (struct command*) ; 
 struct channel_box* luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 double luaL_optnumber (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lread(lua_State *L) {
	struct channel_box *cb = luaL_checkudata(L,1, METANAME);
	double ti = luaL_optnumber(L, 2, 0);
	struct command * c = channel_read(cb->c, ti);
	if (c == NULL)
		return 0;
	lua_pushlstring(L, (const char *)(c+1), c->sz);
	free(c);
	return 1;
}