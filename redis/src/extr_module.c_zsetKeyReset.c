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
struct TYPE_3__ {int zer; int /*<<< orphan*/ * zcurrent; int /*<<< orphan*/  ztype; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_ZSET_RANGE_NONE ; 

void zsetKeyReset(RedisModuleKey *key) {
    key->ztype = REDISMODULE_ZSET_RANGE_NONE;
    key->zcurrent = NULL;
    key->zer = 1;
}