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
struct bson_reader {scalar_t__ size; int /*<<< orphan*/  const* ptr; int /*<<< orphan*/  member_1; int /*<<< orphan*/  const* member_0; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  BSON_ARRAY 146 
#define  BSON_BINARY 145 
#define  BSON_BOOLEAN 144 
#define  BSON_CODEWS 143 
#define  BSON_DATE 142 
#define  BSON_DBPOINTER 141 
#define  BSON_DOCUMENT 140 
#define  BSON_INT32 139 
#define  BSON_INT64 138 
#define  BSON_JSCODE 137 
#define  BSON_MAXKEY 136 
#define  BSON_MINKEY 135 
#define  BSON_NULL 134 
#define  BSON_OBJECTID 133 
#define  BSON_REAL 132 
#define  BSON_REGEX 131 
#define  BSON_STRING 130 
#define  BSON_SYMBOL 129 
#define  BSON_TIMESTAMP 128 
 int BSON_TYPE_SHIFT ; 
 int /*<<< orphan*/  get_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setuservalue (int /*<<< orphan*/ *,int) ; 
 int read_byte (int /*<<< orphan*/ *,struct bson_reader*) ; 
 int /*<<< orphan*/  read_bytes (int /*<<< orphan*/ *,struct bson_reader*,int) ; 
 char* read_cstring (int /*<<< orphan*/ *,struct bson_reader*,size_t*) ; 
 int read_int32 (int /*<<< orphan*/ *,struct bson_reader*) ; 

__attribute__((used)) static int
lmakeindex(lua_State *L) {
	int32_t *bson = luaL_checkudata(L,1,"bson");
	const uint8_t * start = (const uint8_t *)bson;
	struct bson_reader br = { start+4, get_length(start) - 5 };
	lua_newtable(L);

	for (;;) {
		if (br.size == 0)
			break;
		int bt = read_byte(L, &br);
		size_t klen = 0;
		const char * key = read_cstring(L, &br, &klen);
		int field_size = 0;
		switch (bt) {
		case BSON_INT64:
		case BSON_TIMESTAMP: 
		case BSON_DATE:
		case BSON_REAL:
			field_size = 8;
			break;
		case BSON_BOOLEAN:
			field_size = 1;
			break;
		case BSON_JSCODE:
		case BSON_SYMBOL: 
		case BSON_STRING: {
			int sz = read_int32(L, &br);
			read_bytes(L, &br, sz);
			break;
		}
		case BSON_CODEWS:
		case BSON_ARRAY:
		case BSON_DOCUMENT: {
			int sz = read_int32(L, &br);
			read_bytes(L, &br, sz-4);
			break;
		}
		case BSON_BINARY: {
			int sz = read_int32(L, &br);
			read_bytes(L, &br, sz+1);
			break;
		}
		case BSON_OBJECTID:
			field_size = 12;
			break;
		case BSON_MINKEY:
		case BSON_MAXKEY:
		case BSON_NULL:
			break;
		case BSON_REGEX: {
			size_t rlen1=0;
			size_t rlen2=0;
			read_cstring(L, &br, &rlen1);
			read_cstring(L, &br, &rlen2);
			break;
		}
		case BSON_INT32:
			field_size = 4;
			break;
		case BSON_DBPOINTER: {
			int sz = read_int32(L, &br);
			read_bytes(L, &br, sz+12);
			break;
		}
		default:
			// unsupported
			luaL_error(L, "Invalid bson type : %d", bt);
			lua_pop(L,1);
			continue;
		}
		if (field_size > 0) {
			int id = bt | (int)(br.ptr - start) << BSON_TYPE_SHIFT;
			read_bytes(L, &br, field_size);
			lua_pushlstring(L, key, klen);
			lua_pushinteger(L,id);
			lua_rawset(L,-3);
		}
	}
	lua_setuservalue(L,1);
	lua_settop(L,1);

	return 1;
}