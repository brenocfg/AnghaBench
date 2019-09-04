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
struct table {int dummy; } ;
struct state {struct table* root; scalar_t__ ref; scalar_t__ dirty; } ;
struct context {scalar_t__ string_index; int /*<<< orphan*/ * L; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_GCCOLLECT ; 
 scalar_t__ LUA_MINSTACK ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct state* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,scalar_t__) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
convert_stringmap(struct context *ctx, struct table *tbl) {
	lua_State *L = ctx->L;
	lua_checkstack(L, ctx->string_index + LUA_MINSTACK);
	lua_settop(L, ctx->string_index + 1);
	lua_pushvalue(L, 1);
	struct state * s = lua_newuserdata(L, sizeof(*s));
	s->dirty = 0;
	s->ref = 0;
	s->root = tbl;
	lua_replace(L, 1);
	lua_replace(L, -2);

	lua_pushnil(L);
	// ... stringmap nil
	while (lua_next(L, -2) != 0) {
		int idx = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushvalue(L, -1);
		lua_replace(L, idx);
	}

	lua_pop(L, 1);

	lua_gc(L, LUA_GCCOLLECT, 0);
}