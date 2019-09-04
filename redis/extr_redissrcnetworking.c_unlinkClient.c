#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_5__ {int fd; int flags; scalar_t__ replstate; int /*<<< orphan*/ * client_list_node; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ client ;
struct TYPE_6__ {int /*<<< orphan*/  unblocked_clients; int /*<<< orphan*/  clients_pending_write; int /*<<< orphan*/  el; int /*<<< orphan*/  clients; int /*<<< orphan*/  clients_index; TYPE_1__* current_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int CLIENT_PENDING_WRITE ; 
 int CLIENT_SLAVE ; 
 int CLIENT_UNBLOCKED ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 scalar_t__ SLAVE_STATE_WAIT_BGSAVE_END ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  htonu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

void unlinkClient(client *c) {
    listNode *ln;

    /* If this is marked as current client unset it. */
    if (server.current_client == c) server.current_client = NULL;

    /* Certain operations must be done only if the client has an active socket.
     * If the client was already unlinked or if it's a "fake client" the
     * fd is already set to -1. */
    if (c->fd != -1) {
        /* Remove from the list of active clients. */
        if (c->client_list_node) {
            uint64_t id = htonu64(c->id);
            raxRemove(server.clients_index,(unsigned char*)&id,sizeof(id),NULL);
            listDelNode(server.clients,c->client_list_node);
            c->client_list_node = NULL;
        }

        /* In the case of diskless replication the fork is writing to the
         * sockets and just closing the fd isn't enough, if we don't also
         * shutdown the socket the fork will continue to write to the slave
         * and the salve will only find out that it was disconnected when
         * it will finish reading the rdb. */
        if ((c->flags & CLIENT_SLAVE) &&
            (c->replstate == SLAVE_STATE_WAIT_BGSAVE_END)) {
            shutdown(c->fd, SHUT_RDWR);
        }

        /* Unregister async I/O handlers and close the socket. */
        aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
        aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
        close(c->fd);
        c->fd = -1;
    }

    /* Remove from the list of pending writes if needed. */
    if (c->flags & CLIENT_PENDING_WRITE) {
        ln = listSearchKey(server.clients_pending_write,c);
        serverAssert(ln != NULL);
        listDelNode(server.clients_pending_write,ln);
        c->flags &= ~CLIENT_PENDING_WRITE;
    }

    /* When client was just unblocked because of a blocking operation,
     * remove it from the list of unblocked clients. */
    if (c->flags & CLIENT_UNBLOCKED) {
        ln = listSearchKey(server.unblocked_clients,c);
        serverAssert(ln != NULL);
        listDelNode(server.unblocked_clients,ln);
        c->flags &= ~CLIENT_UNBLOCKED;
    }
}