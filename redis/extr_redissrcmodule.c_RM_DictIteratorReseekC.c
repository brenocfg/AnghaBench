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
 int raxSeek (int /*<<< orphan*/ *,char const*,void*,size_t) ; 

int RM_DictIteratorReseekC(RedisModuleDictIter *di, const char *op, void *key, size_t keylen) {
    return raxSeek(&di->ri,op,key,keylen);
}