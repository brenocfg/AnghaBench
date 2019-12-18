#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_16__ {TYPE_9__* db; int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ readyList ;
struct TYPE_17__ {TYPE_5__* value; } ;
typedef  TYPE_4__ listNode ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_14__ {int /*<<< orphan*/ * target; } ;
struct TYPE_18__ {scalar_t__ btype; TYPE_2__* lastcmd; TYPE_1__ bpop; } ;
typedef  TYPE_5__ client ;
struct TYPE_19__ {int /*<<< orphan*/  id; int /*<<< orphan*/  blocking_keys; } ;
struct TYPE_15__ {scalar_t__ proc; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_LIST ; 
 scalar_t__ C_ERR ; 
 int LIST_HEAD ; 
 int LIST_TAIL ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 scalar_t__ blpopCommand ; 
 int /*<<< orphan*/  dbDelete (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* listFirst (int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ *) ; 
 scalar_t__ listTypeLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listTypePop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  listTypePush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ serveClientBlockedOnList (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unblockClient (TYPE_5__*) ; 

void serveClientsBlockedOnListKey(robj *o, readyList *rl) {
    /* We serve clients in the same order they blocked for
     * this key, from the first blocked to the last. */
    dictEntry *de = dictFind(rl->db->blocking_keys,rl->key);
    if (de) {
        list *clients = dictGetVal(de);
        int numclients = listLength(clients);

        while(numclients--) {
            listNode *clientnode = listFirst(clients);
            client *receiver = clientnode->value;

            if (receiver->btype != BLOCKED_LIST) {
                /* Put at the tail, so that at the next call
                 * we'll not run into it again. */
                listDelNode(clients,clientnode);
                listAddNodeTail(clients,receiver);
                continue;
            }

            robj *dstkey = receiver->bpop.target;
            int where = (receiver->lastcmd &&
                         receiver->lastcmd->proc == blpopCommand) ?
                         LIST_HEAD : LIST_TAIL;
            robj *value = listTypePop(o,where);

            if (value) {
                /* Protect receiver->bpop.target, that will be
                 * freed by the next unblockClient()
                 * call. */
                if (dstkey) incrRefCount(dstkey);
                unblockClient(receiver);

                if (serveClientBlockedOnList(receiver,
                    rl->key,dstkey,rl->db,value,
                    where) == C_ERR)
                {
                    /* If we failed serving the client we need
                     * to also undo the POP operation. */
                    listTypePush(o,value,where);
                }

                if (dstkey) decrRefCount(dstkey);
                decrRefCount(value);
            } else {
                break;
            }
        }
    }

    if (listTypeLength(o) == 0) {
        dbDelete(rl->db,rl->key);
        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",rl->key,rl->db->id);
    }
    /* We don't call signalModifiedKey() as it was already called
     * when an element was pushed on the list. */
}