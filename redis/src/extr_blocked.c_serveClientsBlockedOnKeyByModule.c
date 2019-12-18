#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  key; TYPE_1__* db; } ;
typedef  TYPE_2__ readyList ;
struct TYPE_13__ {TYPE_4__* value; } ;
typedef  TYPE_3__ listNode ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_14__ {scalar_t__ btype; } ;
typedef  TYPE_4__ client ;
struct TYPE_11__ {int /*<<< orphan*/  blocking_keys; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_MODULE ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* listFirst (int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moduleTryServeClientBlockedOnKey (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moduleUnblockClient (TYPE_4__*) ; 

void serveClientsBlockedOnKeyByModule(readyList *rl) {
    dictEntry *de;

    /* We serve clients in the same order they blocked for
     * this key, from the first blocked to the last. */
    de = dictFind(rl->db->blocking_keys,rl->key);
    if (de) {
        list *clients = dictGetVal(de);
        int numclients = listLength(clients);

        while(numclients--) {
            listNode *clientnode = listFirst(clients);
            client *receiver = clientnode->value;

            /* Put at the tail, so that at the next call
             * we'll not run into it again: clients here may not be
             * ready to be served, so they'll remain in the list
             * sometimes. We want also be able to skip clients that are
             * not blocked for the MODULE type safely. */
            listDelNode(clients,clientnode);
            listAddNodeTail(clients,receiver);

            if (receiver->btype != BLOCKED_MODULE) continue;

            /* Note that if *this* client cannot be served by this key,
             * it does not mean that another client that is next into the
             * list cannot be served as well: they may be blocked by
             * different modules with different triggers to consider if a key
             * is ready or not. This means we can't exit the loop but need
             * to continue after the first failure. */
            if (!moduleTryServeClientBlockedOnKey(receiver, rl->key)) continue;

            moduleUnblockClient(receiver);
        }
    }
}