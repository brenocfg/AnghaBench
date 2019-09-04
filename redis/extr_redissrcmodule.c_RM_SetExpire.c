#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mstime_t ;
struct TYPE_5__ {int mode; int /*<<< orphan*/  key; int /*<<< orphan*/  db; TYPE_1__* ctx; int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_2__ RedisModuleKey ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 scalar_t__ REDISMODULE_NO_EXPIRE ; 
 int REDISMODULE_OK ; 
 int REDISMODULE_WRITE ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  removeExpire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setExpire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int RM_SetExpire(RedisModuleKey *key, mstime_t expire) {
    if (!(key->mode & REDISMODULE_WRITE) || key->value == NULL)
        return REDISMODULE_ERR;
    if (expire != REDISMODULE_NO_EXPIRE) {
        expire += mstime();
        setExpire(key->ctx->client,key->db,key->key,expire);
    } else {
        removeExpire(key->db,key->key);
    }
    return REDISMODULE_OK;
}