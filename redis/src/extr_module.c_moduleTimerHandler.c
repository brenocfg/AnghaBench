#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  void aeEventLoop ;
struct TYPE_12__ {int /*<<< orphan*/  key_len; scalar_t__ key; TYPE_2__* data; } ;
typedef  TYPE_1__ raxIterator ;
typedef  int /*<<< orphan*/  expiretime ;
struct TYPE_14__ {int /*<<< orphan*/  client; int /*<<< orphan*/  module; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* callback ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dbid; int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ RedisModuleTimer ;
typedef  TYPE_3__ RedisModuleCtx ;

/* Variables and functions */
 int AE_NOMORE ; 
 TYPE_3__ REDISMODULE_CTX_INIT ; 
 int /*<<< orphan*/  Timers ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_3__*) ; 
 int /*<<< orphan*/  moduleFreeContextReusedClient ; 
 scalar_t__ ntohu64 (scalar_t__) ; 
 int /*<<< orphan*/  raxNext (TYPE_1__*) ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxSeek (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ raxSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_1__*) ; 
 int /*<<< orphan*/  selectDb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ustime () ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

int moduleTimerHandler(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    UNUSED(eventLoop);
    UNUSED(id);
    UNUSED(clientData);

    /* To start let's try to fire all the timers already expired. */
    raxIterator ri;
    raxStart(&ri,Timers);
    uint64_t now = ustime();
    long long next_period = 0;
    while(1) {
        raxSeek(&ri,"^",NULL,0);
        if (!raxNext(&ri)) break;
        uint64_t expiretime;
        memcpy(&expiretime,ri.key,sizeof(expiretime));
        expiretime = ntohu64(expiretime);
        if (now >= expiretime) {
            RedisModuleTimer *timer = ri.data;
            RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

            ctx.module = timer->module;
            ctx.client = moduleFreeContextReusedClient;
            selectDb(ctx.client, timer->dbid);
            timer->callback(&ctx,timer->data);
            moduleFreeContext(&ctx);
            raxRemove(Timers,(unsigned char*)ri.key,ri.key_len,NULL);
            zfree(timer);
        } else {
            next_period = (expiretime-now)/1000; /* Scale to milliseconds. */
            break;
        }
    }
    raxStop(&ri);

    /* Reschedule the next timer or cancel it. */
    if (next_period <= 0) next_period = 1;
    return (raxSize(Timers) > 0) ? next_period : AE_NOMORE;
}