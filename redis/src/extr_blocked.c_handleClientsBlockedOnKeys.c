#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ type; } ;
typedef  TYPE_1__ robj ;
struct TYPE_19__ {int /*<<< orphan*/  key; TYPE_14__* db; } ;
typedef  TYPE_2__ readyList ;
struct TYPE_20__ {TYPE_2__* value; } ;
typedef  TYPE_3__ listNode ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_21__ {int /*<<< orphan*/ * ready_keys; } ;
struct TYPE_17__ {int /*<<< orphan*/  ready_keys; } ;

/* Variables and functions */
 scalar_t__ OBJ_LIST ; 
 scalar_t__ OBJ_STREAM ; 
 scalar_t__ OBJ_ZSET ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listCreate () ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* listFirst (int /*<<< orphan*/ *) ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyWrite (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serveClientsBlockedOnKeyByModule (TYPE_2__*) ; 
 int /*<<< orphan*/  serveClientsBlockedOnListKey (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  serveClientsBlockedOnSortedSetKey (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  serveClientsBlockedOnStreamKey (TYPE_1__*,TYPE_2__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void handleClientsBlockedOnKeys(void) {
    while(listLength(server.ready_keys) != 0) {
        list *l;

        /* Point server.ready_keys to a fresh list and save the current one
         * locally. This way as we run the old list we are free to call
         * signalKeyAsReady() that may push new elements in server.ready_keys
         * when handling clients blocked into BRPOPLPUSH. */
        l = server.ready_keys;
        server.ready_keys = listCreate();

        while(listLength(l) != 0) {
            listNode *ln = listFirst(l);
            readyList *rl = ln->value;

            /* First of all remove this key from db->ready_keys so that
             * we can safely call signalKeyAsReady() against this key. */
            dictDelete(rl->db->ready_keys,rl->key);

            /* Serve clients blocked on list key. */
            robj *o = lookupKeyWrite(rl->db,rl->key);

            if (o != NULL) {
                if (o->type == OBJ_LIST)
                    serveClientsBlockedOnListKey(o,rl);
                else if (o->type == OBJ_ZSET)
                    serveClientsBlockedOnSortedSetKey(o,rl);
                else if (o->type == OBJ_STREAM)
                    serveClientsBlockedOnStreamKey(o,rl);
                /* We want to serve clients blocked on module keys
                 * regardless of the object type: we don't know what the
                 * module is trying to accomplish right now. */
                serveClientsBlockedOnKeyByModule(rl);
            }

            /* Free this item. */
            decrRefCount(rl->key);
            zfree(rl);
            listDelNode(l,ln);
        }
        listRelease(l); /* We have the new list on place at this point. */
    }
}