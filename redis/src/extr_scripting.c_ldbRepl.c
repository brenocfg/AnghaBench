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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int step; int currentline; int /*<<< orphan*/  cbuf; scalar_t__ bpcount; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int connRead (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ ldb ; 
 int /*<<< orphan*/  ldbBreak (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldbEval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldbList (int,int) ; 
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbMaxlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldbPrint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbPrintAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldbRedis (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ldbReplParseCommand (int*) ; 
 int /*<<< orphan*/  ldbSendLogs () ; 
 int /*<<< orphan*/  ldbTrace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfreesplitres (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

int ldbRepl(lua_State *lua) {
    sds *argv;
    int argc;

    /* We continue processing commands until a command that should return
     * to the Lua interpreter is found. */
    while(1) {
        while((argv = ldbReplParseCommand(&argc)) == NULL) {
            char buf[1024];
            int nread = connRead(ldb.conn,buf,sizeof(buf));
            if (nread <= 0) {
                /* Make sure the script runs without user input since the
                 * client is no longer connected. */
                ldb.step = 0;
                ldb.bpcount = 0;
                return C_ERR;
            }
            ldb.cbuf = sdscatlen(ldb.cbuf,buf,nread);
        }

        /* Flush the old buffer. */
        sdsfree(ldb.cbuf);
        ldb.cbuf = sdsempty();

        /* Execute the command. */
        if (!strcasecmp(argv[0],"h") || !strcasecmp(argv[0],"help")) {
ldbLog(sdsnew("Redis Lua debugger help:"));
ldbLog(sdsnew("[h]elp               Show this help."));
ldbLog(sdsnew("[s]tep               Run current line and stop again."));
ldbLog(sdsnew("[n]ext               Alias for step."));
ldbLog(sdsnew("[c]continue          Run till next breakpoint."));
ldbLog(sdsnew("[l]list              List source code around current line."));
ldbLog(sdsnew("[l]list [line]       List source code around [line]."));
ldbLog(sdsnew("                     line = 0 means: current position."));
ldbLog(sdsnew("[l]list [line] [ctx] In this form [ctx] specifies how many lines"));
ldbLog(sdsnew("                     to show before/after [line]."));
ldbLog(sdsnew("[w]hole              List all source code. Alias for 'list 1 1000000'."));
ldbLog(sdsnew("[p]rint              Show all the local variables."));
ldbLog(sdsnew("[p]rint <var>        Show the value of the specified variable."));
ldbLog(sdsnew("                     Can also show global vars KEYS and ARGV."));
ldbLog(sdsnew("[b]reak              Show all breakpoints."));
ldbLog(sdsnew("[b]reak <line>       Add a breakpoint to the specified line."));
ldbLog(sdsnew("[b]reak -<line>      Remove breakpoint from the specified line."));
ldbLog(sdsnew("[b]reak 0            Remove all breakpoints."));
ldbLog(sdsnew("[t]race              Show a backtrace."));
ldbLog(sdsnew("[e]eval <code>       Execute some Lua code (in a different callframe)."));
ldbLog(sdsnew("[r]edis <cmd>        Execute a Redis command."));
ldbLog(sdsnew("[m]axlen [len]       Trim logged Redis replies and Lua var dumps to len."));
ldbLog(sdsnew("                     Specifying zero as <len> means unlimited."));
ldbLog(sdsnew("[a]bort              Stop the execution of the script. In sync"));
ldbLog(sdsnew("                     mode dataset changes will be retained."));
ldbLog(sdsnew(""));
ldbLog(sdsnew("Debugger functions you can call from Lua scripts:"));
ldbLog(sdsnew("redis.debug()        Produce logs in the debugger console."));
ldbLog(sdsnew("redis.breakpoint()   Stop execution like if there was a breakpoing."));
ldbLog(sdsnew("                     in the next line of code."));
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step") ||
                   !strcasecmp(argv[0],"n") || !strcasecmp(argv[0],"next")) {
            ldb.step = 1;
            break;
        } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
            break;
        } else if (!strcasecmp(argv[0],"t") || !strcasecmp(argv[0],"trace")) {
            ldbTrace(lua);
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"m") || !strcasecmp(argv[0],"maxlen")) {
            ldbMaxlen(argv,argc);
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"b") || !strcasecmp(argv[0],"break")) {
            ldbBreak(argv,argc);
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"e") || !strcasecmp(argv[0],"eval")) {
            ldbEval(lua,argv,argc);
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"a") || !strcasecmp(argv[0],"abort")) {
            lua_pushstring(lua, "script aborted for user request");
            lua_error(lua);
        } else if (argc > 1 &&
                   (!strcasecmp(argv[0],"r") || !strcasecmp(argv[0],"redis"))) {
            ldbRedis(lua,argv,argc);
            ldbSendLogs();
        } else if ((!strcasecmp(argv[0],"p") || !strcasecmp(argv[0],"print"))) {
            if (argc == 2)
                ldbPrint(lua,argv[1]);
            else
                ldbPrintAll(lua);
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"l") || !strcasecmp(argv[0],"list")){
            int around = ldb.currentline, ctx = 5;
            if (argc > 1) {
                int num = atoi(argv[1]);
                if (num > 0) around = num;
            }
            if (argc > 2) ctx = atoi(argv[2]);
            ldbList(around,ctx);
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"w") || !strcasecmp(argv[0],"whole")){
            ldbList(1,1000000);
            ldbSendLogs();
        } else {
            ldbLog(sdsnew("<error> Unknown Redis Lua debugger command or "
                          "wrong number of arguments."));
            ldbSendLogs();
        }

        /* Free the command vector. */
        sdsfreesplitres(argv,argc);
    }

    /* Free the current command argv if we break inside the while loop. */
    sdsfreesplitres(argv,argc);
    return C_OK;
}