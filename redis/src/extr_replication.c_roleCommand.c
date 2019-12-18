#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  ip ;
struct TYPE_16__ {char* slave_ip; scalar_t__ replstate; int /*<<< orphan*/  repl_ack_off; int /*<<< orphan*/  slave_listening_port; int /*<<< orphan*/  conn; } ;
typedef  TYPE_3__ client ;
struct TYPE_17__ {char* masterhost; int master_repl_offset; int masterport; int repl_state; TYPE_1__* master; int /*<<< orphan*/  slaves; } ;
struct TYPE_14__ {int reploff; } ;

/* Variables and functions */
 int NET_IP_STR_LEN ; 
#define  REPL_STATE_CONNECT 132 
#define  REPL_STATE_CONNECTED 131 
#define  REPL_STATE_CONNECTING 130 
#define  REPL_STATE_NONE 129 
#define  REPL_STATE_TRANSFER 128 
 scalar_t__ SLAVE_STATE_ONLINE ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_3__*,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  addReplyBulkCString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* addReplyDeferredLen (TYPE_3__*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_3__*,int) ; 
 int connPeerToString (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  setDeferredArrayLen (TYPE_3__*,void*,int) ; 
 scalar_t__ slaveIsInHandshakeState () ; 

void roleCommand(client *c) {
    if (server.masterhost == NULL) {
        listIter li;
        listNode *ln;
        void *mbcount;
        int slaves = 0;

        addReplyArrayLen(c,3);
        addReplyBulkCBuffer(c,"master",6);
        addReplyLongLong(c,server.master_repl_offset);
        mbcount = addReplyDeferredLen(c);
        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            client *slave = ln->value;
            char ip[NET_IP_STR_LEN], *slaveip = slave->slave_ip;

            if (slaveip[0] == '\0') {
                if (connPeerToString(slave->conn,ip,sizeof(ip),NULL) == -1)
                    continue;
                slaveip = ip;
            }
            if (slave->replstate != SLAVE_STATE_ONLINE) continue;
            addReplyArrayLen(c,3);
            addReplyBulkCString(c,slaveip);
            addReplyBulkLongLong(c,slave->slave_listening_port);
            addReplyBulkLongLong(c,slave->repl_ack_off);
            slaves++;
        }
        setDeferredArrayLen(c,mbcount,slaves);
    } else {
        char *slavestate = NULL;

        addReplyArrayLen(c,5);
        addReplyBulkCBuffer(c,"slave",5);
        addReplyBulkCString(c,server.masterhost);
        addReplyLongLong(c,server.masterport);
        if (slaveIsInHandshakeState()) {
            slavestate = "handshake";
        } else {
            switch(server.repl_state) {
            case REPL_STATE_NONE: slavestate = "none"; break;
            case REPL_STATE_CONNECT: slavestate = "connect"; break;
            case REPL_STATE_CONNECTING: slavestate = "connecting"; break;
            case REPL_STATE_TRANSFER: slavestate = "sync"; break;
            case REPL_STATE_CONNECTED: slavestate = "connected"; break;
            default: slavestate = "unknown"; break;
            }
        }
        addReplyBulkCString(c,slavestate);
        addReplyLongLong(c,server.master ? server.master->reploff : -1);
    }
}