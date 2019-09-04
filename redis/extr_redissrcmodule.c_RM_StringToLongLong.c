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

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 scalar_t__ string2ll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long*) ; 

int RM_StringToLongLong(const RedisModuleString *str, long long *ll) {
    return string2ll(str->ptr,sdslen(str->ptr),ll) ? REDISMODULE_OK :
                                                     REDISMODULE_ERR;
}