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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Integer ;

/* Variables and functions */
#define  BSON_BINARY 139 
#define  BSON_CODEWS 138 
#define  BSON_DATE 137 
#define  BSON_DBPOINTER 136 
#define  BSON_JSCODE 135 
#define  BSON_MAXKEY 134 
#define  BSON_MINKEY 133 
#define  BSON_NULL 132 
#define  BSON_OBJECTID 131 
#define  BSON_REGEX 130 
#define  BSON_SYMBOL 129 
#define  BSON_TIMESTAMP 128 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 

__attribute__((used)) static int
lsubtype(lua_State *L, int subtype, const uint8_t * buf, size_t sz) {
	switch(subtype) {
	case BSON_BINARY:
		lua_pushvalue(L, lua_upvalueindex(6));
		lua_pushlstring(L, (const char *)buf+1, sz-1);
		lua_pushinteger(L, buf[0]);
		return 3;
	case BSON_OBJECTID: {
		if (sz != 12) {
			return luaL_error(L, "Invalid object id");
		}
		char oid[24];
		int i;
		const uint8_t * id = buf;
		static char *hex = "0123456789abcdef";
		for (i=0;i<12;i++) {
			oid[i*2] = hex[id[i] >> 4];
			oid[i*2+1] = hex[id[i] & 0xf];
		}
		lua_pushvalue(L, lua_upvalueindex(7));
		lua_pushlstring(L, oid, 24);

		return 2;
	}
	case BSON_DATE: {
		if (sz != 4) {
			return luaL_error(L, "Invalid date");
		}
		int d = *(const int *)buf;
		lua_pushvalue(L, lua_upvalueindex(9));
		lua_pushinteger(L, d);
		return 2;
	}
	case BSON_TIMESTAMP: {
		if (sz != 8) {
			return luaL_error(L, "Invalid timestamp");
		}
		const uint32_t * ts = (const uint32_t *)buf;
		lua_pushvalue(L, lua_upvalueindex(8));
		lua_pushinteger(L, (lua_Integer)ts[1]);
		lua_pushinteger(L, (lua_Integer)ts[0]);
		return 3;
	}
	case BSON_REGEX: {
		--sz;
		size_t i;
		const uint8_t *str = buf;
		for (i=0;i<sz;i++) {
			if (str[sz-i-1]==0) {
				break;
			}
		}
		lua_pushvalue(L, lua_upvalueindex(10));
		if (i==sz) {
			return luaL_error(L, "Invalid regex");
		}
		lua_pushlstring(L, (const char *)str, sz - i - 1);
		lua_pushlstring(L, (const char *)str+sz-i, i);
		return 3;
	}
	case BSON_MINKEY:
		lua_pushvalue(L, lua_upvalueindex(11));
		return 1;
	case BSON_MAXKEY:
		lua_pushvalue(L, lua_upvalueindex(12));
		return 1;
	case BSON_NULL:
		lua_pushvalue(L, lua_upvalueindex(4));
		return 1;
	case BSON_JSCODE:
	case BSON_DBPOINTER:
	case BSON_SYMBOL:
	case BSON_CODEWS:
		lua_pushvalue(L, lua_upvalueindex(13));
		lua_pushlstring(L, (const char *)buf, sz);
		return 2;
	default:
		return luaL_error(L, "Invalid subtype %d", subtype);
	}
}