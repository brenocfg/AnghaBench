#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_5__ {scalar_t__ repldboff; } ;
typedef  TYPE_1__ client ;
struct TYPE_6__ {scalar_t__ rdb_pipe_bufflen; scalar_t__ rdb_pipe_buff; int stat_net_output_bytes; } ;

/* Variables and functions */
 scalar_t__ CONN_STATE_CONNECTED ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  connGetLastError (struct connection*) ; 
 TYPE_1__* connGetPrivateData (struct connection*) ; 
 scalar_t__ connGetState (struct connection*) ; 
 int connWrite (struct connection*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  freeClient (TYPE_1__*) ; 
 int /*<<< orphan*/  rdbPipeWriteHandlerConnRemoved (struct connection*) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void rdbPipeWriteHandler(struct connection *conn) {
    serverAssert(server.rdb_pipe_bufflen>0);
    client *slave = connGetPrivateData(conn);
    int nwritten;
    if ((nwritten = connWrite(conn, server.rdb_pipe_buff + slave->repldboff,
                              server.rdb_pipe_bufflen - slave->repldboff)) == -1)
    {
        if (connGetState(conn) == CONN_STATE_CONNECTED)
            return; /* equivalent to EAGAIN */
        serverLog(LL_WARNING,"Write error sending DB to replica: %s",
            connGetLastError(conn));
        freeClient(slave);
        return;
    } else {
        slave->repldboff += nwritten;
        server.stat_net_output_bytes += nwritten;
        if (slave->repldboff < server.rdb_pipe_bufflen)
            return; /* more data to write.. */
    }
    rdbPipeWriteHandlerConnRemoved(conn);
}