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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lua; TYPE_2__* lua_client; scalar_t__ lua_scripts_mem; int /*<<< orphan*/  lua_scripts; scalar_t__ lua_timedout; int /*<<< orphan*/ * lua_cur_script; int /*<<< orphan*/ * lua_caller; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_LUA ; 
 int LL_DEBUG ; 
 int LL_NOTICE ; 
 int LL_VERBOSE ; 
 int LL_WARNING ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_NONE ; 
 int PROPAGATE_REPL ; 
 TYPE_2__* createClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldbInit () ; 
 int /*<<< orphan*/  luaL_loadbuffer (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  luaLoadLibraries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaLogCommand ; 
 int /*<<< orphan*/  luaRedisBreakpointCommand ; 
 int /*<<< orphan*/  luaRedisCallCommand ; 
 int /*<<< orphan*/  luaRedisDebugCommand ; 
 int /*<<< orphan*/  luaRedisErrorReplyCommand ; 
 int /*<<< orphan*/  luaRedisPCallCommand ; 
 int /*<<< orphan*/  luaRedisReplicateCommandsCommand ; 
 int /*<<< orphan*/  luaRedisSetReplCommand ; 
 int /*<<< orphan*/  luaRedisSha1hexCommand ; 
 int /*<<< orphan*/  luaRedisStatusReplyCommand ; 
 int /*<<< orphan*/  luaRemoveUnsupportedFunctions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaSetResp ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_open () ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  redis_math_random ; 
 int /*<<< orphan*/  redis_math_randomseed ; 
 int /*<<< orphan*/  scriptingEnableGlobalsProtection (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  shaScriptObjectDictType ; 
 int /*<<< orphan*/  strlen (char*) ; 

void scriptingInit(int setup) {
    lua_State *lua = lua_open();

    if (setup) {
        server.lua_client = NULL;
        server.lua_caller = NULL;
        server.lua_cur_script = NULL;
        server.lua_timedout = 0;
        ldbInit();
    }

    luaLoadLibraries(lua);
    luaRemoveUnsupportedFunctions(lua);

    /* Initialize a dictionary we use to map SHAs to scripts.
     * This is useful for replication, as we need to replicate EVALSHA
     * as EVAL, so we need to remember the associated script. */
    server.lua_scripts = dictCreate(&shaScriptObjectDictType,NULL);
    server.lua_scripts_mem = 0;

    /* Register the redis commands table and fields */
    lua_newtable(lua);

    /* redis.call */
    lua_pushstring(lua,"call");
    lua_pushcfunction(lua,luaRedisCallCommand);
    lua_settable(lua,-3);

    /* redis.pcall */
    lua_pushstring(lua,"pcall");
    lua_pushcfunction(lua,luaRedisPCallCommand);
    lua_settable(lua,-3);

    /* redis.log and log levels. */
    lua_pushstring(lua,"log");
    lua_pushcfunction(lua,luaLogCommand);
    lua_settable(lua,-3);

    /* redis.setresp */
    lua_pushstring(lua,"setresp");
    lua_pushcfunction(lua,luaSetResp);
    lua_settable(lua,-3);

    lua_pushstring(lua,"LOG_DEBUG");
    lua_pushnumber(lua,LL_DEBUG);
    lua_settable(lua,-3);

    lua_pushstring(lua,"LOG_VERBOSE");
    lua_pushnumber(lua,LL_VERBOSE);
    lua_settable(lua,-3);

    lua_pushstring(lua,"LOG_NOTICE");
    lua_pushnumber(lua,LL_NOTICE);
    lua_settable(lua,-3);

    lua_pushstring(lua,"LOG_WARNING");
    lua_pushnumber(lua,LL_WARNING);
    lua_settable(lua,-3);

    /* redis.sha1hex */
    lua_pushstring(lua, "sha1hex");
    lua_pushcfunction(lua, luaRedisSha1hexCommand);
    lua_settable(lua, -3);

    /* redis.error_reply and redis.status_reply */
    lua_pushstring(lua, "error_reply");
    lua_pushcfunction(lua, luaRedisErrorReplyCommand);
    lua_settable(lua, -3);
    lua_pushstring(lua, "status_reply");
    lua_pushcfunction(lua, luaRedisStatusReplyCommand);
    lua_settable(lua, -3);

    /* redis.replicate_commands */
    lua_pushstring(lua, "replicate_commands");
    lua_pushcfunction(lua, luaRedisReplicateCommandsCommand);
    lua_settable(lua, -3);

    /* redis.set_repl and associated flags. */
    lua_pushstring(lua,"set_repl");
    lua_pushcfunction(lua,luaRedisSetReplCommand);
    lua_settable(lua,-3);

    lua_pushstring(lua,"REPL_NONE");
    lua_pushnumber(lua,PROPAGATE_NONE);
    lua_settable(lua,-3);

    lua_pushstring(lua,"REPL_AOF");
    lua_pushnumber(lua,PROPAGATE_AOF);
    lua_settable(lua,-3);

    lua_pushstring(lua,"REPL_SLAVE");
    lua_pushnumber(lua,PROPAGATE_REPL);
    lua_settable(lua,-3);

    lua_pushstring(lua,"REPL_REPLICA");
    lua_pushnumber(lua,PROPAGATE_REPL);
    lua_settable(lua,-3);

    lua_pushstring(lua,"REPL_ALL");
    lua_pushnumber(lua,PROPAGATE_AOF|PROPAGATE_REPL);
    lua_settable(lua,-3);

    /* redis.breakpoint */
    lua_pushstring(lua,"breakpoint");
    lua_pushcfunction(lua,luaRedisBreakpointCommand);
    lua_settable(lua,-3);

    /* redis.debug */
    lua_pushstring(lua,"debug");
    lua_pushcfunction(lua,luaRedisDebugCommand);
    lua_settable(lua,-3);

    /* Finally set the table as 'redis' global var. */
    lua_setglobal(lua,"redis");

    /* Replace math.random and math.randomseed with our implementations. */
    lua_getglobal(lua,"math");

    lua_pushstring(lua,"random");
    lua_pushcfunction(lua,redis_math_random);
    lua_settable(lua,-3);

    lua_pushstring(lua,"randomseed");
    lua_pushcfunction(lua,redis_math_randomseed);
    lua_settable(lua,-3);

    lua_setglobal(lua,"math");

    /* Add a helper function that we use to sort the multi bulk output of non
     * deterministic commands, when containing 'false' elements. */
    {
        char *compare_func =    "function __redis__compare_helper(a,b)\n"
                                "  if a == false then a = '' end\n"
                                "  if b == false then b = '' end\n"
                                "  return a<b\n"
                                "end\n";
        luaL_loadbuffer(lua,compare_func,strlen(compare_func),"@cmp_func_def");
        lua_pcall(lua,0,0,0);
    }

    /* Add a helper function we use for pcall error reporting.
     * Note that when the error is in the C function we want to report the
     * information about the caller, that's what makes sense from the point
     * of view of the user debugging a script. */
    {
        char *errh_func =       "local dbg = debug\n"
                                "function __redis__err__handler(err)\n"
                                "  local i = dbg.getinfo(2,'nSl')\n"
                                "  if i and i.what == 'C' then\n"
                                "    i = dbg.getinfo(3,'nSl')\n"
                                "  end\n"
                                "  if i then\n"
                                "    return i.source .. ':' .. i.currentline .. ': ' .. err\n"
                                "  else\n"
                                "    return err\n"
                                "  end\n"
                                "end\n";
        luaL_loadbuffer(lua,errh_func,strlen(errh_func),"@err_handler_def");
        lua_pcall(lua,0,0,0);
    }

    /* Create the (non connected) client that we use to execute Redis commands
     * inside the Lua interpreter.
     * Note: there is no need to create it again when this function is called
     * by scriptingReset(). */
    if (server.lua_client == NULL) {
        server.lua_client = createClient(NULL);
        server.lua_client->flags |= CLIENT_LUA;
    }

    /* Lua beginners often don't use "local", this is likely to introduce
     * subtle bugs in their code. To prevent problems we protect accesses
     * to global variables. */
    scriptingEnableGlobalsProtection(lua);

    server.lua = lua;
}