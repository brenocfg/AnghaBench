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
typedef  int UC ;

/* Variables and functions */
 int /*<<< orphan*/  CRLF ; 
 int /*<<< orphan*/  EQCRLF ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_optlstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mime_global_qpwrp(lua_State *L)
{
    size_t size = 0;
    int left = (int) luaL_checknumber(L, 1);
    const UC *input = (UC *) luaL_optlstring(L, 2, NULL, &size);
    const UC *last = input + size;
    int length = (int) luaL_optnumber(L, 3, 76);
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        if (left < length) lua_pushstring(L, EQCRLF);
        else lua_pushnil(L);
        lua_pushnumber(L, length);
        return 2;
    }
    /* process all input */
    luaL_buffinit(L, &buffer);
    while (input < last) {
        switch (*input) {
            case '\r':
                break;
            case '\n':
                left = length;
                luaL_addstring(&buffer, CRLF);
                break;
            case '=':
                if (left <= 3) {
                    left = length;
                    luaL_addstring(&buffer, EQCRLF);
                } 
                luaL_addchar(&buffer, *input);
                left--;
                break;
            default: 
                if (left <= 1) {
                    left = length;
                    luaL_addstring(&buffer, EQCRLF);
                }
                luaL_addchar(&buffer, *input);
                left--;
                break;
        }
        input++;
    }
    luaL_pushresult(&buffer);
    lua_pushnumber(L, left);
    return 2;
}