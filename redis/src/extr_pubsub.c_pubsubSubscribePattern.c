#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* client; int /*<<< orphan*/  pattern; } ;
typedef  TYPE_1__ robj ;
typedef  TYPE_1__ pubsubPattern ;
struct TYPE_15__ {int /*<<< orphan*/  pubsub_patterns; } ;
typedef  TYPE_3__ client ;
struct TYPE_16__ {int /*<<< orphan*/  pubsub_patterns; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyPubsubPatSubscribed (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  getDecodedObject (TYPE_1__*) ; 
 int /*<<< orphan*/  incrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_5__ server ; 
 TYPE_1__* zmalloc (int) ; 

int pubsubSubscribePattern(client *c, robj *pattern) {
    int retval = 0;

    if (listSearchKey(c->pubsub_patterns,pattern) == NULL) {
        retval = 1;
        pubsubPattern *pat;
        listAddNodeTail(c->pubsub_patterns,pattern);
        incrRefCount(pattern);
        pat = zmalloc(sizeof(*pat));
        pat->pattern = getDecodedObject(pattern);
        pat->client = c;
        listAddNodeTail(server.pubsub_patterns,pat);
    }
    /* Notify the client */
    addReplyPubsubPatSubscribed(c,pattern);
    return retval;
}