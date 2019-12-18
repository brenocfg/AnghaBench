#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * last_val_string; scalar_t__ last_val_int; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleDictIter ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  TYPE_1__ EventElement ;

/* Variables and functions */
 int /*<<< orphan*/  RedisModule_DictDel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_DictIteratorStart (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_DictIteratorStop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_DictNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  RedisModule_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_log ; 

void clearEvents(RedisModuleCtx *ctx)
{
    RedisModuleString *key;
    EventElement *event;
    RedisModuleDictIter *iter = RedisModule_DictIteratorStart(event_log, "^", NULL);
    while((key = RedisModule_DictNext(ctx, iter, (void**)&event)) != NULL) {
        event->count = 0;
        event->last_val_int = 0;
        if (event->last_val_string) RedisModule_FreeString(ctx, event->last_val_string);
        event->last_val_string = NULL;
        RedisModule_DictDel(event_log, key, NULL);
        RedisModule_Free(event);
    }
    RedisModule_DictIteratorStop(iter);
}