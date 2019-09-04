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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int TEMP_LENGTH ; 
 int /*<<< orphan*/  fill_header (int /*<<< orphan*/ *,int*,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,size_t) ; 

__attribute__((used)) static int
lpacktrace(lua_State *L) {
	size_t sz;
	const char * tag = luaL_checklstring(L, 1, &sz);
	if (sz > 0x8000) {
		return luaL_error(L, "trace tag is too long : %d", (int) sz);
	}
	uint8_t buf[TEMP_LENGTH];
	buf[2] = 4;
	fill_header(L, buf, sz+1);
	memcpy(buf+3, tag, sz);
	lua_pushlstring(L, (const char *)buf, sz+3);
	return 1;
}