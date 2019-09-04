#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int argc; int /*<<< orphan*/  flags; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_PUBSUB ; 
 scalar_t__ clientSubscriptionsCount (TYPE_1__*) ; 
 int /*<<< orphan*/  pubsubUnsubscribeAllChannels (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pubsubUnsubscribeChannel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void unsubscribeCommand(client *c) {
    if (c->argc == 1) {
        pubsubUnsubscribeAllChannels(c,1);
    } else {
        int j;

        for (j = 1; j < c->argc; j++)
            pubsubUnsubscribeChannel(c,c->argv[j],1);
    }
    if (clientSubscriptionsCount(c) == 0) c->flags &= ~CLIENT_PUBSUB;
}