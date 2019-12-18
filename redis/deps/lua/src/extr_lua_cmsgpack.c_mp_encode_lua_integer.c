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
typedef  int /*<<< orphan*/  mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  scalar_t__ lua_Integer ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_encode_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mp_encode_lua_integer(lua_State *L, mp_buf *buf) {
#if (LUA_VERSION_NUM < 503) && BITS_32
    lua_Number i = lua_tonumber(L,-1);
#else
    lua_Integer i = lua_tointeger(L,-1);
#endif
    mp_encode_int(L, buf, (int64_t)i);
}