#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_13__ {scalar_t__ reploffset; scalar_t__ numreplicas; scalar_t__ xread_group_noack; int /*<<< orphan*/ * xread_consumer; int /*<<< orphan*/ * xread_group; int /*<<< orphan*/ * target; void* keys; scalar_t__ timeout; } ;
struct TYPE_14__ {int resp; int fd; int bulklen; int authenticated; char* slave_ip; void* pubsub_patterns; int /*<<< orphan*/ * client_list_node; int /*<<< orphan*/ * peerid; void* pubsub_channels; void* watched_keys; scalar_t__ woff; TYPE_1__ bpop; int /*<<< orphan*/  btype; void* reply; scalar_t__ obuf_soft_limit_reached_time; scalar_t__ reply_bytes; int /*<<< orphan*/  slave_capa; scalar_t__ slave_listening_port; scalar_t__ repl_ack_time; scalar_t__ repl_ack_off; scalar_t__ read_reploff; scalar_t__ reploff; scalar_t__ repl_put_online_on_ack; int /*<<< orphan*/  replstate; TYPE_11__* user; int /*<<< orphan*/  lastinteraction; int /*<<< orphan*/  ctime; scalar_t__ flags; scalar_t__ sentlen; scalar_t__ multibulklen; int /*<<< orphan*/ * lastcmd; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * argv; scalar_t__ argc; scalar_t__ reqtype; scalar_t__ querybuf_peak; void* pending_querybuf; void* querybuf; scalar_t__ qb_pos; scalar_t__ bufpos; int /*<<< orphan*/ * name; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ client ;
struct TYPE_15__ {int /*<<< orphan*/  unixtime; int /*<<< orphan*/  next_client_id; int /*<<< orphan*/  el; scalar_t__ tcpkeepalive; } ;
struct TYPE_12__ {int flags; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  BLOCKED_NONE ; 
 TYPE_11__* DefaultUser ; 
 int /*<<< orphan*/  REPL_STATE_NONE ; 
 int /*<<< orphan*/  SLAVE_CAPA_NONE ; 
 int USER_FLAG_NOPASS ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  anetEnableTcpNoDelay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  anetKeepAlive (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  anetNonBlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomicGetIncr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
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
 TYPE_5__ server ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 
 TYPE_2__* zmalloc (int) ; 

client *createClient(int fd) {
    client *c = zmalloc(sizeof(client));

    /* passing -1 as fd it is possible to create a non connected client.
     * This is useful since all the commands needs to be executed
     * in the context of a client. When commands are executed in other
     * contexts (for instance a Lua script) we need a non connected client. */
    if (fd != -1) {
        anetNonBlock(NULL,fd);
        anetEnableTcpNoDelay(NULL,fd);
        if (server.tcpkeepalive)
            anetKeepAlive(NULL,fd,server.tcpkeepalive);
        if (aeCreateFileEvent(server.el,fd,AE_READABLE,
            readQueryFromClient, c) == AE_ERR)
        {
            close(fd);
            zfree(c);
            return NULL;
        }
    }

    selectDb(c,0);
    uint64_t client_id;
    atomicGetIncr(server.next_client_id,client_id,1);
    c->id = client_id;
    c->resp = 2;
    c->fd = fd;
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
    listSetFreeMethod(c->pubsub_patterns,decrRefCountVoid);
    listSetMatchMethod(c->pubsub_patterns,listMatchObjects);
    if (fd != -1) linkClient(c);
    initClientMultiState(c);
    return c;
}