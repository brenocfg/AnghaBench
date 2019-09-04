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
typedef  int /*<<< orphan*/  uint8_t ;
struct bson {int member_1; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  void* int64_t ;
typedef  void* int32_t ;

/* Variables and functions */
#define  BSON_BOOLEAN 134 
#define  BSON_DATE 133 
#define  BSON_INT32 132 
#define  BSON_INT64 131 
#define  BSON_OBJECTID 130 
#define  BSON_REAL 129 
#define  BSON_TIMESTAMP 128 
 int BSON_TYPE_SHIFT ; 
 scalar_t__ LUA_TNUMBER ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 void* lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  replace_object (int /*<<< orphan*/ *,int,struct bson*) ; 
 int /*<<< orphan*/  write_byte (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_double (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_int32 (struct bson*,void*) ; 
 int /*<<< orphan*/  write_int64 (struct bson*,void*) ; 

__attribute__((used)) static int
lreplace(lua_State *L) {
	lua_getuservalue(L,1);
	if (!lua_istable(L,-1)) {
		return luaL_error(L, "call makeindex first");
	}
	lua_pushvalue(L,2);
	if (lua_rawget(L, -2) != LUA_TNUMBER) {
		return luaL_error(L, "Can't replace key : %s", lua_tostring(L,2));
	}
	int id = lua_tointeger(L, -1);
	int type = id & ((1<<(BSON_TYPE_SHIFT)) - 1);
	int offset = id >> BSON_TYPE_SHIFT;
	uint8_t * start = lua_touserdata(L,1);
	struct bson b = { 0,16, start + offset };
	switch (type) {
	case BSON_REAL:
		write_double(&b, luaL_checknumber(L, 3));
		break;
	case BSON_BOOLEAN:
		write_byte(&b, lua_toboolean(L,3));
		break;
	case BSON_OBJECTID:
	case BSON_DATE:
	case BSON_TIMESTAMP:
		replace_object(L, type, &b);
		break;
	case BSON_INT32: {
		if (!lua_isinteger(L, 3)) {
			luaL_error(L, "%f must be a 32bit integer ", lua_tonumber(L, 3));
		}
		int32_t i = lua_tointeger(L,3);
		write_int32(&b, i);
		break;
	}
	case BSON_INT64: {
		if (!lua_isinteger(L, 3)) {
			luaL_error(L, "%f must be a 64bit integer ", lua_tonumber(L, 3));
		}
		int64_t i = lua_tointeger(L,3);
		write_int64(&b, i);
		break;
	}
	default:
		luaL_error(L, "Can't replace type %d", type);
		break;
	}
	return 0;
}