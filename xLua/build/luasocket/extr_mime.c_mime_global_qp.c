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
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int /*<<< orphan*/  UC ;

/* Variables and functions */
 int /*<<< orphan*/  CRLF ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_optlstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_tostring (int /*<<< orphan*/ *,int) ; 
 size_t qpencode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,char const*,int /*<<< orphan*/ *) ; 
 size_t qppad (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mime_global_qp(lua_State *L)
{

    size_t asize = 0, isize = 0;
    UC atom[3];
    const UC *input = (UC *) luaL_optlstring(L, 1, NULL, &isize);
    const UC *last = input + isize;
    const char *marker = luaL_optstring(L, 3, CRLF);
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* make sure we don't confuse buffer stuff with arguments */
    lua_settop(L, 3);
    /* process first part of input */
    luaL_buffinit(L, &buffer);
    while (input < last)
        asize = qpencode(*input++, atom, asize, marker, &buffer);
    input = (UC *) luaL_optlstring(L, 2, NULL, &isize);
    /* if second part is nil, we are done */
    if (!input) {
        asize = qppad(atom, asize, &buffer);
        luaL_pushresult(&buffer);
        if (!(*lua_tostring(L, -1))) lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
    /* otherwise process rest of input */
    last = input + isize;
    while (input < last)
        asize = qpencode(*input++, atom, asize, marker, &buffer);
    luaL_pushresult(&buffer);
    lua_pushlstring(L, (char *) atom, asize);
    return 2;
}