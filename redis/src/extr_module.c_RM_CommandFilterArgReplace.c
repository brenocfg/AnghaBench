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
struct TYPE_3__ {int argc; int /*<<< orphan*/ ** argv; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  TYPE_1__ RedisModuleCommandFilterCtx ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 

int RM_CommandFilterArgReplace(RedisModuleCommandFilterCtx *fctx, int pos, RedisModuleString *arg)
{
    if (pos < 0 || pos >= fctx->argc) return REDISMODULE_ERR;

    decrRefCount(fctx->argv[pos]);
    fctx->argv[pos] = arg;

    return REDISMODULE_OK;
}