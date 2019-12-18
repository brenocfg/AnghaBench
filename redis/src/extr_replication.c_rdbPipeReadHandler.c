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
typedef  void aeEventLoop ;
typedef  int /*<<< orphan*/  connection ;
struct TYPE_5__ {int repldboff; } ;
typedef  TYPE_1__ client ;
struct TYPE_6__ {scalar_t__ rdb_pipe_numconns_writing; int rdb_pipe_bufflen; int rdb_pipe_numconns; int stat_net_output_bytes; int /*<<< orphan*/  rdb_pipe_read; int /*<<< orphan*/  el; int /*<<< orphan*/ ** rdb_pipe_conns; scalar_t__ rdb_pipe_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 scalar_t__ CONN_STATE_CONNECTED ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  PROTO_IOBUF_LEN ; 
 int /*<<< orphan*/  RdbPipeCleanup () ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connGetLastError (int /*<<< orphan*/ *) ; 
 TYPE_1__* connGetPrivateData (int /*<<< orphan*/ *) ; 
 scalar_t__ connGetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connSetWriteHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int connWrite (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freeClient (TYPE_1__*) ; 
 int /*<<< orphan*/  killRDBChild () ; 
 int /*<<< orphan*/  rdbPipeWriteHandler ; 
 int read (int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ zmalloc (int /*<<< orphan*/ ) ; 

void rdbPipeReadHandler(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask) {
    UNUSED(mask);
    UNUSED(clientData);
    UNUSED(eventLoop);
    int i;
    if (!server.rdb_pipe_buff)
        server.rdb_pipe_buff = zmalloc(PROTO_IOBUF_LEN);
    serverAssert(server.rdb_pipe_numconns_writing==0);

    while (1) {
        server.rdb_pipe_bufflen = read(fd, server.rdb_pipe_buff, PROTO_IOBUF_LEN);
        if (server.rdb_pipe_bufflen < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return;
            serverLog(LL_WARNING,"Diskless rdb transfer, read error sending DB to replicas: %s", strerror(errno));
            for (i=0; i < server.rdb_pipe_numconns; i++) {
                connection *conn = server.rdb_pipe_conns[i];
                if (!conn)
                    continue;
                client *slave = connGetPrivateData(conn);
                freeClient(slave);
                server.rdb_pipe_conns[i] = NULL;
            }
            killRDBChild();
            return;
        }

        if (server.rdb_pipe_bufflen == 0) {
            /* EOF - write end was closed. */
            int stillUp = 0;
            aeDeleteFileEvent(server.el, server.rdb_pipe_read, AE_READABLE);
            for (i=0; i < server.rdb_pipe_numconns; i++)
            {
                connection *conn = server.rdb_pipe_conns[i];
                if (!conn)
                    continue;
                stillUp++;
            }
            serverLog(LL_WARNING,"Diskless rdb transfer, done reading from pipe, %d replicas still up.", stillUp);
            RdbPipeCleanup();
            return;
        }

        int stillAlive = 0;
        for (i=0; i < server.rdb_pipe_numconns; i++)
        {
            int nwritten;
            connection *conn = server.rdb_pipe_conns[i];
            if (!conn)
                continue;

            client *slave = connGetPrivateData(conn);
            if ((nwritten = connWrite(conn, server.rdb_pipe_buff, server.rdb_pipe_bufflen)) == -1) {
                if (connGetState(conn) != CONN_STATE_CONNECTED) {
                    serverLog(LL_WARNING,"Diskless rdb transfer, write error sending DB to replica: %s",
                        connGetLastError(conn));
                    freeClient(slave);
                    server.rdb_pipe_conns[i] = NULL;
                    continue;
                }
                /* An error and still in connected state, is equivalent to EAGAIN */
                slave->repldboff = 0;
            } else {
                slave->repldboff = nwritten;
                server.stat_net_output_bytes += nwritten;
            }
            /* If we were unable to write all the data to one of the replicas,
             * setup write handler (and disable pipe read handler, below) */
            if (nwritten != server.rdb_pipe_bufflen) {
                server.rdb_pipe_numconns_writing++;
                connSetWriteHandler(conn, rdbPipeWriteHandler);
            }
            stillAlive++;
        }

        if (stillAlive == 0) {
            serverLog(LL_WARNING,"Diskless rdb transfer, last replica dropped, killing fork child.");
            killRDBChild();
            RdbPipeCleanup();
        }
        /*  Remove the pipe read handler if at least one write handler was set. */
        if (server.rdb_pipe_numconns_writing || stillAlive == 0) {
            aeDeleteFileEvent(server.el, server.rdb_pipe_read, AE_READABLE);
            break;
        }
    }
}