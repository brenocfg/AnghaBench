#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_5__ {int /*<<< orphan*/  pubsub_channels; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyPubsubUnsubscribed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ pubsubUnsubscribeChannel (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int pubsubUnsubscribeAllChannels(client *c, int notify) {
    dictIterator *di = dictGetSafeIterator(c->pubsub_channels);
    dictEntry *de;
    int count = 0;

    while((de = dictNext(di)) != NULL) {
        robj *channel = dictGetKey(de);

        count += pubsubUnsubscribeChannel(c,channel,notify);
    }
    /* We were subscribed to nothing? Still reply to the client. */
    if (notify && count == 0) addReplyPubsubUnsubscribed(c,NULL);
    dictReleaseIterator(di);
    return count;
}