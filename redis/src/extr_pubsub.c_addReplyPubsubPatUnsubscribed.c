#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_10__ {int resp; } ;
typedef  TYPE_1__ client ;
struct TYPE_11__ {int /*<<< orphan*/  punsubscribebulk; int /*<<< orphan*/ * mbulkhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_1__*) ; 
 int /*<<< orphan*/  addReplyPushLen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clientSubscriptionsCount (TYPE_1__*) ; 
 TYPE_2__ shared ; 

void addReplyPubsubPatUnsubscribed(client *c, robj *pattern) {
    if (c->resp == 2)
        addReply(c,shared.mbulkhdr[3]);
    else
        addReplyPushLen(c,3);
    addReply(c,shared.punsubscribebulk);
    if (pattern)
        addReplyBulk(c,pattern);
    else
        addReplyNull(c);
    addReplyLongLong(c,clientSubscriptionsCount(c));
}