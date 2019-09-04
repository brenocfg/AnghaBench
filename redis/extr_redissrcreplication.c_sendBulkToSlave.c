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
typedef  int ssize_t ;
struct TYPE_5__ {char* replpreamble; int repldbfd; scalar_t__ repldboff; scalar_t__ repldbsize; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ client ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_6__ {int stat_net_output_bytes; int /*<<< orphan*/  el; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_WRITABLE ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int PROTO_IOBUF_LEN ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freeClient (TYPE_1__*) ; 
 int /*<<< orphan*/  lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putSlaveOnline (TYPE_1__*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 scalar_t__ sdslen (char*) ; 
 int /*<<< orphan*/  sdsrange (char*,int,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*) ; 
 char* strerror (scalar_t__) ; 
 int write (int,char*,int) ; 

void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
    client *slave = privdata;
    UNUSED(el);
    UNUSED(mask);
    char buf[PROTO_IOBUF_LEN];
    ssize_t nwritten, buflen;

    /* Before sending the RDB file, we send the preamble as configured by the
     * replication process. Currently the preamble is just the bulk count of
     * the file in the form "$<length>\r\n". */
    if (slave->replpreamble) {
        nwritten = write(fd,slave->replpreamble,sdslen(slave->replpreamble));
        if (nwritten == -1) {
            serverLog(LL_VERBOSE,"Write error sending RDB preamble to replica: %s",
                strerror(errno));
            freeClient(slave);
            return;
        }
        server.stat_net_output_bytes += nwritten;
        sdsrange(slave->replpreamble,nwritten,-1);
        if (sdslen(slave->replpreamble) == 0) {
            sdsfree(slave->replpreamble);
            slave->replpreamble = NULL;
            /* fall through sending data. */
        } else {
            return;
        }
    }

    /* If the preamble was already transferred, send the RDB bulk data. */
    lseek(slave->repldbfd,slave->repldboff,SEEK_SET);
    buflen = read(slave->repldbfd,buf,PROTO_IOBUF_LEN);
    if (buflen <= 0) {
        serverLog(LL_WARNING,"Read error sending DB to replica: %s",
            (buflen == 0) ? "premature EOF" : strerror(errno));
        freeClient(slave);
        return;
    }
    if ((nwritten = write(fd,buf,buflen)) == -1) {
        if (errno != EAGAIN) {
            serverLog(LL_WARNING,"Write error sending DB to replica: %s",
                strerror(errno));
            freeClient(slave);
        }
        return;
    }
    slave->repldboff += nwritten;
    server.stat_net_output_bytes += nwritten;
    if (slave->repldboff == slave->repldbsize) {
        close(slave->repldbfd);
        slave->repldbfd = -1;
        aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
        putSlaveOnline(slave);
    }
}