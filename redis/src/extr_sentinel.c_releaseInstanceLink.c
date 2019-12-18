#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* link; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_15__ {TYPE_4__* head; } ;
typedef  TYPE_3__ redisCallbackList ;
struct TYPE_16__ {struct TYPE_16__* next; TYPE_2__* privdata; int /*<<< orphan*/  fn; } ;
typedef  TYPE_4__ redisCallback ;
struct TYPE_17__ {scalar_t__ refcount; TYPE_11__* pc; TYPE_11__* cc; } ;
typedef  TYPE_5__ instanceLink ;
struct TYPE_13__ {scalar_t__ cc; } ;
struct TYPE_12__ {TYPE_3__ replies; } ;

/* Variables and functions */
 int /*<<< orphan*/  instanceLinkCloseConnection (TYPE_5__*,TYPE_11__*) ; 
 int /*<<< orphan*/  sentinelDiscardReplyCallback ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  zfree (TYPE_5__*) ; 

instanceLink *releaseInstanceLink(instanceLink *link, sentinelRedisInstance *ri)
{
    serverAssert(link->refcount > 0);
    link->refcount--;
    if (link->refcount != 0) {
        if (ri && ri->link->cc) {
            /* This instance may have pending callbacks in the hiredis async
             * context, having as 'privdata' the instance that we are going to
             * free. Let's rewrite the callback list, directly exploiting
             * hiredis internal data structures, in order to bind them with
             * a callback that will ignore the reply at all. */
            redisCallback *cb;
            redisCallbackList *callbacks = &link->cc->replies;

            cb = callbacks->head;
            while(cb) {
                if (cb->privdata == ri) {
                    cb->fn = sentinelDiscardReplyCallback;
                    cb->privdata = NULL; /* Not strictly needed. */
                }
                cb = cb->next;
            }
        }
        return link; /* Other active users. */
    }

    instanceLinkCloseConnection(link,link->cc);
    instanceLinkCloseConnection(link,link->pc);
    zfree(link);
    return NULL;
}