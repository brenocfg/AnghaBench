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
typedef  int /*<<< orphan*/  user ;
typedef  int uint64_t ;
struct redisCommand {int flags; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_2__ {int /*<<< orphan*/  orig_commands; } ;

/* Variables and functions */
 int ACLGetCommandCategoryFlagByName (char const*) ; 
 int /*<<< orphan*/  ACLResetSubcommandsForCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACLSetUserCommandBit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int CMD_MODULE ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 struct redisCommand* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

int ACLSetUserCommandBitsForCategory(user *u, const char *category, int value) {
    uint64_t cflag = ACLGetCommandCategoryFlagByName(category);
    if (!cflag) return C_ERR;
    dictIterator *di = dictGetIterator(server.orig_commands);
    dictEntry *de;
    while ((de = dictNext(di)) != NULL) {
        struct redisCommand *cmd = dictGetVal(de);
        if (cmd->flags & CMD_MODULE) continue; /* Ignore modules commands. */
        if (cmd->flags & cflag) {
            ACLSetUserCommandBit(u,cmd->id,value);
            ACLResetSubcommandsForCommand(u,cmd->id);
        }
    }
    dictReleaseIterator(di);
    return C_OK;
}