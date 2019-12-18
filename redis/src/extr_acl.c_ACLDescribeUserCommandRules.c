#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char*** allowed_subcommands; int /*<<< orphan*/  allowed_commands; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ user ;
struct redisCommand {size_t id; char* name; } ;
typedef  char* sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_12__ {scalar_t__ flag; char* name; } ;
struct TYPE_11__ {int /*<<< orphan*/  orig_commands; } ;

/* Variables and functions */
 TYPE_9__* ACLCommandCategories ; 
 int /*<<< orphan*/  ACLCountCategoryBitsForUser (TYPE_1__*,unsigned long*,unsigned long*,char*) ; 
 int ACLGetUserCommandBit (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  ACLSetUser (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ACLSetUserCommandBit (TYPE_1__*,size_t,int) ; 
 scalar_t__ ACLUserCanExecuteFutureCommands (TYPE_1__*) ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 struct redisCommand* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatlen (char*,char*,int) ; 
 char* sdscatsds (char*,char*) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 char* sdsnewlen (char*,int) ; 
 int /*<<< orphan*/  sdsrange (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

sds ACLDescribeUserCommandRules(user *u) {
    sds rules = sdsempty();
    int additive;   /* If true we start from -@all and add, otherwise if
                       false we start from +@all and remove. */

    /* This code is based on a trick: as we generate the rules, we apply
     * them to a fake user, so that as we go we still know what are the
     * bit differences we should try to address by emitting more rules. */
    user fu = {0};
    user *fakeuser = &fu;

    /* Here we want to understand if we should start with +@all and remove
     * the commands corresponding to the bits that are not set in the user
     * commands bitmap, or the contrary. Note that semantically the two are
     * different. For instance starting with +@all and subtracting, the user
     * will be able to execute future commands, while -@all and adding will just
     * allow the user the run the selected commands and/or categories.
     * How do we test for that? We use the trick of a reserved command ID bit
     * that is set only by +@all (and its alias "allcommands"). */
    if (ACLUserCanExecuteFutureCommands(u)) {
        additive = 0;
        rules = sdscat(rules,"+@all ");
        ACLSetUser(fakeuser,"+@all",-1);
    } else {
        additive = 1;
        rules = sdscat(rules,"-@all ");
        ACLSetUser(fakeuser,"-@all",-1);
    }

    /* Try to add or subtract each category one after the other. Often a
     * single category will not perfectly match the set of commands into
     * it, so at the end we do a final pass adding/removing the single commands
     * needed to make the bitmap exactly match. */
    for (int j = 0; ACLCommandCategories[j].flag != 0; j++) {
        unsigned long on, off;
        ACLCountCategoryBitsForUser(u,&on,&off,ACLCommandCategories[j].name);
        if ((additive && on > off) || (!additive && off > on)) {
            sds op = sdsnewlen(additive ? "+@" : "-@", 2);
            op = sdscat(op,ACLCommandCategories[j].name);
            ACLSetUser(fakeuser,op,-1);
            rules = sdscatsds(rules,op);
            rules = sdscatlen(rules," ",1);
            sdsfree(op);
        }
    }

    /* Fix the final ACLs with single commands differences. */
    dictIterator *di = dictGetIterator(server.orig_commands);
    dictEntry *de;
    while ((de = dictNext(di)) != NULL) {
        struct redisCommand *cmd = dictGetVal(de);
        int userbit = ACLGetUserCommandBit(u,cmd->id);
        int fakebit = ACLGetUserCommandBit(fakeuser,cmd->id);
        if (userbit != fakebit) {
            rules = sdscatlen(rules, userbit ? "+" : "-", 1);
            rules = sdscat(rules,cmd->name);
            rules = sdscatlen(rules," ",1);
            ACLSetUserCommandBit(fakeuser,cmd->id,userbit);
        }

        /* Emit the subcommands if there are any. */
        if (userbit == 0 && u->allowed_subcommands &&
            u->allowed_subcommands[cmd->id])
        {
            for (int j = 0; u->allowed_subcommands[cmd->id][j]; j++) {
                rules = sdscatlen(rules,"+",1);
                rules = sdscat(rules,cmd->name);
                rules = sdscatlen(rules,"|",1);
                rules = sdscatsds(rules,u->allowed_subcommands[cmd->id][j]);
                rules = sdscatlen(rules," ",1);
            }
        }
    }
    dictReleaseIterator(di);

    /* Trim the final useless space. */
    sdsrange(rules,0,-2);

    /* This is technically not needed, but we want to verify that now the
     * predicted bitmap is exactly the same as the user bitmap, and abort
     * otherwise, because aborting is better than a security risk in this
     * code path. */
    if (memcmp(fakeuser->allowed_commands,
                        u->allowed_commands,
                        sizeof(u->allowed_commands)) != 0)
    {
        serverLog(LL_WARNING,
            "CRITICAL ERROR: User ACLs don't match final bitmap: '%s'",
            rules);
        serverPanic("No bitmap match in ACLDescribeUserCommandRules()");
    }
    return rules;
}