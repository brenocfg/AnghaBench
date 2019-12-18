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
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 int /*<<< orphan*/  LRU_CLOCK () ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 scalar_t__ objectSetLRUOrLFU (int /*<<< orphan*/ ,long long,long long,int /*<<< orphan*/ ) ; 

int RM_SetLRUOrLFU(RedisModuleKey *key, long long lfu_freq, long long lru_idle) {
    if (!key->value)
        return REDISMODULE_ERR;
    if (objectSetLRUOrLFU(key->value, lfu_freq, lru_idle, lru_idle>=0 ? LRU_CLOCK() : 0))
        return REDISMODULE_OK;
    return REDISMODULE_ERR;
}