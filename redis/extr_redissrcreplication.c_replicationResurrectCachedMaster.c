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
struct TYPE_7__ {int fd; int flags; int authenticated; int /*<<< orphan*/  lastinteraction; } ;
struct TYPE_6__ {TYPE_2__* master; int /*<<< orphan*/  el; scalar_t__ repl_down_since; int /*<<< orphan*/  repl_state; int /*<<< orphan*/  unixtime; TYPE_2__* cached_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int CLIENT_CLOSE_AFTER_REPLY ; 
 int CLIENT_CLOSE_ASAP ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  REPL_STATE_CONNECTED ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ clientHasPendingReplies (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_2__*) ; 
 int /*<<< orphan*/  linkClient (TYPE_2__*) ; 
 int /*<<< orphan*/  readQueryFromClient ; 
 int /*<<< orphan*/  sendReplyToClient ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void replicationResurrectCachedMaster(int newfd) {
    server.master = server.cached_master;
    server.cached_master = NULL;
    server.master->fd = newfd;
    server.master->flags &= ~(CLIENT_CLOSE_AFTER_REPLY|CLIENT_CLOSE_ASAP);
    server.master->authenticated = 1;
    server.master->lastinteraction = server.unixtime;
    server.repl_state = REPL_STATE_CONNECTED;
    server.repl_down_since = 0;

    /* Re-add to the list of clients. */
    linkClient(server.master);
    if (aeCreateFileEvent(server.el, newfd, AE_READABLE,
                          readQueryFromClient, server.master)) {
        serverLog(LL_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
        freeClientAsync(server.master); /* Close ASAP. */
    }

    /* We may also need to install the write handler as well if there is
     * pending data in the write buffers. */
    if (clientHasPendingReplies(server.master)) {
        if (aeCreateFileEvent(server.el, newfd, AE_WRITABLE,
                          sendReplyToClient, server.master)) {
            serverLog(LL_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
            freeClientAsync(server.master); /* Close ASAP. */
        }
    }
}