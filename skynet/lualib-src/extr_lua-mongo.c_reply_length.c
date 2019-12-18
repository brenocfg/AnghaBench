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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int little_endian (int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 

__attribute__((used)) static int
reply_length(lua_State *L) {
	const char * rawlen_str = luaL_checkstring(L, 1);
	int rawlen = 0;
	memcpy(&rawlen, rawlen_str, sizeof(int));
	int length = little_endian(rawlen);
	lua_pushinteger(L, length - 4);
	return 1;
}