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
struct TYPE_2__ {int lua_replicate_commands; scalar_t__ lua_write_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  redisSrand48 (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 

int luaRedisReplicateCommandsCommand(lua_State *lua) {
    if (server.lua_write_dirty) {
        lua_pushboolean(lua,0);
    } else {
        server.lua_replicate_commands = 1;
        /* When we switch to single commands replication, we can provide
         * different math.random() sequences at every call, which is what
         * the user normally expects. */
        redisSrand48(rand());
        lua_pushboolean(lua,1);
    }
    return 1;
}