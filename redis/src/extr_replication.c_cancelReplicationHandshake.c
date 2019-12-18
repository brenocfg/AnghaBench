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
struct TYPE_2__ {scalar_t__ repl_state; } ;

/* Variables and functions */
 void* REPL_STATE_CONNECT ; 
 scalar_t__ REPL_STATE_CONNECTING ; 
 scalar_t__ REPL_STATE_TRANSFER ; 
 int /*<<< orphan*/  replicationAbortSyncTransfer () ; 
 TYPE_1__ server ; 
 scalar_t__ slaveIsInHandshakeState () ; 
 int /*<<< orphan*/  undoConnectWithMaster () ; 

int cancelReplicationHandshake(void) {
    if (server.repl_state == REPL_STATE_TRANSFER) {
        replicationAbortSyncTransfer();
        server.repl_state = REPL_STATE_CONNECT;
    } else if (server.repl_state == REPL_STATE_CONNECTING ||
               slaveIsInHandshakeState())
    {
        undoConnectWithMaster();
        server.repl_state = REPL_STATE_CONNECT;
    } else {
        return 0;
    }
    return 1;
}