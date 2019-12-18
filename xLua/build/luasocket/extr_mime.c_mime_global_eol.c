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

/* Variables and functions */
 int /*<<< orphan*/  CRLF ; 
 int eolprocess (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 char* luaL_optlstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mime_global_eol(lua_State *L)
{
    int ctx = luaL_checkint(L, 1);
    size_t isize = 0;
    const char *input = luaL_optlstring(L, 2, NULL, &isize);
    const char *last = input + isize;
    const char *marker = luaL_optstring(L, 3, CRLF);
    luaL_Buffer buffer;
    luaL_buffinit(L, &buffer);
    /* end of input blackhole */
    if (!input) {
       lua_pushnil(L);
       lua_pushnumber(L, 0);
       return 2;
    }
    /* process all input */
    while (input < last)
        ctx = eolprocess(*input++, ctx, marker, &buffer);
    luaL_pushresult(&buffer);
    lua_pushnumber(L, ctx);
    return 2;
}