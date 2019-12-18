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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  connection ;
struct TYPE_4__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  sndbuf; } ;
typedef  TYPE_1__ clusterLink ;

/* Variables and functions */
 int /*<<< orphan*/  LL_DEBUG ; 
 char* connGetLastError (int /*<<< orphan*/ *) ; 
 TYPE_1__* connGetPrivateData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connSetWriteHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int connWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  handleLinkIOError (TYPE_1__*) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*) ; 

void clusterWriteHandler(connection *conn) {
    clusterLink *link = connGetPrivateData(conn);
    ssize_t nwritten;

    nwritten = connWrite(conn, link->sndbuf, sdslen(link->sndbuf));
    if (nwritten <= 0) {
        serverLog(LL_DEBUG,"I/O error writing to node link: %s",
            (nwritten == -1) ? connGetLastError(conn) : "short write");
        handleLinkIOError(link);
        return;
    }
    sdsrange(link->sndbuf,nwritten,-1);
    if (sdslen(link->sndbuf) == 0)
        connSetWriteHandler(link->conn, NULL);
}