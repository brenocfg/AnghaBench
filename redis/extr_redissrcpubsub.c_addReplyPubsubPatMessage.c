#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_7__ {int resp; } ;
typedef  TYPE_1__ client ;
struct TYPE_8__ {int /*<<< orphan*/  pmessagebulk; int /*<<< orphan*/ * mbulkhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyPushLen (TYPE_1__*,int) ; 
 TYPE_2__ shared ; 

void addReplyPubsubPatMessage(client *c, robj *pat, robj *channel, robj *msg) {
    if (c->resp == 2)
        addReply(c,shared.mbulkhdr[4]);
    else
        addReplyPushLen(c,4);
    addReply(c,shared.pmessagebulk);
    addReplyBulk(c,pat);
    addReplyBulk(c,channel);
    addReplyBulk(c,msg);
}