#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int CLIENT_CLOSE_AFTER_REPLY ; 
 int /*<<< orphan*/  addReplySds (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  unblockClient (TYPE_1__*) ; 

void disconnectAllBlockedClients(void) {
    listNode *ln;
    listIter li;

    listRewind(server.clients,&li);
    while((ln = listNext(&li))) {
        client *c = listNodeValue(ln);

        if (c->flags & CLIENT_BLOCKED) {
            addReplySds(c,sdsnew(
                "-UNBLOCKED force unblock from blocking operation, "
                "instance state changed (master -> replica?)\r\n"));
            unblockClient(c);
            c->flags |= CLIENT_CLOSE_AFTER_REPLY;
        }
    }
}