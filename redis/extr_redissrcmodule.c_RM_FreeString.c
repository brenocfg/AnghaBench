#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_AM_STRING ; 
 int /*<<< orphan*/  autoMemoryFreed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 

void RM_FreeString(RedisModuleCtx *ctx, RedisModuleString *str) {
    decrRefCount(str);
    if (ctx != NULL) autoMemoryFreed(ctx,REDISMODULE_AM_STRING,str);
}