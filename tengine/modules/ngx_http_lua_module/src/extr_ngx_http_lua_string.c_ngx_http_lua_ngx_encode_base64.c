#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TBOOLEAN ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_http_lua_base64_encoded_length (scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_http_lua_encode_base64 (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_encode_base64(lua_State *L)
{
    int                      n;
    int                      no_padding = 0;
    ngx_str_t                p, src;

    n = lua_gettop(L);
    if (n != 1 && n != 2) {
        return luaL_error(L, "expecting one or two arguments");
    }

    if (lua_isnil(L, 1)) {
        src.data = (u_char *) "";
        src.len = 0;

    } else {
        src.data = (u_char *) luaL_checklstring(L, 1, &src.len);
    }

    if (n == 2) {
        /* get the 2nd optional argument */
        luaL_checktype(L, 2, LUA_TBOOLEAN);
        no_padding = lua_toboolean(L, 2);
    }

    p.len = ngx_http_lua_base64_encoded_length(src.len, no_padding);

    p.data = lua_newuserdata(L, p.len);

    ngx_http_lua_encode_base64(&p, &src, no_padding);

    lua_pushlstring(L, (char *) p.data, p.len);

    return 1;
}