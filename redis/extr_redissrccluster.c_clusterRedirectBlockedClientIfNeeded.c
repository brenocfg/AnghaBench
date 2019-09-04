#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ptr; } ;
typedef  TYPE_3__ robj ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  clusterNode ;
struct TYPE_9__ {int /*<<< orphan*/  keys; } ;
struct TYPE_12__ {int flags; scalar_t__ btype; TYPE_1__ bpop; } ;
typedef  TYPE_4__ client ;
struct TYPE_13__ {TYPE_2__* cluster; } ;
struct TYPE_10__ {scalar_t__ state; int /*<<< orphan*/ ** importing_slots_from; int /*<<< orphan*/ ** slots; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_LIST ; 
 scalar_t__ BLOCKED_STREAM ; 
 scalar_t__ BLOCKED_ZSET ; 
 int CLIENT_BLOCKED ; 
 scalar_t__ CLUSTER_FAIL ; 
 int /*<<< orphan*/  CLUSTER_REDIR_DOWN_STATE ; 
 int /*<<< orphan*/  CLUSTER_REDIR_DOWN_UNBOUND ; 
 int /*<<< orphan*/  CLUSTER_REDIR_MOVED ; 
 int /*<<< orphan*/  clusterRedirectClient (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_3__* dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int keyHashSlot (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * myself ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 TYPE_5__ server ; 

int clusterRedirectBlockedClientIfNeeded(client *c) {
    if (c->flags & CLIENT_BLOCKED &&
        (c->btype == BLOCKED_LIST ||
         c->btype == BLOCKED_ZSET ||
         c->btype == BLOCKED_STREAM))
    {
        dictEntry *de;
        dictIterator *di;

        /* If the cluster is down, unblock the client with the right error. */
        if (server.cluster->state == CLUSTER_FAIL) {
            clusterRedirectClient(c,NULL,0,CLUSTER_REDIR_DOWN_STATE);
            return 1;
        }

        /* All keys must belong to the same slot, so check first key only. */
        di = dictGetIterator(c->bpop.keys);
        if ((de = dictNext(di)) != NULL) {
            robj *key = dictGetKey(de);
            int slot = keyHashSlot((char*)key->ptr, sdslen(key->ptr));
            clusterNode *node = server.cluster->slots[slot];

            /* We send an error and unblock the client if:
             * 1) The slot is unassigned, emitting a cluster down error.
             * 2) The slot is not handled by this node, nor being imported. */
            if (node != myself &&
                server.cluster->importing_slots_from[slot] == NULL)
            {
                if (node == NULL) {
                    clusterRedirectClient(c,NULL,0,
                        CLUSTER_REDIR_DOWN_UNBOUND);
                } else {
                    clusterRedirectClient(c,node,slot,
                        CLUSTER_REDIR_MOVED);
                }
                dictReleaseIterator(di);
                return 1;
            }
        }
        dictReleaseIterator(di);
    }
    return 0;
}