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
struct RedisModuleDict {int /*<<< orphan*/  rax; } ;
typedef  struct RedisModuleDict RedisModuleDict ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_AM_DICT ; 
 int /*<<< orphan*/  autoMemoryAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct RedisModuleDict*) ; 
 int /*<<< orphan*/  raxNew () ; 
 struct RedisModuleDict* zmalloc (int) ; 

RedisModuleDict *RM_CreateDict(RedisModuleCtx *ctx) {
    struct RedisModuleDict *d = zmalloc(sizeof(*d));
    d->rax = raxNew();
    if (ctx != NULL) autoMemoryAdd(ctx,REDISMODULE_AM_DICT,d);
    return d;
}