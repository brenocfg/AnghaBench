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
struct TYPE_7__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  repl_ack_time; scalar_t__ repl_put_online_on_ack; int /*<<< orphan*/  replstate; } ;
typedef  TYPE_1__ client ;
struct TYPE_8__ {int /*<<< orphan*/  el; int /*<<< orphan*/  unixtime; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SLAVE_STATE_ONLINE ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeClient (TYPE_1__*) ; 
 int /*<<< orphan*/  refreshGoodSlavesCount () ; 
 int /*<<< orphan*/  replicationGetSlaveName (TYPE_1__*) ; 
 int /*<<< orphan*/  sendReplyToClient ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void putSlaveOnline(client *slave) {
    slave->replstate = SLAVE_STATE_ONLINE;
    slave->repl_put_online_on_ack = 0;
    slave->repl_ack_time = server.unixtime; /* Prevent false timeout. */
    if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
        sendReplyToClient, slave) == AE_ERR) {
        serverLog(LL_WARNING,"Unable to register writable event for replica bulk transfer: %s", strerror(errno));
        freeClient(slave);
        return;
    }
    refreshGoodSlavesCount();
    serverLog(LL_NOTICE,"Synchronization with replica %s succeeded",
        replicationGetSlaveName(slave));
}