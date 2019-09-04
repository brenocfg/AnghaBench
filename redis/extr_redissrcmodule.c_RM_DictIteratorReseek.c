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
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleDictIter ;

/* Variables and functions */
 int RM_DictIteratorReseekC (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

int RM_DictIteratorReseek(RedisModuleDictIter *di, const char *op, RedisModuleString *key) {
    return RM_DictIteratorReseekC(di,op,key->ptr,sdslen(key->ptr));
}