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
typedef  int /*<<< orphan*/  RedisModuleDict ;

/* Variables and functions */
 void* RM_DictGetC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

void *RM_DictGet(RedisModuleDict *d, RedisModuleString *key, int *nokey) {
    return RM_DictGetC(d,key->ptr,sdslen(key->ptr),nokey);
}