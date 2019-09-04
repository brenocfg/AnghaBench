#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ lua_replicate_commands; int lua_repl; } ;

/* Variables and functions */
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int lua_error (int /*<<< orphan*/ *) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ server ; 

int luaRedisSetReplCommand(lua_State *lua) {
    int argc = lua_gettop(lua);
    int flags;

    if (server.lua_replicate_commands == 0) {
        lua_pushstring(lua, "You can set the replication behavior only after turning on single commands replication with redis.replicate_commands().");
        return lua_error(lua);
    } else if (argc != 1) {
        lua_pushstring(lua, "redis.set_repl() requires two arguments.");
        return lua_error(lua);
    }

    flags = lua_tonumber(lua,-1);
    if ((flags & ~(PROPAGATE_AOF|PROPAGATE_REPL)) != 0) {
        lua_pushstring(lua, "Invalid replication flags. Use REPL_AOF, REPL_REPLICA, REPL_ALL or REPL_NONE.");
        return lua_error(lua);
    }
    server.lua_repl = flags;
    return 0;
}