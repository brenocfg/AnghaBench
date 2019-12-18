#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_3__* value; } ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ RedisModuleString ;
typedef  TYPE_2__ RedisModuleKey ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ OBJ_ZSET ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 scalar_t__ zsetScore (TYPE_3__*,int /*<<< orphan*/ ,double*) ; 

int RM_ZsetScore(RedisModuleKey *key, RedisModuleString *ele, double *score) {
    if (key->value == NULL) return REDISMODULE_ERR;
    if (key->value->type != OBJ_ZSET) return REDISMODULE_ERR;
    if (zsetScore(key->value,ele->ptr,score) == C_ERR) return REDISMODULE_ERR;
    return REDISMODULE_OK;
}