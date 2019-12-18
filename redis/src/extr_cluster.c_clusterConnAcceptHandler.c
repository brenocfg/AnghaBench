#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  connection ;
struct TYPE_4__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ clusterLink ;

/* Variables and functions */
 scalar_t__ CONN_STATE_CONNECTED ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  clusterReadHandler ; 
 int /*<<< orphan*/  connClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connGetLastError (int /*<<< orphan*/ *) ; 
 scalar_t__ connGetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connSetPrivateData (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  connSetReadHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* createClusterLink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clusterConnAcceptHandler(connection *conn) {
    clusterLink *link;

    if (connGetState(conn) != CONN_STATE_CONNECTED) {
        serverLog(LL_VERBOSE,
                "Error accepting cluster node connection: %s", connGetLastError(conn));
        connClose(conn);
        return;
    }

    /* Create a link object we use to handle the connection.
     * It gets passed to the readable handler when data is available.
     * Initiallly the link->node pointer is set to NULL as we don't know
     * which node is, but the right node is references once we know the
     * node identity. */
    link = createClusterLink(NULL);
    link->conn = conn;
    connSetPrivateData(conn, link);

    /* Register read handler */
    connSetReadHandler(conn, clusterReadHandler);
}