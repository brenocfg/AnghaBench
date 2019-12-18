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
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_dyups_delete_upstream (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
ngx_http_lua_delete_upstream(lua_State *L)
{
    ngx_int_t  status;
    ngx_str_t  name, rv;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "exactly 1 argument expected");
    }

    name.data = (u_char *) luaL_checklstring(L, 1, &name.len);

    status = ngx_dyups_delete_upstream(&name, &rv);

    lua_pushinteger(L, (lua_Integer) status);
    lua_pushlstring(L, (char *) rv.data, rv.len);

    return 2;
}