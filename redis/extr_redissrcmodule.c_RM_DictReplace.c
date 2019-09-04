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
 int RM_DictReplaceC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

int RM_DictReplace(RedisModuleDict *d, RedisModuleString *key, void *ptr) {
    return RM_DictReplaceC(d,key->ptr,sdslen(key->ptr),ptr);
}