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
 int LUACMSGPACK_MAX_NESTING ; 
#define  LUA_TBOOLEAN 131 
 int LUA_TNIL ; 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_encode_lua_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_encode_lua_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_encode_lua_null (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_encode_lua_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_encode_lua_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_encode_lua_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void mp_encode_lua_type(lua_State *L, mp_buf *buf, int level) {
    int t = lua_type(L,-1);

    /* Limit the encoding of nested tables to a specified maximum depth, so that
     * we survive when called against circular references in tables. */
    if (t == LUA_TTABLE && level == LUACMSGPACK_MAX_NESTING) t = LUA_TNIL;
    switch(t) {
    case LUA_TSTRING: mp_encode_lua_string(L,buf); break;
    case LUA_TBOOLEAN: mp_encode_lua_bool(L,buf); break;
    case LUA_TNUMBER:
    #if LUA_VERSION_NUM < 503
        mp_encode_lua_number(L,buf); break;
    #else
        if (lua_isinteger(L, -1)) {
            mp_encode_lua_integer(L, buf);
        } else {
            mp_encode_lua_number(L, buf);
        }
        break;
    #endif
    case LUA_TTABLE: mp_encode_lua_table(L,buf,level); break;
    default: mp_encode_lua_null(L,buf); break;
    }
    lua_pop(L,1);
}