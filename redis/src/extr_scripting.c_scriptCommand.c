#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_20__ {int argc; int /*<<< orphan*/  flags; TYPE_7__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_23__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_22__ {int lua_kill; scalar_t__ lua_write_dirty; TYPE_1__* lua_caller; int /*<<< orphan*/  lua; int /*<<< orphan*/  lua_scripts; int /*<<< orphan*/  dirty; } ;
struct TYPE_21__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  czero; int /*<<< orphan*/  cone; } ;
struct TYPE_19__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_LUA_DEBUG_SYNC ; 
 int CLIENT_MASTER ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_2__*,char const**) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySubcommandSyntaxError (TYPE_2__*) ; 
 scalar_t__ clientHasPendingReplies (TYPE_2__*) ; 
 scalar_t__ dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forceCommandPropagation (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ldbDisable (TYPE_2__*) ; 
 int /*<<< orphan*/  ldbEnable (TYPE_2__*) ; 
 int /*<<< orphan*/ * luaCreateFunction (TYPE_2__*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  replicationScriptCacheFlush () ; 
 int /*<<< orphan*/  scriptingReset () ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_4__ server ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

void scriptCommand(client *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"help")) {
        const char *help[] = {
"DEBUG (yes|sync|no) -- Set the debug mode for subsequent scripts executed.",
"EXISTS <sha1> [<sha1> ...] -- Return information about the existence of the scripts in the script cache.",
"FLUSH -- Flush the Lua scripts cache. Very dangerous on replicas.",
"KILL -- Kill the currently executing Lua script.",
"LOAD <script> -- Load a script into the scripts cache, without executing it.",
NULL
        };
        addReplyHelp(c, help);
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
        scriptingReset();
        addReply(c,shared.ok);
        replicationScriptCacheFlush();
        server.dirty++; /* Propagating this command is a good idea. */
    } else if (c->argc >= 2 && !strcasecmp(c->argv[1]->ptr,"exists")) {
        int j;

        addReplyArrayLen(c, c->argc-2);
        for (j = 2; j < c->argc; j++) {
            if (dictFind(server.lua_scripts,c->argv[j]->ptr))
                addReply(c,shared.cone);
            else
                addReply(c,shared.czero);
        }
    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"load")) {
        sds sha = luaCreateFunction(c,server.lua,c->argv[2]);
        if (sha == NULL) return; /* The error was sent by luaCreateFunction(). */
        addReplyBulkCBuffer(c,sha,40);
        forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
        if (server.lua_caller == NULL) {
            addReplySds(c,sdsnew("-NOTBUSY No scripts in execution right now.\r\n"));
        } else if (server.lua_caller->flags & CLIENT_MASTER) {
            addReplySds(c,sdsnew("-UNKILLABLE The busy script was sent by a master instance in the context of replication and cannot be killed.\r\n"));
        } else if (server.lua_write_dirty) {
            addReplySds(c,sdsnew("-UNKILLABLE Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in a hard way using the SHUTDOWN NOSAVE command.\r\n"));
        } else {
            server.lua_kill = 1;
            addReply(c,shared.ok);
        }
    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"debug")) {
        if (clientHasPendingReplies(c)) {
            addReplyError(c,"SCRIPT DEBUG must be called outside a pipeline");
            return;
        }
        if (!strcasecmp(c->argv[2]->ptr,"no")) {
            ldbDisable(c);
            addReply(c,shared.ok);
        } else if (!strcasecmp(c->argv[2]->ptr,"yes")) {
            ldbEnable(c);
            addReply(c,shared.ok);
        } else if (!strcasecmp(c->argv[2]->ptr,"sync")) {
            ldbEnable(c);
            addReply(c,shared.ok);
            c->flags |= CLIENT_LUA_DEBUG_SYNC;
        } else {
            addReplyError(c,"Use SCRIPT DEBUG yes/sync/no");
            return;
        }
    } else {
        addReplySubcommandSyntaxError(c);
    }
}