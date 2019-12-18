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
struct TYPE_3__ {int /*<<< orphan*/  ri; } ;
typedef  TYPE_1__ RedisModuleDictIter ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int raxCompare (int /*<<< orphan*/ *,char const*,void*,size_t) ; 
 scalar_t__ raxEOF (int /*<<< orphan*/ *) ; 

int RM_DictCompareC(RedisModuleDictIter *di, const char *op, void *key, size_t keylen) {
    if (raxEOF(&di->ri)) return REDISMODULE_ERR;
    int res = raxCompare(&di->ri,op,key,keylen);
    return res ? REDISMODULE_OK : REDISMODULE_ERR;
}