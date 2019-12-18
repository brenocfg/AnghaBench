#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_15__ {int /*<<< orphan*/ * module; } ;
struct TYPE_14__ {scalar_t__ id; } ;
struct TYPE_13__ {int /*<<< orphan*/ * callback; TYPE_3__ event; int /*<<< orphan*/ * module; } ;
typedef  TYPE_2__ RedisModuleEventListener ;
typedef  int /*<<< orphan*/ * RedisModuleEventCallback ;
typedef  TYPE_3__ RedisModuleEvent ;
typedef  TYPE_4__ RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_EventListeners ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 
 TYPE_2__* zmalloc (int) ; 

int RM_SubscribeToServerEvent(RedisModuleCtx *ctx, RedisModuleEvent event, RedisModuleEventCallback callback) {
    RedisModuleEventListener *el;

    /* Protect in case of calls from contexts without a module reference. */
    if (ctx->module == NULL) return REDISMODULE_ERR;

    /* Search an event matching this module and event ID. */
    listIter li;
    listNode *ln;
    listRewind(RedisModule_EventListeners,&li);
    while((ln = listNext(&li))) {
        el = ln->value;
        if (el->module == ctx->module && el->event.id == event.id)
            break; /* Matching event found. */
    }

    /* Modify or remove the event listener if we already had one. */
    if (ln) {
        if (callback == NULL) {
            listDelNode(RedisModule_EventListeners,ln);
            zfree(el);
        } else {
            el->callback = callback; /* Update the callback with the new one. */
        }
        return REDISMODULE_OK;
    }

    /* No event found, we need to add a new one. */
    el = zmalloc(sizeof(*el));
    el->module = ctx->module;
    el->event = event;
    el->callback = callback;
    listAddNodeTail(RedisModule_EventListeners,el);
    return REDISMODULE_OK;
}