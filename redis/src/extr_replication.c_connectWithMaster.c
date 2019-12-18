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
struct TYPE_2__ {int /*<<< orphan*/  repl_state; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  repl_transfer_lastio; int /*<<< orphan*/ * repl_transfer_s; int /*<<< orphan*/  masterport; int /*<<< orphan*/  masterhost; scalar_t__ tls_replication; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  NET_FIRST_BIND_ADDR ; 
 int /*<<< orphan*/  REPL_STATE_CONNECTING ; 
 int /*<<< orphan*/  connClose (int /*<<< orphan*/ *) ; 
 scalar_t__ connConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * connCreateSocket () ; 
 int /*<<< orphan*/ * connCreateTLS () ; 
 int /*<<< orphan*/  connGetLastError (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syncWithMaster ; 

int connectWithMaster(void) {
    server.repl_transfer_s = server.tls_replication ? connCreateTLS() : connCreateSocket();
    if (connConnect(server.repl_transfer_s, server.masterhost, server.masterport,
                NET_FIRST_BIND_ADDR, syncWithMaster) == C_ERR) {
        serverLog(LL_WARNING,"Unable to connect to MASTER: %s",
                connGetLastError(server.repl_transfer_s));
        connClose(server.repl_transfer_s);
        server.repl_transfer_s = NULL;
        return C_ERR;
    }


    server.repl_transfer_lastio = server.unixtime;
    server.repl_state = REPL_STATE_CONNECTING;
    return C_OK;
}