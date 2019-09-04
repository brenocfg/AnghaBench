#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_6__* module_blocked_handle; scalar_t__ timeout; } ;
struct TYPE_17__ {int flags; TYPE_2__ bpop; TYPE_1__* db; } ;
typedef  TYPE_4__ client ;
struct TYPE_19__ {int /*<<< orphan*/  flags; } ;
struct TYPE_18__ {void (* free_privdata ) (TYPE_3__*,void*) ;int /*<<< orphan*/  dbid; TYPE_8__* reply_client; int /*<<< orphan*/ * privdata; int /*<<< orphan*/ * disconnect_callback; void* timeout_callback; void* reply_callback; int /*<<< orphan*/  module; TYPE_4__* client; } ;
struct TYPE_16__ {int /*<<< orphan*/  module; TYPE_4__* client; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ RedisModuleCtx ;
typedef  void* RedisModuleCmdFunc ;
typedef  TYPE_6__ RedisModuleBlockedClient ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED_MODULE ; 
 int CLIENT_LUA ; 
 int /*<<< orphan*/  CLIENT_MODULE ; 
 int CLIENT_MULTI ; 
 int /*<<< orphan*/  addReplyError (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  blockClient (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* createClient (int) ; 
 scalar_t__ mstime () ; 
 TYPE_6__* zmalloc (int) ; 

RedisModuleBlockedClient *RM_BlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc reply_callback, RedisModuleCmdFunc timeout_callback, void (*free_privdata)(RedisModuleCtx*,void*), long long timeout_ms) {
    client *c = ctx->client;
    int islua = c->flags & CLIENT_LUA;
    int ismulti = c->flags & CLIENT_MULTI;

    c->bpop.module_blocked_handle = zmalloc(sizeof(RedisModuleBlockedClient));
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;

    /* We need to handle the invalid operation of calling modules blocking
     * commands from Lua or MULTI. We actually create an already aborted
     * (client set to NULL) blocked client handle, and actually reply with
     * an error. */
    bc->client = (islua || ismulti) ? NULL : c;
    bc->module = ctx->module;
    bc->reply_callback = reply_callback;
    bc->timeout_callback = timeout_callback;
    bc->disconnect_callback = NULL; /* Set by RM_SetDisconnectCallback() */
    bc->free_privdata = free_privdata;
    bc->privdata = NULL;
    bc->reply_client = createClient(-1);
    bc->reply_client->flags |= CLIENT_MODULE;
    bc->dbid = c->db->id;
    c->bpop.timeout = timeout_ms ? (mstime()+timeout_ms) : 0;

    if (islua || ismulti) {
        c->bpop.module_blocked_handle = NULL;
        addReplyError(c, islua ?
            "Blocking module command called from Lua script" :
            "Blocking module command called from transaction");
    } else {
        blockClient(c,BLOCKED_MODULE);
    }
    return bc;
}