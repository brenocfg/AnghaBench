#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_4__* value; } ;
typedef  TYPE_1__ listNode ;
struct TYPE_19__ {int flags; int /*<<< orphan*/  argc; scalar_t__ argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_22__ {int /*<<< orphan*/  clients_pending_write; int /*<<< orphan*/ * module_blocked_pipe; } ;
struct TYPE_21__ {int /*<<< orphan*/ * disconnect_callback; int /*<<< orphan*/  reply_client; scalar_t__ privdata; int /*<<< orphan*/  (* free_privdata ) (TYPE_3__*,scalar_t__) ;TYPE_2__* client; int /*<<< orphan*/  module; int /*<<< orphan*/  (* reply_callback ) (TYPE_3__*,void**,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {TYPE_2__* client; int /*<<< orphan*/  module; scalar_t__ blocked_privdata; int /*<<< orphan*/  flags; TYPE_4__* blocked_client; } ;
typedef  TYPE_3__ RedisModuleCtx ;
typedef  TYPE_4__ RedisModuleBlockedClient ;

/* Variables and functions */
 int /*<<< orphan*/  AddReplyFromClient (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int CLIENT_PENDING_WRITE ; 
 int /*<<< orphan*/  REDISMODULE_CTX_BLOCKED_DISCONNECTED ; 
 int /*<<< orphan*/  REDISMODULE_CTX_BLOCKED_REPLY ; 
 TYPE_3__ REDISMODULE_CTX_INIT ; 
 scalar_t__ clientHasPendingReplies (TYPE_2__*) ; 
 int /*<<< orphan*/  freeClient (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listAddNodeHead (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* listFirst (int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_3__*) ; 
 int /*<<< orphan*/  moduleHandlePropagationAfterCommandCallback (TYPE_3__*) ; 
 int /*<<< orphan*/  moduleUnblockedClients ; 
 int /*<<< orphan*/  moduleUnblockedClientsMutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_9__ server ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  unblockClient (TYPE_2__*) ; 
 int /*<<< orphan*/  zfree (TYPE_4__*) ; 

void moduleHandleBlockedClients(void) {
    listNode *ln;
    RedisModuleBlockedClient *bc;

    pthread_mutex_lock(&moduleUnblockedClientsMutex);
    /* Here we unblock all the pending clients blocked in modules operations
     * so we can read every pending "awake byte" in the pipe. */
    char buf[1];
    while (read(server.module_blocked_pipe[0],buf,1) == 1);
    while (listLength(moduleUnblockedClients)) {
        ln = listFirst(moduleUnblockedClients);
        bc = ln->value;
        client *c = bc->client;
        listDelNode(moduleUnblockedClients,ln);
        pthread_mutex_unlock(&moduleUnblockedClientsMutex);

        /* Release the lock during the loop, as long as we don't
         * touch the shared list. */

        /* Call the reply callback if the client is valid and we have
         * any callback. */
        if (c && bc->reply_callback) {
            RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
            ctx.flags |= REDISMODULE_CTX_BLOCKED_REPLY;
            ctx.blocked_privdata = bc->privdata;
            ctx.module = bc->module;
            ctx.client = bc->client;
            ctx.blocked_client = bc;
            bc->reply_callback(&ctx,(void**)c->argv,c->argc);
            moduleHandlePropagationAfterCommandCallback(&ctx);
            moduleFreeContext(&ctx);
        }

        /* Free privdata if any. */
        if (bc->privdata && bc->free_privdata) {
            RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
            if (c == NULL)
                ctx.flags |= REDISMODULE_CTX_BLOCKED_DISCONNECTED;
            ctx.blocked_privdata = bc->privdata;
            ctx.module = bc->module;
            ctx.client = bc->client;
            bc->free_privdata(&ctx,bc->privdata);
            moduleFreeContext(&ctx);
        }

        /* It is possible that this blocked client object accumulated
         * replies to send to the client in a thread safe context.
         * We need to glue such replies to the client output buffer and
         * free the temporary client we just used for the replies. */
        if (c) AddReplyFromClient(c, bc->reply_client);
        freeClient(bc->reply_client);

        if (c != NULL) {
            /* Before unblocking the client, set the disconnect callback
             * to NULL, because if we reached this point, the client was
             * properly unblocked by the module. */
            bc->disconnect_callback = NULL;
            unblockClient(c);
            /* Put the client in the list of clients that need to write
             * if there are pending replies here. This is needed since
             * during a non blocking command the client may receive output. */
            if (clientHasPendingReplies(c) &&
                !(c->flags & CLIENT_PENDING_WRITE))
            {
                c->flags |= CLIENT_PENDING_WRITE;
                listAddNodeHead(server.clients_pending_write,c);
            }
        }

        /* Free 'bc' only after unblocking the client, since it is
         * referenced in the client blocking context, and must be valid
         * when calling unblockClient(). */
        zfree(bc);

        /* Lock again before to iterate the loop. */
        pthread_mutex_lock(&moduleUnblockedClientsMutex);
    }
    pthread_mutex_unlock(&moduleUnblockedClientsMutex);
}