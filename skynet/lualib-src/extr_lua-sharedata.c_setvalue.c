#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct table {int dummy; } ;
struct TYPE_2__ {struct table* tbl; int /*<<< orphan*/  boolean; int /*<<< orphan*/  string; int /*<<< orphan*/  n; int /*<<< orphan*/  d; } ;
struct node {int /*<<< orphan*/  valuetype; TYPE_1__ v; } ;
struct context {struct table* tbl; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TBOOLEAN 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  VALUETYPE_BOOLEAN ; 
 int /*<<< orphan*/  VALUETYPE_INTEGER ; 
 int /*<<< orphan*/  VALUETYPE_NIL ; 
 int /*<<< orphan*/  VALUETYPE_REAL ; 
 int /*<<< orphan*/  VALUETYPE_STRING ; 
 int /*<<< orphan*/  VALUETYPE_TABLE ; 
 int /*<<< orphan*/  convtable ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_absindex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct context*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stringindex (struct context*,char const*,size_t) ; 

__attribute__((used)) static void
setvalue(struct context * ctx, lua_State *L, int index, struct node *n) {
	int vt = lua_type(L, index);
	switch(vt) {
	case LUA_TNIL:
		n->valuetype = VALUETYPE_NIL;
		break;
	case LUA_TNUMBER:
		if (lua_isinteger(L, index)) {
			n->v.d = lua_tointeger(L, index);
			n->valuetype = VALUETYPE_INTEGER;
		} else {
			n->v.n = lua_tonumber(L, index);
			n->valuetype = VALUETYPE_REAL;
		}
		break;
	case LUA_TSTRING: {
		size_t sz = 0;
		const char * str = lua_tolstring(L, index, &sz);
		n->v.string = stringindex(ctx, str, sz);
		n->valuetype = VALUETYPE_STRING;
		break;
	}
	case LUA_TBOOLEAN:
		n->v.boolean = lua_toboolean(L, index);
		n->valuetype = VALUETYPE_BOOLEAN;
		break;
	case LUA_TTABLE: {
		struct table *tbl = ctx->tbl;
		ctx->tbl = (struct table *)malloc(sizeof(struct table));
		if (ctx->tbl == NULL) {
			ctx->tbl = tbl;
			luaL_error(L, "memory error");
			// never get here
		}
		memset(ctx->tbl, 0, sizeof(struct table));
		int absidx = lua_absindex(L, index);

		lua_pushcfunction(L, convtable);
		lua_pushvalue(L, absidx);
		lua_pushlightuserdata(L, ctx);

		lua_call(L, 2, 0);

		n->v.tbl = ctx->tbl;
		n->valuetype = VALUETYPE_TABLE;

		ctx->tbl = tbl;

		break;
	}
	default:
		luaL_error(L, "Unsupport value type %s", lua_typename(L, vt));
		break;
	}
}