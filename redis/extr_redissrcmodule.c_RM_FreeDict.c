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
struct TYPE_5__ {int /*<<< orphan*/  rax; } ;
typedef  TYPE_1__ RedisModuleDict ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_AM_DICT ; 
 int /*<<< orphan*/  autoMemoryFreed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  raxFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void RM_FreeDict(RedisModuleCtx *ctx, RedisModuleDict *d) {
    if (ctx != NULL) autoMemoryFreed(ctx,REDISMODULE_AM_DICT,d);
    raxFree(d->rax);
    zfree(d);
}