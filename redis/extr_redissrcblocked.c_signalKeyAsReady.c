#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_7__ {int /*<<< orphan*/  ready_keys; int /*<<< orphan*/  blocking_keys; } ;
typedef  TYPE_1__ redisDb ;
struct TYPE_8__ {TYPE_1__* db; int /*<<< orphan*/ * key; } ;
typedef  TYPE_2__ readyList ;
struct TYPE_9__ {int /*<<< orphan*/  ready_keys; } ;

/* Variables and functions */
 scalar_t__ DICT_OK ; 
 scalar_t__ dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 TYPE_2__* zmalloc (int) ; 

void signalKeyAsReady(redisDb *db, robj *key) {
    readyList *rl;

    /* No clients blocking for this key? No need to queue it. */
    if (dictFind(db->blocking_keys,key) == NULL) return;

    /* Key was already signaled? No need to queue it again. */
    if (dictFind(db->ready_keys,key) != NULL) return;

    /* Ok, we need to queue this key into server.ready_keys. */
    rl = zmalloc(sizeof(*rl));
    rl->key = key;
    rl->db = db;
    incrRefCount(key);
    listAddNodeTail(server.ready_keys,rl);

    /* We also add the key in the db->ready_keys dictionary in order
     * to avoid adding it multiple times into a list with a simple O(1)
     * check. */
    incrRefCount(key);
    serverAssert(dictAdd(db->ready_keys,key,NULL) == DICT_OK);
}