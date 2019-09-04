#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {scalar_t__ firstkey; int arity; int /*<<< orphan*/ * getkeys_proc; } ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_13__ {int argc; TYPE_3__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_15__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_14__ {int /*<<< orphan*/  commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyArrayLen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  addReplyCommand (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,int) ; 
 int /*<<< orphan*/  addReplySubcommandSyntaxError (TYPE_1__*) ; 
 int /*<<< orphan*/  dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getKeysFreeResult (int*) ; 
 int* getKeysFromCommand (struct redisCommand*,TYPE_3__**,int,int*) ; 
 struct redisCommand* lookupCommand (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

void commandCommand(client *c) {
    dictIterator *di;
    dictEntry *de;

    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"help")) {
        const char *help[] = {
"(no subcommand) -- Return details about all Redis commands.",
"COUNT -- Return the total number of commands in this Redis server.",
"GETKEYS <full-command> -- Return the keys from a full Redis command.",
"INFO [command-name ...] -- Return details about multiple Redis commands.",
NULL
        };
        addReplyHelp(c, help);
    } else if (c->argc == 1) {
        addReplyArrayLen(c, dictSize(server.commands));
        di = dictGetIterator(server.commands);
        while ((de = dictNext(di)) != NULL) {
            addReplyCommand(c, dictGetVal(de));
        }
        dictReleaseIterator(di);
    } else if (!strcasecmp(c->argv[1]->ptr, "info")) {
        int i;
        addReplyArrayLen(c, c->argc-2);
        for (i = 2; i < c->argc; i++) {
            addReplyCommand(c, dictFetchValue(server.commands, c->argv[i]->ptr));
        }
    } else if (!strcasecmp(c->argv[1]->ptr, "count") && c->argc == 2) {
        addReplyLongLong(c, dictSize(server.commands));
    } else if (!strcasecmp(c->argv[1]->ptr,"getkeys") && c->argc >= 3) {
        struct redisCommand *cmd = lookupCommand(c->argv[2]->ptr);
        int *keys, numkeys, j;

        if (!cmd) {
            addReplyError(c,"Invalid command specified");
            return;
        } else if (cmd->getkeys_proc == NULL && cmd->firstkey == 0) {
            addReplyError(c,"The command has no key arguments");
            return;
        } else if ((cmd->arity > 0 && cmd->arity != c->argc-2) ||
                   ((c->argc-2) < -cmd->arity))
        {
            addReplyError(c,"Invalid number of arguments specified for command");
            return;
        }

        keys = getKeysFromCommand(cmd,c->argv+2,c->argc-2,&numkeys);
        if (!keys) {
            addReplyError(c,"Invalid arguments specified for command");
        } else {
            addReplyArrayLen(c,numkeys);
            for (j = 0; j < numkeys; j++) addReplyBulk(c,c->argv[keys[j]+2]);
            getKeysFreeResult(keys);
        }
    } else {
        addReplySubcommandSyntaxError(c);
    }
}