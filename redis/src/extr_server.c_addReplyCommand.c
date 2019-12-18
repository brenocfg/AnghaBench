#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct redisCommand {int flags; int /*<<< orphan*/  keystep; int /*<<< orphan*/  lastkey; int /*<<< orphan*/  firstkey; scalar_t__ getkeys_proc; int /*<<< orphan*/  arity; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ADMIN ; 
 int /*<<< orphan*/  CMD_ASKING ; 
 int /*<<< orphan*/  CMD_DENYOOM ; 
 int /*<<< orphan*/  CMD_FAST ; 
 int /*<<< orphan*/  CMD_LOADING ; 
 int CMD_MODULE ; 
 int CMD_MODULE_GETKEYS ; 
 int /*<<< orphan*/  CMD_NOSCRIPT ; 
 int /*<<< orphan*/  CMD_PUBSUB ; 
 int /*<<< orphan*/  CMD_RANDOM ; 
 int /*<<< orphan*/  CMD_READONLY ; 
 int /*<<< orphan*/  CMD_SKIP_MONITOR ; 
 int /*<<< orphan*/  CMD_SKIP_SLOWLOG ; 
 int /*<<< orphan*/  CMD_SORT_FOR_SCRIPT ; 
 int /*<<< orphan*/  CMD_STALE ; 
 int /*<<< orphan*/  CMD_WRITE ; 
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyCommandCategories (int /*<<< orphan*/ *,struct redisCommand*) ; 
 scalar_t__ addReplyCommandFlag (int /*<<< orphan*/ *,struct redisCommand*,int /*<<< orphan*/ ,char*) ; 
 void* addReplyDeferredLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyStatus (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setDeferredSetLen (int /*<<< orphan*/ *,void*,int) ; 

void addReplyCommand(client *c, struct redisCommand *cmd) {
    if (!cmd) {
        addReplyNull(c);
    } else {
        /* We are adding: command name, arg count, flags, first, last, offset, categories */
        addReplyArrayLen(c, 7);
        addReplyBulkCString(c, cmd->name);
        addReplyLongLong(c, cmd->arity);

        int flagcount = 0;
        void *flaglen = addReplyDeferredLen(c);
        flagcount += addReplyCommandFlag(c,cmd,CMD_WRITE, "write");
        flagcount += addReplyCommandFlag(c,cmd,CMD_READONLY, "readonly");
        flagcount += addReplyCommandFlag(c,cmd,CMD_DENYOOM, "denyoom");
        flagcount += addReplyCommandFlag(c,cmd,CMD_ADMIN, "admin");
        flagcount += addReplyCommandFlag(c,cmd,CMD_PUBSUB, "pubsub");
        flagcount += addReplyCommandFlag(c,cmd,CMD_NOSCRIPT, "noscript");
        flagcount += addReplyCommandFlag(c,cmd,CMD_RANDOM, "random");
        flagcount += addReplyCommandFlag(c,cmd,CMD_SORT_FOR_SCRIPT,"sort_for_script");
        flagcount += addReplyCommandFlag(c,cmd,CMD_LOADING, "loading");
        flagcount += addReplyCommandFlag(c,cmd,CMD_STALE, "stale");
        flagcount += addReplyCommandFlag(c,cmd,CMD_SKIP_MONITOR, "skip_monitor");
        flagcount += addReplyCommandFlag(c,cmd,CMD_SKIP_SLOWLOG, "skip_slowlog");
        flagcount += addReplyCommandFlag(c,cmd,CMD_ASKING, "asking");
        flagcount += addReplyCommandFlag(c,cmd,CMD_FAST, "fast");
        if ((cmd->getkeys_proc && !(cmd->flags & CMD_MODULE)) ||
            cmd->flags & CMD_MODULE_GETKEYS)
        {
            addReplyStatus(c, "movablekeys");
            flagcount += 1;
        }
        setDeferredSetLen(c, flaglen, flagcount);

        addReplyLongLong(c, cmd->firstkey);
        addReplyLongLong(c, cmd->lastkey);
        addReplyLongLong(c, cmd->keystep);

        addReplyCommandCategories(c,cmd);
    }
}