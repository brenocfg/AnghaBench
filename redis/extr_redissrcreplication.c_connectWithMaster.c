#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int repl_transfer_s; int /*<<< orphan*/  repl_state; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  repl_transfer_lastio; int /*<<< orphan*/  el; int /*<<< orphan*/  masterport; int /*<<< orphan*/  masterhost; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  NET_FIRST_BIND_ADDR ; 
 int /*<<< orphan*/  REPL_STATE_CONNECTING ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int anetTcpNonBlockBestEffortBindConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syncWithMaster ; 

int connectWithMaster(void) {
    int fd;

    fd = anetTcpNonBlockBestEffortBindConnect(NULL,
        server.masterhost,server.masterport,NET_FIRST_BIND_ADDR);
    if (fd == -1) {
        serverLog(LL_WARNING,"Unable to connect to MASTER: %s",
            strerror(errno));
        return C_ERR;
    }

    if (aeCreateFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE,syncWithMaster,NULL) ==
            AE_ERR)
    {
        close(fd);
        serverLog(LL_WARNING,"Can't create readable event for SYNC");
        return C_ERR;
    }

    server.repl_transfer_lastio = server.unixtime;
    server.repl_transfer_s = fd;
    server.repl_state = REPL_STATE_CONNECTING;
    return C_OK;
}