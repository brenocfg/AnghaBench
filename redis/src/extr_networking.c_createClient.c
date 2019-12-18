#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  connection ;
struct TYPE_12__ {scalar_t__ reploffset; scalar_t__ numreplicas; scalar_t__ xread_group_noack; int /*<<< orphan*/ * xread_consumer; int /*<<< orphan*/ * xread_group; int /*<<< orphan*/ * target; void* keys; scalar_t__ timeout; } ;
struct TYPE_13__ {int resp; int bulklen; int authenticated; char* slave_ip; void* pubsub_patterns; scalar_t__ client_tracking_redirection; int /*<<< orphan*/ * client_list_node; int /*<<< orphan*/ * peerid; void* pubsub_channels; void* watched_keys; scalar_t__ woff; TYPE_1__ bpop; int /*<<< orphan*/  btype; void* reply; scalar_t__ obuf_soft_limit_reached_time; scalar_t__ reply_bytes; int /*<<< orphan*/  slave_capa; scalar_t__ slave_listening_port; scalar_t__ repl_ack_time; scalar_t__ repl_ack_off; scalar_t__ read_reploff; scalar_t__ reploff; scalar_t__ repl_put_online_on_ack; int /*<<< orphan*/  replstate; TYPE_10__* user; int /*<<< orphan*/  lastinteraction; int /*<<< orphan*/  ctime; scalar_t__ flags; scalar_t__ sentlen; scalar_t__ multibulklen; int /*<<< orphan*/ * lastcmd; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * argv; scalar_t__ argc; scalar_t__ reqtype; scalar_t__ querybuf_peak; void* pending_querybuf; void* querybuf; scalar_t__ qb_pos; scalar_t__ bufpos; int /*<<< orphan*/ * name; int /*<<< orphan*/ * conn; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ client ;
struct TYPE_14__ {int /*<<< orphan*/  unixtime; int /*<<< orphan*/  next_client_id; scalar_t__ tcpkeepalive; } ;
struct TYPE_11__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED_NONE ; 
 TYPE_10__* DefaultUser ; 
 int /*<<< orphan*/  REPL_STATE_NONE ; 
 int /*<<< orphan*/  SLAVE_CAPA_NONE ; 
 int USER_FLAG_NOPASS ; 
 int /*<<< orphan*/  connEnableTcpNoDelay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connKeepAlive (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  connNonBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connSetPrivateData (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  connSetReadHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCountVoid ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dupClientReplyValue ; 
 int /*<<< orphan*/  freeClientReplyValue ; 
 int /*<<< orphan*/  initClientMultiState (TYPE_2__*) ; 
 int /*<<< orphan*/  linkClient (TYPE_2__*) ; 
 void* listCreate () ; 
 int /*<<< orphan*/  listMatchObjects ; 
 int /*<<< orphan*/  listSetDupMethod (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listSetFreeMethod (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listSetMatchMethod (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objectKeyHeapPointerValueDictType ; 
 int /*<<< orphan*/  objectKeyPointerValueDictType ; 
 int /*<<< orphan*/  readQueryFromClient ; 
 void* sdsempty () ; 
 int /*<<< orphan*/  selectDb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 
 TYPE_2__* zmalloc (int) ; 

client *createClient(connection *conn) {
    client *c = zmalloc(sizeof(client));

    /* passing NULL as conn it is possible to create a non connected client.
     * This is useful since all the commands needs to be executed
     * in the context of a client. When commands are executed in other
     * contexts (for instance a Lua script) we need a non connected client. */
    if (conn) {
        connNonBlock(conn);
        connEnableTcpNoDelay(conn);
        if (server.tcpkeepalive)
            connKeepAlive(conn,server.tcpkeepalive);
        connSetReadHandler(conn, readQueryFromClient);
        connSetPrivateData(conn, c);
    }

    selectDb(c,0);
    uint64_t client_id = ++server.next_client_id;
    c->id = client_id;
    c->resp = 2;
    c->conn = conn;
    c->name = NULL;
    c->bufpos = 0;
    c->qb_pos = 0;
    c->querybuf = sdsempty();
    c->pending_querybuf = sdsempty();
    c->querybuf_peak = 0;
    c->reqtype = 0;
    c->argc = 0;
    c->argv = NULL;
    c->cmd = c->lastcmd = NULL;
    c->user = DefaultUser;
    c->multibulklen = 0;
    c->bulklen = -1;
    c->sentlen = 0;
    c->flags = 0;
    c->ctime = c->lastinteraction = server.unixtime;
    /* If the default user does not require authentication, the user is
     * directly authenticated. */
    c->authenticated = (c->user->flags & USER_FLAG_NOPASS) != 0;
    c->replstate = REPL_STATE_NONE;
    c->repl_put_online_on_ack = 0;
    c->reploff = 0;
    c->read_reploff = 0;
    c->repl_ack_off = 0;
    c->repl_ack_time = 0;
    c->slave_listening_port = 0;
    c->slave_ip[0] = '\0';
    c->slave_capa = SLAVE_CAPA_NONE;
    c->reply = listCreate();
    c->reply_bytes = 0;
    c->obuf_soft_limit_reached_time = 0;
    listSetFreeMethod(c->reply,freeClientReplyValue);
    listSetDupMethod(c->reply,dupClientReplyValue);
    c->btype = BLOCKED_NONE;
    c->bpop.timeout = 0;
    c->bpop.keys = dictCreate(&objectKeyHeapPointerValueDictType,NULL);
    c->bpop.target = NULL;
    c->bpop.xread_group = NULL;
    c->bpop.xread_consumer = NULL;
    c->bpop.xread_group_noack = 0;
    c->bpop.numreplicas = 0;
    c->bpop.reploffset = 0;
    c->woff = 0;
    c->watched_keys = listCreate();
    c->pubsub_channels = dictCreate(&objectKeyPointerValueDictType,NULL);
    c->pubsub_patterns = listCreate();
    c->peerid = NULL;
    c->client_list_node = NULL;
    c->client_tracking_redirection = 0;
    listSetFreeMethod(c->pubsub_patterns,decrRefCountVoid);
    listSetMatchMethod(c->pubsub_patterns,listMatchObjects);
    if (conn) linkClient(c);
    initClientMultiState(c);
    return c;
}