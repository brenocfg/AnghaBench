#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  streamID ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  mstime_t ;
typedef  void list ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_8__ {int /*<<< orphan*/  keys; int /*<<< orphan*/ * target; int /*<<< orphan*/  timeout; } ;
struct TYPE_10__ {TYPE_2__* db; TYPE_1__ bpop; } ;
typedef  TYPE_3__ client ;
struct TYPE_9__ {int /*<<< orphan*/  blocking_keys; } ;

/* Variables and functions */
 int BLOCKED_STREAM ; 
 int DICT_OK ; 
 int /*<<< orphan*/  blockClient (TYPE_3__*,int) ; 
 int dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (void*,TYPE_3__*) ; 
 void* listCreate () ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfree (void*) ; 
 void* zmalloc (int) ; 

void blockForKeys(client *c, int btype, robj **keys, int numkeys, mstime_t timeout, robj *target, streamID *ids) {
    dictEntry *de;
    list *l;
    int j;

    c->bpop.timeout = timeout;
    c->bpop.target = target;

    if (target != NULL) incrRefCount(target);

    for (j = 0; j < numkeys; j++) {
        /* The value associated with the key name in the bpop.keys dictionary
         * is NULL for lists and sorted sets, or the stream ID for streams. */
        void *key_data = NULL;
        if (btype == BLOCKED_STREAM) {
            key_data = zmalloc(sizeof(streamID));
            memcpy(key_data,ids+j,sizeof(streamID));
        }

        /* If the key already exists in the dictionary ignore it. */
        if (dictAdd(c->bpop.keys,keys[j],key_data) != DICT_OK) {
            zfree(key_data);
            continue;
        }
        incrRefCount(keys[j]);

        /* And in the other "side", to map keys -> clients */
        de = dictFind(c->db->blocking_keys,keys[j]);
        if (de == NULL) {
            int retval;

            /* For every key we take a list of clients blocked for it */
            l = listCreate();
            retval = dictAdd(c->db->blocking_keys,keys[j],l);
            incrRefCount(keys[j]);
            serverAssertWithInfo(c,keys[j],retval == DICT_OK);
        } else {
            l = dictGetVal(de);
        }
        listAddNodeTail(l,c);
    }
    blockClient(c,btype);
}