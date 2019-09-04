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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int step; } ;
struct TYPE_3__ {int lua_replicate_commands; } ;

/* Variables and functions */
 TYPE_2__ ldb ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 

void ldbRedis(lua_State *lua, sds *argv, int argc) {
    int j, saved_rc = server.lua_replicate_commands;

    lua_getglobal(lua,"redis");
    lua_pushstring(lua,"call");
    lua_gettable(lua,-2);       /* Stack: redis, redis.call */
    for (j = 1; j < argc; j++)
        lua_pushlstring(lua,argv[j],sdslen(argv[j]));
    ldb.step = 1;               /* Force redis.call() to log. */
    server.lua_replicate_commands = 1;
    lua_pcall(lua,argc-1,1,0);  /* Stack: redis, result */
    ldb.step = 0;               /* Disable logging. */
    server.lua_replicate_commands = saved_rc;
    lua_pop(lua,2);             /* Discard the result and clean the stack. */
}