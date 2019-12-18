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
struct TYPE_3__ {int mode; int /*<<< orphan*/ * value; int /*<<< orphan*/  key; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  dbDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int RM_DeleteKey(RedisModuleKey *key) {
    if (!(key->mode & REDISMODULE_WRITE)) return REDISMODULE_ERR;
    if (key->value) {
        dbDelete(key->db,key->key);
        key->value = NULL;
    }
    return REDISMODULE_OK;
}