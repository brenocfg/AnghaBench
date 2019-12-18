#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {int mode; TYPE_3__* value; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 scalar_t__ OBJ_LIST ; 
 int /*<<< orphan*/  QUICKLIST_HEAD ; 
 int /*<<< orphan*/  QUICKLIST_TAIL ; 
 int REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_KEYTYPE_LIST ; 
 int REDISMODULE_LIST_HEAD ; 
 int REDISMODULE_OK ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  listTypePush (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moduleCreateEmptyKey (TYPE_1__*,int /*<<< orphan*/ ) ; 

int RM_ListPush(RedisModuleKey *key, int where, RedisModuleString *ele) {
    if (!(key->mode & REDISMODULE_WRITE)) return REDISMODULE_ERR;
    if (key->value && key->value->type != OBJ_LIST) return REDISMODULE_ERR;
    if (key->value == NULL) moduleCreateEmptyKey(key,REDISMODULE_KEYTYPE_LIST);
    listTypePush(key->value, ele,
        (where == REDISMODULE_LIST_HEAD) ? QUICKLIST_HEAD : QUICKLIST_TAIL);
    return REDISMODULE_OK;
}