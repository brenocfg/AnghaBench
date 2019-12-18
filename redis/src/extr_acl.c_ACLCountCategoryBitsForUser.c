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
 scalar_t__ ACLGetUserCommandBit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 struct redisCommand* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

int ACLCountCategoryBitsForUser(user *u, unsigned long *on, unsigned long *off,
                                const char *category)
{
    uint64_t cflag = ACLGetCommandCategoryFlagByName(category);
    if (!cflag) return C_ERR;

    *on = *off = 0;
    dictIterator *di = dictGetIterator(server.orig_commands);
    dictEntry *de;
    while ((de = dictNext(di)) != NULL) {
        struct redisCommand *cmd = dictGetVal(de);
        if (cmd->flags & cflag) {
            if (ACLGetUserCommandBit(u,cmd->id))
                (*on)++;
            else
                (*off)++;
        }
    }
    dictReleaseIterator(di);
    return C_OK;
}