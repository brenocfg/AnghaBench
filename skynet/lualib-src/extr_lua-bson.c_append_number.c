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
struct bson {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSON_INT32 ; 
 int /*<<< orphan*/  BSON_INT64 ; 
 int /*<<< orphan*/  BSON_REAL ; 
 int /*<<< orphan*/  append_key (struct bson*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ is_32bit (int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_double (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_int32 (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_int64 (struct bson*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
append_number(struct bson *bs, lua_State *L, const char *key, size_t sz) {
	if (lua_isinteger(L, -1)) {
		int64_t i = lua_tointeger(L, -1);
		if (is_32bit(i)) {
			append_key(bs, L, BSON_INT32, key, sz);
			write_int32(bs, i);
		} else {
			append_key(bs, L, BSON_INT64, key, sz);
			write_int64(bs, i);
		}
	} else {
		lua_Number d = lua_tonumber(L,-1);
		append_key(bs, L, BSON_REAL, key, sz);
		write_double(bs, d);
	}
}