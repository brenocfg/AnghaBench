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
struct TYPE_6__ {int flags; scalar_t__ btype; scalar_t__ qb_pos; int /*<<< orphan*/  querybuf; scalar_t__ read_reploff; scalar_t__ reploff; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {TYPE_1__* current_client; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_MODULE ; 
 int CLIENT_BLOCKED ; 
 int CLIENT_MASTER ; 
 int CLIENT_MULTI ; 
 int C_ERR ; 
 scalar_t__ C_OK ; 
 scalar_t__ processCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  resetClient (TYPE_1__*) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

int processCommandAndResetClient(client *c) {
    int deadclient = 0;
    server.current_client = c;
    if (processCommand(c) == C_OK) {
        if (c->flags & CLIENT_MASTER && !(c->flags & CLIENT_MULTI)) {
            /* Update the applied replication offset of our master. */
            c->reploff = c->read_reploff - sdslen(c->querybuf) + c->qb_pos;
        }

        /* Don't reset the client structure for clients blocked in a
         * module blocking command, so that the reply callback will
         * still be able to access the client argv and argc field.
         * The client will be reset in unblockClientFromModule(). */
        if (!(c->flags & CLIENT_BLOCKED) ||
            c->btype != BLOCKED_MODULE)
        {
            resetClient(c);
        }
    }
    if (server.current_client == NULL) deadclient = 1;
    server.current_client = NULL;
    /* freeMemoryIfNeeded may flush slave output buffers. This may
     * result into a slave, that may be the active client, to be
     * freed. */
    return deadclient ? C_ERR : C_OK;
}