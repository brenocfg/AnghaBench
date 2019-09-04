#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  module; } ;
struct TYPE_6__ {int event_mask; scalar_t__ active; int /*<<< orphan*/  notify_callback; int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  RedisModuleNotificationFunc ;
typedef  TYPE_1__ RedisModuleKeyspaceSubscriber ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  moduleKeyspaceSubscribers ; 
 TYPE_1__* zmalloc (int) ; 

int RM_SubscribeToKeyspaceEvents(RedisModuleCtx *ctx, int types, RedisModuleNotificationFunc callback) {
    RedisModuleKeyspaceSubscriber *sub = zmalloc(sizeof(*sub));
    sub->module = ctx->module;
    sub->event_mask = types;
    sub->notify_callback = callback;
    sub->active = 0;

    listAddNodeTail(moduleKeyspaceSubscribers, sub);
    return REDISMODULE_OK;
}