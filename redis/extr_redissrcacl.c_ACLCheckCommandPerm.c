#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int /*<<< orphan*/  patterns; int /*<<< orphan*/ *** allowed_subcommands; } ;
typedef  TYPE_1__ user ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_8__ {int argc; TYPE_4__** argv; TYPE_3__* cmd; TYPE_1__* user; } ;
typedef  TYPE_2__ client ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_9__ {size_t id; scalar_t__ proc; scalar_t__ firstkey; scalar_t__ getkeys_proc; } ;

/* Variables and functions */
 scalar_t__ ACLGetUserCommandBit (TYPE_1__*,size_t) ; 
 int ACL_DENIED_CMD ; 
 int ACL_DENIED_KEY ; 
 int ACL_OK ; 
 int USER_FLAG_ALLCOMMANDS ; 
 int USER_FLAG_ALLKEYS ; 
 scalar_t__ authCommand ; 
 int /*<<< orphan*/  getKeysFreeResult (int*) ; 
 int* getKeysFromCommand (TYPE_3__*,TYPE_4__**,int,int*) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stringmatchlen (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

int ACLCheckCommandPerm(client *c) {
    user *u = c->user;
    uint64_t id = c->cmd->id;

    /* If there is no associated user, the connection can run anything. */
    if (u == NULL) return ACL_OK;

    /* Check if the user can execute this command. */
    if (!(u->flags & USER_FLAG_ALLCOMMANDS) &&
        c->cmd->proc != authCommand)
    {
        /* If the bit is not set we have to check further, in case the
         * command is allowed just with that specific subcommand. */
        if (ACLGetUserCommandBit(u,id) == 0) {
            /* Check if the subcommand matches. */
            if (c->argc < 2 ||
                u->allowed_subcommands == NULL ||
                u->allowed_subcommands[id] == NULL)
            {
                return ACL_DENIED_CMD;
            }

            long subid = 0;
            while (1) {
                if (u->allowed_subcommands[id][subid] == NULL)
                    return ACL_DENIED_CMD;
                if (!strcasecmp(c->argv[1]->ptr,
                                u->allowed_subcommands[id][subid]))
                    break; /* Subcommand match found. Stop here. */
                subid++;
            }
        }
    }

    /* Check if the user can execute commands explicitly touching the keys
     * mentioned in the command arguments. */
    if (!(c->user->flags & USER_FLAG_ALLKEYS) &&
        (c->cmd->getkeys_proc || c->cmd->firstkey))
    {
        int numkeys;
        int *keyidx = getKeysFromCommand(c->cmd,c->argv,c->argc,&numkeys);
        for (int j = 0; j < numkeys; j++) {
            listIter li;
            listNode *ln;
            listRewind(u->patterns,&li);

            /* Test this key against every pattern. */
            int match = 0;
            while((ln = listNext(&li))) {
                sds pattern = listNodeValue(ln);
                size_t plen = sdslen(pattern);
                int idx = keyidx[j];
                if (stringmatchlen(pattern,plen,c->argv[idx]->ptr,
                                   sdslen(c->argv[idx]->ptr),0))
                {
                    match = 1;
                    break;
                }
            }
            if (!match) {
                getKeysFreeResult(keyidx);
                return ACL_DENIED_KEY;
            }
        }
        getKeysFreeResult(keyidx);
    }

    /* If we survived all the above checks, the user can execute the
     * command. */
    return ACL_OK;
}