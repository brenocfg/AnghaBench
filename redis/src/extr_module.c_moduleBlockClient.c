#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ mstime_t ;
struct TYPE_19__ {TYPE_7__* module_blocked_handle; scalar_t__ timeout; } ;
struct TYPE_21__ {int flags; TYPE_3__ bpop; TYPE_2__* db; } ;
typedef  TYPE_5__ client ;
struct TYPE_22__ {void (* free_privdata ) (TYPE_4__*,void*) ;scalar_t__ unblocked; int /*<<< orphan*/  blocked_on_keys; int /*<<< orphan*/  dbid; TYPE_12__* reply_client; void* privdata; int /*<<< orphan*/ * disconnect_callback; void* timeout_callback; void* reply_callback; TYPE_1__* module; TYPE_5__* client; } ;
struct TYPE_20__ {TYPE_1__* module; TYPE_5__* client; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {int /*<<< orphan*/  blocked_clients; } ;
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  TYPE_4__ RedisModuleCtx ;
typedef  void* RedisModuleCmdFunc ;
typedef  TYPE_7__ RedisModuleBlockedClient ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED_MODULE ; 
 int CLIENT_LUA ; 
 int /*<<< orphan*/  CLIENT_MODULE ; 
 int CLIENT_MULTI ; 
 int /*<<< orphan*/  addReplyError (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  blockClient (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blockForKeys (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_12__* createClient (int /*<<< orphan*/ *) ; 
 scalar_t__ mstime () ; 
 TYPE_7__* zmalloc (int) ; 

RedisModuleBlockedClient *moduleBlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc reply_callback, RedisModuleCmdFunc timeout_callback, void (*free_privdata)(RedisModuleCtx*,void*), long long timeout_ms, RedisModuleString **keys, int numkeys, void *privdata) {
    client *c = ctx->client;
    int islua = c->flags & CLIENT_LUA;
    int ismulti = c->flags & CLIENT_MULTI;

    c->bpop.module_blocked_handle = zmalloc(sizeof(RedisModuleBlockedClient));
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;
    ctx->module->blocked_clients++;

    /* We need to handle the invalid operation of calling modules blocking
     * commands from Lua or MULTI. We actually create an already aborted
     * (client set to NULL) blocked client handle, and actually reply with
     * an error. */
    mstime_t timeout = timeout_ms ? (mstime()+timeout_ms) : 0;
    bc->client = (islua || ismulti) ? NULL : c;
    bc->module = ctx->module;
    bc->reply_callback = reply_callback;
    bc->timeout_callback = timeout_callback;
    bc->disconnect_callback = NULL; /* Set by RM_SetDisconnectCallback() */
    bc->free_privdata = free_privdata;
    bc->privdata = privdata;
    bc->reply_client = createClient(NULL);
    bc->reply_client->flags |= CLIENT_MODULE;
    bc->dbid = c->db->id;
    bc->blocked_on_keys = keys != NULL;
    bc->unblocked = 0;
    c->bpop.timeout = timeout;

    if (islua || ismulti) {
        c->bpop.module_blocked_handle = NULL;
        addReplyError(c, islua ?
            "Blocking module command called from Lua script" :
            "Blocking module command called from transaction");
    } else {
        if (keys) {
            blockForKeys(c,BLOCKED_MODULE,keys,numkeys,timeout,NULL,NULL);
        } else {
            blockClient(c,BLOCKED_MODULE);
        }
    }
    return bc;
}