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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_6__ {int flags; scalar_t__ replstate; int /*<<< orphan*/ * conn; int /*<<< orphan*/ * client_list_node; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int rdb_pipe_numconns; int /*<<< orphan*/  unblocked_clients; int /*<<< orphan*/  clients_pending_read; int /*<<< orphan*/  clients_pending_write; int /*<<< orphan*/ ** rdb_pipe_conns; int /*<<< orphan*/  clients; int /*<<< orphan*/  clients_index; TYPE_1__* current_client; } ;

/* Variables and functions */
 int CLIENT_PENDING_READ ; 
 int CLIENT_PENDING_WRITE ; 
 int CLIENT_SLAVE ; 
 int CLIENT_TRACKING ; 
 int CLIENT_UNBLOCKED ; 
 scalar_t__ SLAVE_STATE_WAIT_BGSAVE_END ; 
 int /*<<< orphan*/  connClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disableTracking (TYPE_1__*) ; 
 int /*<<< orphan*/  htonu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdbPipeWriteHandlerConnRemoved (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 

void unlinkClient(client *c) {
    listNode *ln;

    /* If this is marked as current client unset it. */
    if (server.current_client == c) server.current_client = NULL;

    /* Certain operations must be done only if the client has an active connection.
     * If the client was already unlinked or if it's a "fake client" the
     * conn is already set to NULL. */
    if (c->conn) {
        /* Remove from the list of active clients. */
        if (c->client_list_node) {
            uint64_t id = htonu64(c->id);
            raxRemove(server.clients_index,(unsigned char*)&id,sizeof(id),NULL);
            listDelNode(server.clients,c->client_list_node);
            c->client_list_node = NULL;
        }

        /* Check if this is a replica waiting for diskless replication (rdb pipe),
         * in which case it needs to be cleaned from that list */
        if (c->flags & CLIENT_SLAVE &&
            c->replstate == SLAVE_STATE_WAIT_BGSAVE_END &&
            server.rdb_pipe_conns)
        {
            int i;
            for (i=0; i < server.rdb_pipe_numconns; i++) {
                if (server.rdb_pipe_conns[i] == c->conn) {
                    rdbPipeWriteHandlerConnRemoved(c->conn);
                    server.rdb_pipe_conns[i] = NULL;
                    break;
                }
            }
        }
        connClose(c->conn);
        c->conn = NULL;
    }

    /* Remove from the list of pending writes if needed. */
    if (c->flags & CLIENT_PENDING_WRITE) {
        ln = listSearchKey(server.clients_pending_write,c);
        serverAssert(ln != NULL);
        listDelNode(server.clients_pending_write,ln);
        c->flags &= ~CLIENT_PENDING_WRITE;
    }

    /* Remove from the list of pending reads if needed. */
    if (c->flags & CLIENT_PENDING_READ) {
        ln = listSearchKey(server.clients_pending_read,c);
        serverAssert(ln != NULL);
        listDelNode(server.clients_pending_read,ln);
        c->flags &= ~CLIENT_PENDING_READ;
    }

    /* When client was just unblocked because of a blocking operation,
     * remove it from the list of unblocked clients. */
    if (c->flags & CLIENT_UNBLOCKED) {
        ln = listSearchKey(server.unblocked_clients,c);
        serverAssert(ln != NULL);
        listDelNode(server.unblocked_clients,ln);
        c->flags &= ~CLIENT_UNBLOCKED;
    }

    /* Clear the tracking status. */
    if (c->flags & CLIENT_TRACKING) disableTracking(c);
}