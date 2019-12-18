#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t btype; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_10__ {int /*<<< orphan*/ * blocked_clients_by_type; int /*<<< orphan*/  blocked_clients; } ;

/* Variables and functions */
 size_t BLOCKED_LIST ; 
 size_t BLOCKED_MODULE ; 
 size_t BLOCKED_NONE ; 
 size_t BLOCKED_STREAM ; 
 size_t BLOCKED_WAIT ; 
 size_t BLOCKED_ZSET ; 
 int /*<<< orphan*/  CLIENT_BLOCKED ; 
 scalar_t__ moduleClientIsBlockedOnKeys (TYPE_1__*) ; 
 int /*<<< orphan*/  queueClientForReprocessing (TYPE_1__*) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  unblockClientFromModule (TYPE_1__*) ; 
 int /*<<< orphan*/  unblockClientWaitingData (TYPE_1__*) ; 
 int /*<<< orphan*/  unblockClientWaitingReplicas (TYPE_1__*) ; 

void unblockClient(client *c) {
    if (c->btype == BLOCKED_LIST ||
        c->btype == BLOCKED_ZSET ||
        c->btype == BLOCKED_STREAM) {
        unblockClientWaitingData(c);
    } else if (c->btype == BLOCKED_WAIT) {
        unblockClientWaitingReplicas(c);
    } else if (c->btype == BLOCKED_MODULE) {
        if (moduleClientIsBlockedOnKeys(c)) unblockClientWaitingData(c);
        unblockClientFromModule(c);
    } else {
        serverPanic("Unknown btype in unblockClient().");
    }
    /* Clear the flags, and put the client in the unblocked list so that
     * we'll process new commands in its query buffer ASAP. */
    server.blocked_clients--;
    server.blocked_clients_by_type[c->btype]--;
    c->flags &= ~CLIENT_BLOCKED;
    c->btype = BLOCKED_NONE;
    queueClientForReprocessing(c);
}