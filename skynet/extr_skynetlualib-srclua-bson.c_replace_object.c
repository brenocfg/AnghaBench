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
typedef  int /*<<< orphan*/  uint32_t ;
struct bson {int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int int64_t ;

/* Variables and functions */
#define  BSON_DATE 130 
#define  BSON_OBJECTID 129 
#define  BSON_TIMESTAMP 128 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  write_int32 (struct bson*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_int64 (struct bson*,int) ; 

__attribute__((used)) static void
replace_object(lua_State *L, int type, struct bson * bs) {
	size_t len = 0;
	const char * data = luaL_checklstring(L,3, &len);
	if (len < 6 || data[0] != 0 || data[1] != type) {
		luaL_error(L, "Type mismatch, need bson type %d", type);
	}
	switch (type) {
	case BSON_OBJECTID:
		if (len != 2+12) {
			luaL_error(L, "Invalid object id");
		}
		memcpy(bs->ptr, data+2, 12);
		break;
	case BSON_DATE: {
		if (len != 2+4) {
			luaL_error(L, "Invalid date");
		}
		const uint32_t * ts = (const uint32_t *)(data + 2);
		int64_t v = (int64_t)*ts * 1000;
		write_int64(bs, v);
		break;
	}
	case BSON_TIMESTAMP: {
		if (len != 2+8) {
			luaL_error(L, "Invalid timestamp");
		}
		const uint32_t * inc = (const uint32_t *)(data + 2);
		const uint32_t * ts = (const uint32_t *)(data + 6);
		write_int32(bs, *inc);
		write_int32(bs, *ts);
		break;
	}
	}
}