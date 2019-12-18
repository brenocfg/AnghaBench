#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {TYPE_1__* lua_client; } ;
struct TYPE_3__ {int resp; } ;

/* Variables and functions */
 int lua_error (int /*<<< orphan*/ *) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ server ; 

int luaSetResp(lua_State *lua) {
    int argc = lua_gettop(lua);

    if (argc != 1) {
        lua_pushstring(lua, "redis.setresp() requires one argument.");
        return lua_error(lua);
    }

    int resp = lua_tonumber(lua,-argc);
    if (resp != 2 && resp != 3) {
        lua_pushstring(lua, "RESP version must be 2 or 3.");
        return lua_error(lua);
    }

    server.lua_client->resp = resp;
    return 0;
}