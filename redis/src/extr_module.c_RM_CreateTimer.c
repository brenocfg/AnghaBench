#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_16__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ raxIterator ;
typedef  int mstime_t ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_19__ {int /*<<< orphan*/  el; } ;
struct TYPE_18__ {TYPE_2__* client; int /*<<< orphan*/  module; } ;
struct TYPE_17__ {int /*<<< orphan*/  dbid; void* data; int /*<<< orphan*/  callback; int /*<<< orphan*/  module; } ;
struct TYPE_15__ {TYPE_1__* db; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  RedisModuleTimerProc ;
typedef  scalar_t__ RedisModuleTimerID ;
typedef  TYPE_4__ RedisModuleTimer ;
typedef  TYPE_5__ RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  Timers ; 
 int aeCreateTimeEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aeDeleteTimeEvent (int /*<<< orphan*/ ,int) ; 
 int aeTimer ; 
 scalar_t__ htonu64 (scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  moduleTimerHandler ; 
 scalar_t__ raxFind (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxNext (TYPE_3__*) ; 
 scalar_t__ raxNotFound ; 
 int /*<<< orphan*/  raxSeek (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_3__*) ; 
 TYPE_7__ server ; 
 scalar_t__ ustime () ; 
 TYPE_4__* zmalloc (int) ; 

RedisModuleTimerID RM_CreateTimer(RedisModuleCtx *ctx, mstime_t period, RedisModuleTimerProc callback, void *data) {
    RedisModuleTimer *timer = zmalloc(sizeof(*timer));
    timer->module = ctx->module;
    timer->callback = callback;
    timer->data = data;
    timer->dbid = ctx->client->db->id;
    uint64_t expiretime = ustime()+period*1000;
    uint64_t key;

    while(1) {
        key = htonu64(expiretime);
        if (raxFind(Timers, (unsigned char*)&key,sizeof(key)) == raxNotFound) {
            raxInsert(Timers,(unsigned char*)&key,sizeof(key),timer,NULL);
            break;
        } else {
            expiretime++;
        }
    }

    /* We need to install the main event loop timer if it's not already
     * installed, or we may need to refresh its period if we just installed
     * a timer that will expire sooner than any other else. */
    if (aeTimer != -1) {
        raxIterator ri;
        raxStart(&ri,Timers);
        raxSeek(&ri,"^",NULL,0);
        raxNext(&ri);
        if (memcmp(ri.key,&key,sizeof(key)) == 0) {
            /* This is the first key, we need to re-install the timer according
             * to the just added event. */
            aeDeleteTimeEvent(server.el,aeTimer);
            aeTimer = -1;
        }
        raxStop(&ri);
    }

    /* If we have no main timer (the old one was invalidated, or this is the
     * first module timer we have), install one. */
    if (aeTimer == -1)
        aeTimer = aeCreateTimeEvent(server.el,period,moduleTimerHandler,NULL,NULL);

    return key;
}