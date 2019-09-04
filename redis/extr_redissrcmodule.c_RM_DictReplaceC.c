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
struct TYPE_3__ {int /*<<< orphan*/  rax; } ;
typedef  TYPE_1__ RedisModuleDict ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int raxInsert (int /*<<< orphan*/ ,void*,size_t,void*,int /*<<< orphan*/ *) ; 

int RM_DictReplaceC(RedisModuleDict *d, void *key, size_t keylen, void *ptr) {
    int retval = raxInsert(d->rax,key,keylen,ptr,NULL);
    return (retval == 1) ? REDISMODULE_OK : REDISMODULE_ERR;
}