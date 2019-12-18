#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  reploff; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {TYPE_1__* master; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_MASTER_FORCE_REPLY ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  addReplyBulkCString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

void replicationSendAck(void) {
    client *c = server.master;

    if (c != NULL) {
        c->flags |= CLIENT_MASTER_FORCE_REPLY;
        addReplyArrayLen(c,3);
        addReplyBulkCString(c,"REPLCONF");
        addReplyBulkCString(c,"ACK");
        addReplyBulkLongLong(c,c->reploff);
        c->flags &= ~CLIENT_MASTER_FORCE_REPLY;
    }
}