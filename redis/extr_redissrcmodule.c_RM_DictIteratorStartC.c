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
struct TYPE_7__ {int /*<<< orphan*/  rax; } ;
struct TYPE_6__ {int /*<<< orphan*/  ri; TYPE_2__* dict; } ;
typedef  TYPE_1__ RedisModuleDictIter ;
typedef  TYPE_2__ RedisModuleDict ;

/* Variables and functions */
 int /*<<< orphan*/  raxSeek (int /*<<< orphan*/ *,char const*,void*,size_t) ; 
 int /*<<< orphan*/  raxStart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* zmalloc (int) ; 

RedisModuleDictIter *RM_DictIteratorStartC(RedisModuleDict *d, const char *op, void *key, size_t keylen) {
    RedisModuleDictIter *di = zmalloc(sizeof(*di));
    di->dict = d;
    raxStart(&di->ri,d->rax);
    raxSeek(&di->ri,op,key,keylen);
    return di;
}