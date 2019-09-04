#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mstime_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {scalar_t__ event; int /*<<< orphan*/  short_src; int /*<<< orphan*/  currentline; } ;
typedef  TYPE_1__ lua_Debug ;
struct TYPE_9__ {int step; int /*<<< orphan*/  currentline; scalar_t__ luabp; } ;
struct TYPE_8__ {scalar_t__ lua_time_start; int lua_time_limit; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ LUA_HOOKCOUNT ; 
 TYPE_6__ ldb ; 
 scalar_t__ ldbIsBreakpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbLogSourceLine (int /*<<< orphan*/ ) ; 
 scalar_t__ ldbRepl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldbSendLogs () ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_getstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    ldb.currentline = ar->currentline;

    int bp = ldbIsBreakpoint(ldb.currentline) || ldb.luabp;
    int timeout = 0;

    /* Events outside our script are not interesting. */
    if(strstr(ar->short_src,"user_script") == NULL) return;

    /* Check if a timeout occurred. */
    if (ar->event == LUA_HOOKCOUNT && ldb.step == 0 && bp == 0) {
        mstime_t elapsed = mstime() - server.lua_time_start;
        mstime_t timelimit = server.lua_time_limit ?
                             server.lua_time_limit : 5000;
        if (elapsed >= timelimit) {
            timeout = 1;
            ldb.step = 1;
        } else {
            return; /* No timeout, ignore the COUNT event. */
        }
    }

    if (ldb.step || bp) {
        char *reason = "step over";
        if (bp) reason = ldb.luabp ? "redis.breakpoint() called" :
                                     "break point";
        else if (timeout) reason = "timeout reached, infinite loop?";
        ldb.step = 0;
        ldb.luabp = 0;
        ldbLog(sdscatprintf(sdsempty(),
            "* Stopped at %d, stop reason = %s",
            ldb.currentline, reason));
        ldbLogSourceLine(ldb.currentline);
        ldbSendLogs();
        if (ldbRepl(lua) == C_ERR && timeout) {
            /* If the client closed the connection and we have a timeout
             * connection, let's kill the script otherwise the process
             * will remain blocked indefinitely. */
            lua_pushstring(lua, "timeout during Lua debugging with client closing connection");
            lua_error(lua);
        }
        server.lua_time_start = mstime();
    }
}