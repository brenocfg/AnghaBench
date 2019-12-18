#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  connection ;
struct TYPE_8__ {int /*<<< orphan*/  totlen; int /*<<< orphan*/  sig; } ;
typedef  TYPE_1__ clusterMsg ;
struct TYPE_9__ {scalar_t__ rcvbuf; } ;
typedef  TYPE_2__ clusterLink ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned int CLUSTERMSG_MIN_LEN ; 
 scalar_t__ CONN_STATE_CONNECTED ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ clusterProcessPacket (TYPE_2__*) ; 
 char* connGetLastError (int /*<<< orphan*/ *) ; 
 TYPE_2__* connGetPrivateData (int /*<<< orphan*/ *) ; 
 scalar_t__ connGetState (int /*<<< orphan*/ *) ; 
 int connRead (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  handleLinkIOError (TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ sdscatlen (scalar_t__,TYPE_1__*,int) ; 
 scalar_t__ sdsempty () ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 unsigned int sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 

void clusterReadHandler(connection *conn) {
    clusterMsg buf[1];
    ssize_t nread;
    clusterMsg *hdr;
    clusterLink *link = connGetPrivateData(conn);
    unsigned int readlen, rcvbuflen;

    while(1) { /* Read as long as there is data to read. */
        rcvbuflen = sdslen(link->rcvbuf);
        if (rcvbuflen < 8) {
            /* First, obtain the first 8 bytes to get the full message
             * length. */
            readlen = 8 - rcvbuflen;
        } else {
            /* Finally read the full message. */
            hdr = (clusterMsg*) link->rcvbuf;
            if (rcvbuflen == 8) {
                /* Perform some sanity check on the message signature
                 * and length. */
                if (memcmp(hdr->sig,"RCmb",4) != 0 ||
                    ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN)
                {
                    serverLog(LL_WARNING,
                        "Bad message length or signature received "
                        "from Cluster bus.");
                    handleLinkIOError(link);
                    return;
                }
            }
            readlen = ntohl(hdr->totlen) - rcvbuflen;
            if (readlen > sizeof(buf)) readlen = sizeof(buf);
        }

        nread = connRead(conn,buf,readlen);
        if (nread == -1 && (connGetState(conn) == CONN_STATE_CONNECTED)) return; /* No more data ready. */

        if (nread <= 0) {
            /* I/O error... */
            serverLog(LL_DEBUG,"I/O error reading from node link: %s",
                (nread == 0) ? "connection closed" : connGetLastError(conn));
            handleLinkIOError(link);
            return;
        } else {
            /* Read data and recast the pointer to the new buffer. */
            link->rcvbuf = sdscatlen(link->rcvbuf,buf,nread);
            hdr = (clusterMsg*) link->rcvbuf;
            rcvbuflen += nread;
        }

        /* Total length obtained? Process this packet. */
        if (rcvbuflen >= 8 && rcvbuflen == ntohl(hdr->totlen)) {
            if (clusterProcessPacket(link)) {
                sdsfree(link->rcvbuf);
                link->rcvbuf = sdsempty();
            } else {
                return; /* Link no longer valid. */
            }
        }
    }
}