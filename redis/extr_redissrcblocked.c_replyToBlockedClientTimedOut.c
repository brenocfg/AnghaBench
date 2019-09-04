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
struct TYPE_7__ {int /*<<< orphan*/  reploffset; } ;
struct TYPE_8__ {scalar_t__ btype; TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;

/* Variables and functions */
 scalar_t__ BLOCKED_LIST ; 
 scalar_t__ BLOCKED_MODULE ; 
 scalar_t__ BLOCKED_STREAM ; 
 scalar_t__ BLOCKED_WAIT ; 
 scalar_t__ BLOCKED_ZSET ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyNullArray (TYPE_2__*) ; 
 int /*<<< orphan*/  moduleBlockedClientTimedOut (TYPE_2__*) ; 
 int /*<<< orphan*/  replicationCountAcksByOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

void replyToBlockedClientTimedOut(client *c) {
    if (c->btype == BLOCKED_LIST ||
        c->btype == BLOCKED_ZSET ||
        c->btype == BLOCKED_STREAM) {
        addReplyNullArray(c);
    } else if (c->btype == BLOCKED_WAIT) {
        addReplyLongLong(c,replicationCountAcksByOffset(c->bpop.reploffset));
    } else if (c->btype == BLOCKED_MODULE) {
        moduleBlockedClientTimedOut(c);
    } else {
        serverPanic("Unknown btype in replyToBlockedClientTimedOut().");
    }
}