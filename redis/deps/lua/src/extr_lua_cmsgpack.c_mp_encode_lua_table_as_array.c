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

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 size_t lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,size_t) ; 
 size_t lua_rawlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_encode_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mp_encode_lua_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void mp_encode_lua_table_as_array(lua_State *L, mp_buf *buf, int level) {
#if LUA_VERSION_NUM < 502
    size_t len = lua_objlen(L,-1), j;
#else
    size_t len = lua_rawlen(L,-1), j;
#endif

    mp_encode_array(L,buf,len);
    luaL_checkstack(L, 1, "in function mp_encode_lua_table_as_array");
    for (j = 1; j <= len; j++) {
        lua_pushnumber(L,j);
        lua_gettable(L,-2);
        mp_encode_lua_type(L,buf,level+1);
    }
}