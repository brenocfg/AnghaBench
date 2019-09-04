#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pos; int /*<<< orphan*/ * end; int /*<<< orphan*/ * last; int /*<<< orphan*/ * start; } ;
typedef  TYPE_2__ ngx_buf_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ ngx_dyups_update_upstream (TYPE_1__*,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int
ngx_http_lua_update_upstream(lua_State *L)
{
    size_t     size;
    ngx_int_t  status;
    ngx_str_t  name, rv;
    ngx_buf_t  buf;

    if (lua_gettop(L) != 2) {
        return luaL_error(L, "exactly 2 arguments expected");
    }

    name.data = (u_char *) luaL_checklstring(L, 1, &name.len);
    buf.pos = buf.start = (u_char *) luaL_checklstring(L, 2, &size);
    buf.last = buf.end = buf.pos + size;

    status = ngx_dyups_update_upstream(&name, &buf, &rv);

    lua_pushinteger(L, (lua_Integer) status);
    lua_pushlstring(L, (char *) rv.data, rv.len);

    return 2;
}