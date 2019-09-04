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
struct write_block {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
#define  LUA_TBOOLEAN 133 
#define  LUA_TLIGHTUSERDATA 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int MAX_DEPTH ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wb_boolean (struct write_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_free (struct write_block*) ; 
 int /*<<< orphan*/  wb_integer (struct write_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_nil (struct write_block*) ; 
 int /*<<< orphan*/  wb_pointer (struct write_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_real (struct write_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_string (struct write_block*,char const*,int) ; 
 int /*<<< orphan*/  wb_table (int /*<<< orphan*/ *,struct write_block*,int,int) ; 

__attribute__((used)) static void
pack_one(lua_State *L, struct write_block *b, int index, int depth) {
	if (depth > MAX_DEPTH) {
		wb_free(b);
		luaL_error(L, "serialize can't pack too depth table");
	}
	int type = lua_type(L,index);
	switch(type) {
	case LUA_TNIL:
		wb_nil(b);
		break;
	case LUA_TNUMBER: {
		if (lua_isinteger(L, index)) {
			lua_Integer x = lua_tointeger(L,index);
			wb_integer(b, x);
		} else {
			lua_Number n = lua_tonumber(L,index);
			wb_real(b,n);
		}
		break;
	}
	case LUA_TBOOLEAN: 
		wb_boolean(b, lua_toboolean(L,index));
		break;
	case LUA_TSTRING: {
		size_t sz = 0;
		const char *str = lua_tolstring(L,index,&sz);
		wb_string(b, str, (int)sz);
		break;
	}
	case LUA_TLIGHTUSERDATA:
		wb_pointer(b, lua_touserdata(L,index));
		break;
	case LUA_TTABLE: {
		if (index < 0) {
			index = lua_gettop(L) + index + 1;
		}
		wb_table(L, b, index, depth+1);
		break;
	}
	default:
		wb_free(b);
		luaL_error(L, "Unsupport type %s to serialize", lua_typename(L, type));
	}
}