#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  TYPE_1__ RedisModuleCallReply ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_AM_REPLY ; 
 int /*<<< orphan*/  RM_FreeCallReply_Rec (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autoMemoryFreed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void RM_FreeCallReply(RedisModuleCallReply *reply) {

    RedisModuleCtx *ctx = reply->ctx;
    RM_FreeCallReply_Rec(reply,0);
    autoMemoryFreed(ctx,REDISMODULE_AM_REPLY,reply);
}