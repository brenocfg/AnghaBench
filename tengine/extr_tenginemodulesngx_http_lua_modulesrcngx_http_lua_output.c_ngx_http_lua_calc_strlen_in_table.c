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
#define  LUA_TBOOLEAN 133 
#define  LUA_TLIGHTUSERDATA 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  dd (char*,int) ; 
 double floor (double) ; 
 size_t luaL_argerror (int /*<<< orphan*/ *,int,char const*) ; 
 int luaL_typename (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 

size_t
ngx_http_lua_calc_strlen_in_table(lua_State *L, int index, int arg_i,
    unsigned strict)
{
    double              key;
    int                 max;
    int                 i;
    int                 type;
    size_t              size;
    size_t              len;
    const char         *msg;

    if (index < 0) {
        index = lua_gettop(L) + index + 1;
    }

    dd("table index: %d", index);

    max = 0;

    lua_pushnil(L); /* stack: table key */
    while (lua_next(L, index) != 0) { /* stack: table key value */
        dd("key type: %s", luaL_typename(L, -2));

        if (lua_type(L, -2) == LUA_TNUMBER) {

            key = lua_tonumber(L, -2);

            dd("key value: %d", (int) key);

            if (floor(key) == key && key >= 1) {
                if (key > max) {
                    max = (int) key;
                }

                lua_pop(L, 1); /* stack: table key */
                continue;
            }
        }

        /* not an array (non positive integer key) */
        lua_pop(L, 2); /* stack: table */

        luaL_argerror(L, arg_i, "non-array table found");
        return 0;
    }

    size = 0;

    for (i = 1; i <= max; i++) {
        lua_rawgeti(L, index, i); /* stack: table value */
        type = lua_type(L, -1);

        switch (type) {
            case LUA_TNUMBER:
            case LUA_TSTRING:

                lua_tolstring(L, -1, &len);
                size += len;
                break;

            case LUA_TNIL:

                if (strict) {
                    goto bad_type;
                }

                size += sizeof("nil") - 1;
                break;

            case LUA_TBOOLEAN:

                if (strict) {
                    goto bad_type;
                }

                if (lua_toboolean(L, -1)) {
                    size += sizeof("true") - 1;

                } else {
                    size += sizeof("false") - 1;
                }

                break;

            case LUA_TTABLE:

                size += ngx_http_lua_calc_strlen_in_table(L, -1, arg_i, strict);
                break;

            case LUA_TLIGHTUSERDATA:

                if (strict) {
                    goto bad_type;
                }

                if (lua_touserdata(L, -1) == NULL) {
                    size += sizeof("null") - 1;
                    break;
                }

                continue;

            default:

bad_type:

                msg = lua_pushfstring(L, "bad data type %s found",
                                      lua_typename(L, type));
                return luaL_argerror(L, arg_i, msg);
        }

        lua_pop(L, 1); /* stack: table */
    }

    return size;
}