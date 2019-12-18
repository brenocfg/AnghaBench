#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; int /*<<< orphan*/ * value; int /*<<< orphan*/  key; int /*<<< orphan*/  db; scalar_t__ iter; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RM_DeleteKey (TYPE_1__*) ; 
 int /*<<< orphan*/  setKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int RM_StringSet(RedisModuleKey *key, RedisModuleString *str) {
    if (!(key->mode & REDISMODULE_WRITE) || key->iter) return REDISMODULE_ERR;
    RM_DeleteKey(key);
    setKey(key->db,key->key,str);
    key->value = str;
    return REDISMODULE_OK;
}