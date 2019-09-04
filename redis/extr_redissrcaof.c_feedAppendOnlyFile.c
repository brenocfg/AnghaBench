#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {scalar_t__ proc; } ;
typedef  int /*<<< orphan*/  seldb ;
typedef  scalar_t__ sds ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_10__ {int aof_selected_db; scalar_t__ aof_state; int aof_child_pid; int /*<<< orphan*/  aof_buf; struct redisCommand* pexpireCommand; struct redisCommand* expireCommand; } ;

/* Variables and functions */
 scalar_t__ AOF_ON ; 
 int /*<<< orphan*/  aofRewriteBufferAppend (unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ catAppendOnlyExpireAtCommand (scalar_t__,struct redisCommand*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ catAppendOnlyGenericCommand (scalar_t__,int,TYPE_1__**) ; 
 TYPE_1__* createStringObject (char*,int) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 scalar_t__ expireCommand ; 
 scalar_t__ expireatCommand ; 
 scalar_t__ pexpireCommand ; 
 scalar_t__ psetexCommand ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sdscatprintf (scalar_t__,char*,unsigned long,char*) ; 
 scalar_t__ sdsempty () ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 scalar_t__ setCommand ; 
 scalar_t__ setexCommand ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
    sds buf = sdsempty();
    robj *tmpargv[3];

    /* The DB this command was targeting is not the same as the last command
     * we appended. To issue a SELECT command is needed. */
    if (dictid != server.aof_selected_db) {
        char seldb[64];

        snprintf(seldb,sizeof(seldb),"%d",dictid);
        buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%lu\r\n%s\r\n",
            (unsigned long)strlen(seldb),seldb);
        server.aof_selected_db = dictid;
    }

    if (cmd->proc == expireCommand || cmd->proc == pexpireCommand ||
        cmd->proc == expireatCommand) {
        /* Translate EXPIRE/PEXPIRE/EXPIREAT into PEXPIREAT */
        buf = catAppendOnlyExpireAtCommand(buf,cmd,argv[1],argv[2]);
    } else if (cmd->proc == setexCommand || cmd->proc == psetexCommand) {
        /* Translate SETEX/PSETEX to SET and PEXPIREAT */
        tmpargv[0] = createStringObject("SET",3);
        tmpargv[1] = argv[1];
        tmpargv[2] = argv[3];
        buf = catAppendOnlyGenericCommand(buf,3,tmpargv);
        decrRefCount(tmpargv[0]);
        buf = catAppendOnlyExpireAtCommand(buf,cmd,argv[1],argv[2]);
    } else if (cmd->proc == setCommand && argc > 3) {
        int i;
        robj *exarg = NULL, *pxarg = NULL;
        /* Translate SET [EX seconds][PX milliseconds] to SET and PEXPIREAT */
        buf = catAppendOnlyGenericCommand(buf,3,argv);
        for (i = 3; i < argc; i ++) {
            if (!strcasecmp(argv[i]->ptr, "ex")) exarg = argv[i+1];
            if (!strcasecmp(argv[i]->ptr, "px")) pxarg = argv[i+1];
        }
        serverAssert(!(exarg && pxarg));
        if (exarg)
            buf = catAppendOnlyExpireAtCommand(buf,server.expireCommand,argv[1],
                                               exarg);
        if (pxarg)
            buf = catAppendOnlyExpireAtCommand(buf,server.pexpireCommand,argv[1],
                                               pxarg);
    } else {
        /* All the other commands don't need translation or need the
         * same translation already operated in the command vector
         * for the replication itself. */
        buf = catAppendOnlyGenericCommand(buf,argc,argv);
    }

    /* Append to the AOF buffer. This will be flushed on disk just before
     * of re-entering the event loop, so before the client will get a
     * positive reply about the operation performed. */
    if (server.aof_state == AOF_ON)
        server.aof_buf = sdscatlen(server.aof_buf,buf,sdslen(buf));

    /* If a background append only file rewriting is in progress we want to
     * accumulate the differences between the child DB and the current one
     * in a buffer, so that when the child process will do its work we
     * can append the differences to the new append only file. */
    if (server.aof_child_pid != -1)
        aofRewriteBufferAppend((unsigned char*)buf,sdslen(buf));

    sdsfree(buf);
}