#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_1__* moduleAssertUnsharedString (TYPE_1__*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char const*,size_t) ; 

int RM_StringAppendBuffer(RedisModuleCtx *ctx, RedisModuleString *str, const char *buf, size_t len) {
    UNUSED(ctx);
    str = moduleAssertUnsharedString(str);
    if (str == NULL) return REDISMODULE_ERR;
    str->ptr = sdscatlen(str->ptr,buf,len);
    return REDISMODULE_OK;
}