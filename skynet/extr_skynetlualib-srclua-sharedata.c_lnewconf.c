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
struct table {int string_index; struct table* L; struct table* tbl; } ;
struct context {int string_index; struct context* L; struct context* tbl; } ;
typedef  struct table lua_State ;

/* Variables and functions */
 int LUA_OK ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  convert_stringmap (struct table*,struct table*) ; 
 int /*<<< orphan*/  delete_tbl (struct table*) ; 
 int /*<<< orphan*/  luaL_checktype (struct table*,int,int /*<<< orphan*/ ) ; 
 struct table* luaL_newstate () ; 
 int /*<<< orphan*/  lua_close (struct table*) ; 
 int /*<<< orphan*/  lua_error (struct table*) ; 
 int lua_pcall (struct table*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (struct table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (struct table*,struct table*) ; 
 int /*<<< orphan*/  lua_pushliteral (struct table*,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (struct table*,char const*,size_t) ; 
 char* lua_tolstring (struct table*,int,size_t*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pconv ; 

__attribute__((used)) static int
lnewconf(lua_State *L) {
	int ret;
	struct context ctx;
	struct table * tbl = NULL;
	luaL_checktype(L,1,LUA_TTABLE);
	ctx.L = luaL_newstate();
	ctx.tbl = NULL;
	ctx.string_index = 1;	// 1 reserved for dirty flag
	if (ctx.L == NULL) {
		lua_pushliteral(L, "memory error");
		goto error;
	}
	tbl = (struct table *)malloc(sizeof(struct table));
	if (tbl == NULL) {
		// lua_pushliteral may fail because of memory error, close first.
		lua_close(ctx.L);
		ctx.L = NULL;
		lua_pushliteral(L, "memory error");
		goto error;
	}
	memset(tbl, 0, sizeof(struct table));
	ctx.tbl = tbl;

	lua_pushcfunction(ctx.L, pconv);
	lua_pushlightuserdata(ctx.L , &ctx);
	lua_pushlightuserdata(ctx.L , L);

	ret = lua_pcall(ctx.L, 2, 1, 0);

	if (ret != LUA_OK) {
		size_t sz = 0;
		const char * error = lua_tolstring(ctx.L, -1, &sz);
		lua_pushlstring(L, error, sz);
		goto error;
	}

	convert_stringmap(&ctx, tbl);

	lua_pushlightuserdata(L, tbl);	

	return 1;
error:
	if (ctx.L) {
		lua_close(ctx.L);
	}
	if (tbl) {
		delete_tbl(tbl);
	}
	lua_error(L);
	return -1;
}