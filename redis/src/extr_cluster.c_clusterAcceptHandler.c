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
typedef  int /*<<< orphan*/  connection ;
typedef  int /*<<< orphan*/  cip ;
typedef  void aeEventLoop ;
struct TYPE_2__ {scalar_t__ tls_cluster; int /*<<< orphan*/  neterr; scalar_t__ loading; int /*<<< orphan*/ * masterhost; } ;

/* Variables and functions */
 int ANET_ERR ; 
 scalar_t__ C_ERR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int MAX_CLUSTER_ACCEPTS_PER_CALL ; 
 int NET_IP_STR_LEN ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int anetTcpAccept (int /*<<< orphan*/ ,int,char*,int,int*) ; 
 int /*<<< orphan*/  clusterConnAcceptHandler ; 
 scalar_t__ connAccept (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * connCreateAcceptedSocket (int) ; 
 int /*<<< orphan*/ * connCreateAcceptedTLS (int,int) ; 
 int /*<<< orphan*/  connEnableTcpNoDelay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connGetLastError (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connNonBlock (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*,...) ; 

void clusterAcceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    int cport, cfd;
    int max = MAX_CLUSTER_ACCEPTS_PER_CALL;
    char cip[NET_IP_STR_LEN];
    UNUSED(el);
    UNUSED(mask);
    UNUSED(privdata);

    /* If the server is starting up, don't accept cluster connections:
     * UPDATE messages may interact with the database content. */
    if (server.masterhost == NULL && server.loading) return;

    while(max--) {
        cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
        if (cfd == ANET_ERR) {
            if (errno != EWOULDBLOCK)
                serverLog(LL_VERBOSE,
                    "Error accepting cluster node: %s", server.neterr);
            return;
        }

        connection *conn = server.tls_cluster ? connCreateAcceptedTLS(cfd,1) : connCreateAcceptedSocket(cfd);
        connNonBlock(conn);
        connEnableTcpNoDelay(conn);

        /* Use non-blocking I/O for cluster messages. */
        serverLog(LL_VERBOSE,"Accepting cluster node connection from %s:%d", cip, cport);

        /* Accept the connection now.  connAccept() may call our handler directly
         * or schedule it for later depending on connection implementation.
         */
        if (connAccept(conn, clusterConnAcceptHandler) == C_ERR) {
            serverLog(LL_VERBOSE,
                    "Error accepting cluster node connection: %s",
                    connGetLastError(conn));
            connClose(conn);
            return;
        }
    }
}