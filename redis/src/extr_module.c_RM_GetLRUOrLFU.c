#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int maxmemory_policy; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 long long LFUDecrAndReturn (int /*<<< orphan*/ ) ; 
 int MAXMEMORY_FLAG_LFU ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int estimateObjectIdleTime (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

int RM_GetLRUOrLFU(RedisModuleKey *key, long long *lfu_freq, long long *lru_idle) {
    *lru_idle = *lfu_freq = -1;
    if (!key->value)
        return REDISMODULE_ERR;
    if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
        *lfu_freq = LFUDecrAndReturn(key->value);
    } else {
        *lru_idle = estimateObjectIdleTime(key->value)/1000;
    }
    return REDISMODULE_OK;
}