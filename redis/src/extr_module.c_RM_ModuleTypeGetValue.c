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
struct TYPE_7__ {void* value; } ;
typedef  TYPE_2__ moduleValue ;
struct TYPE_8__ {TYPE_1__* value; } ;
struct TYPE_6__ {TYPE_2__* ptr; } ;
typedef  TYPE_3__ RedisModuleKey ;

/* Variables and functions */
 scalar_t__ REDISMODULE_KEYTYPE_MODULE ; 
 scalar_t__ RM_KeyType (TYPE_3__*) ; 

void *RM_ModuleTypeGetValue(RedisModuleKey *key) {
    if (key == NULL ||
        key->value == NULL ||
        RM_KeyType(key) != REDISMODULE_KEYTYPE_MODULE) return NULL;
    moduleValue *mv = key->value->ptr;
    return mv->value;
}