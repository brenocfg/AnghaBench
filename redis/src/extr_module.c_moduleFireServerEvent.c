#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_16__ {TYPE_4__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_23__ {int /*<<< orphan*/ * user; int /*<<< orphan*/  flags; } ;
struct TYPE_22__ {scalar_t__ id; int /*<<< orphan*/  dataver; } ;
struct TYPE_21__ {int /*<<< orphan*/  in_hook; int /*<<< orphan*/  ver; int /*<<< orphan*/  name; } ;
struct TYPE_20__ {TYPE_9__* client; TYPE_6__* module; } ;
struct TYPE_19__ {TYPE_6__* module; TYPE_8__ event; int /*<<< orphan*/  (* callback ) (TYPE_5__*,TYPE_8__,int,void*) ;} ;
struct TYPE_18__ {int dbnum; } ;
struct TYPE_17__ {int /*<<< orphan*/  module_version; int /*<<< orphan*/  module_name; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  RedisModuleReplicationInfoV1 ;
typedef  TYPE_2__ RedisModuleModuleChangeV1 ;
typedef  TYPE_3__ RedisModuleFlushInfoV1 ;
typedef  TYPE_4__ RedisModuleEventListener ;
typedef  TYPE_5__ RedisModuleCtx ;
typedef  int /*<<< orphan*/  RedisModuleClientInfoV1 ;
typedef  TYPE_6__ RedisModule ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_MODULE ; 
 scalar_t__ ModulesInHooks ; 
 TYPE_5__ REDISMODULE_CTX_INIT ; 
 scalar_t__ REDISMODULE_EVENT_CLIENT_CHANGE ; 
 scalar_t__ REDISMODULE_EVENT_CRON_LOOP ; 
 scalar_t__ REDISMODULE_EVENT_FLUSHDB ; 
 scalar_t__ REDISMODULE_EVENT_LOADING_PROGRESS ; 
 scalar_t__ REDISMODULE_EVENT_MODULE_CHANGE ; 
 scalar_t__ REDISMODULE_EVENT_REPLICATION_ROLE_CHANGED ; 
 int /*<<< orphan*/  REDISMODULE_MODULE_CHANGE_VERSION ; 
 int /*<<< orphan*/  RedisModule_EventListeners ; 
 TYPE_9__* createClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeClient (TYPE_9__*) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_5__*) ; 
 TYPE_9__* moduleFreeContextReusedClient ; 
 int /*<<< orphan*/  modulePopulateClientInfoStructure (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modulePopulateReplicationInfoStructure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDb (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_8__,int,void*) ; 

void moduleFireServerEvent(uint64_t eid, int subid, void *data) {
    /* Fast path to return ASAP if there is nothing to do, avoiding to
     * setup the iterator and so forth: we want this call to be extremely
     * cheap if there are no registered modules. */
    if (listLength(RedisModule_EventListeners) == 0) return;

    listIter li;
    listNode *ln;
    listRewind(RedisModule_EventListeners,&li);
    while((ln = listNext(&li))) {
        RedisModuleEventListener *el = ln->value;
        if (el->event.id == eid) {
            RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
            ctx.module = el->module;

            if (ModulesInHooks == 0) {
                ctx.client = moduleFreeContextReusedClient;
            } else {
                ctx.client = createClient(NULL);
                ctx.client->flags |= CLIENT_MODULE;
                ctx.client->user = NULL; /* Root user. */
            }

            void *moduledata = NULL;
            RedisModuleClientInfoV1 civ1;
            RedisModuleReplicationInfoV1 riv1;
            RedisModuleModuleChangeV1 mcv1;
            /* Start at DB zero by default when calling the handler. It's
             * up to the specific event setup to change it when it makes
             * sense. For instance for FLUSHDB events we select the correct
             * DB automatically. */
            selectDb(ctx.client, 0);

            /* Event specific context and data pointer setup. */
            if (eid == REDISMODULE_EVENT_CLIENT_CHANGE) {
                modulePopulateClientInfoStructure(&civ1,data,
                                                  el->event.dataver);
                moduledata = &civ1;
            } else if (eid == REDISMODULE_EVENT_REPLICATION_ROLE_CHANGED) {
                modulePopulateReplicationInfoStructure(&riv1,el->event.dataver);
                moduledata = &riv1;
            } else if (eid == REDISMODULE_EVENT_FLUSHDB) {
                moduledata = data;
                RedisModuleFlushInfoV1 *fi = data;
                if (fi->dbnum != -1)
                    selectDb(ctx.client, fi->dbnum);
            } else if (eid == REDISMODULE_EVENT_MODULE_CHANGE) {
                RedisModule *m = data;
                if (m == el->module)
                    continue;
                mcv1.version = REDISMODULE_MODULE_CHANGE_VERSION;
                mcv1.module_name = m->name;
                mcv1.module_version = m->ver;
                moduledata = &mcv1;
            } else if (eid == REDISMODULE_EVENT_LOADING_PROGRESS) {
                moduledata = data;
            } else if (eid == REDISMODULE_EVENT_CRON_LOOP) {
                moduledata = data;
            }

            ModulesInHooks++;
            el->module->in_hook++;
            el->callback(&ctx,el->event,subid,moduledata);
            el->module->in_hook--;
            ModulesInHooks--;

            if (ModulesInHooks != 0) freeClient(ctx.client);
            moduleFreeContext(&ctx);
        }
    }
}