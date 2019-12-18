#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_17__ {int /*<<< orphan*/ * key; TYPE_1__* db; } ;
typedef  TYPE_4__ readyList ;
struct TYPE_18__ {TYPE_6__* value; } ;
typedef  TYPE_5__ listNode ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_19__ {scalar_t__ btype; TYPE_3__* db; TYPE_2__* lastcmd; } ;
typedef  TYPE_6__ client ;
struct TYPE_20__ {struct redisCommand* zpopmaxCommand; struct redisCommand* zpopminCommand; } ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;
struct TYPE_15__ {scalar_t__ proc; } ;
struct TYPE_14__ {int /*<<< orphan*/  blocking_keys; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_ZSET ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int ZSET_MAX ; 
 int ZSET_MIN ; 
 scalar_t__ bzpopminCommand ; 
 int /*<<< orphan*/ * createStringObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genericZpopCommand (TYPE_6__*,int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* listFirst (int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  propagate (struct redisCommand*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unblockClient (TYPE_6__*) ; 
 unsigned long zsetLength (int /*<<< orphan*/ *) ; 

void serveClientsBlockedOnSortedSetKey(robj *o, readyList *rl) {
    /* We serve clients in the same order they blocked for
     * this key, from the first blocked to the last. */
    dictEntry *de = dictFind(rl->db->blocking_keys,rl->key);
    if (de) {
        list *clients = dictGetVal(de);
        int numclients = listLength(clients);
        unsigned long zcard = zsetLength(o);

        while(numclients-- && zcard) {
            listNode *clientnode = listFirst(clients);
            client *receiver = clientnode->value;

            if (receiver->btype != BLOCKED_ZSET) {
                /* Put at the tail, so that at the next call
                 * we'll not run into it again. */
                listDelNode(clients,clientnode);
                listAddNodeTail(clients,receiver);
                continue;
            }

            int where = (receiver->lastcmd &&
                         receiver->lastcmd->proc == bzpopminCommand)
                         ? ZSET_MIN : ZSET_MAX;
            unblockClient(receiver);
            genericZpopCommand(receiver,&rl->key,1,where,1,NULL);
            zcard--;

            /* Replicate the command. */
            robj *argv[2];
            struct redisCommand *cmd = where == ZSET_MIN ?
                                       server.zpopminCommand :
                                       server.zpopmaxCommand;
            argv[0] = createStringObject(cmd->name,strlen(cmd->name));
            argv[1] = rl->key;
            incrRefCount(rl->key);
            propagate(cmd,receiver->db->id,
                      argv,2,PROPAGATE_AOF|PROPAGATE_REPL);
            decrRefCount(argv[0]);
            decrRefCount(argv[1]);
        }
    }
}