#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mode; int /*<<< orphan*/  ctx; int /*<<< orphan*/  key; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_AM_KEY ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RM_ZsetRangeStop (TYPE_1__*) ; 
 int SHOULD_SIGNAL_MODIFIED_KEYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autoMemoryFreed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signalModifiedKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void RM_CloseKey(RedisModuleKey *key) {
    if (key == NULL) return;
    int signal = SHOULD_SIGNAL_MODIFIED_KEYS(key->ctx);
    if ((key->mode & REDISMODULE_WRITE) && signal)
        signalModifiedKey(key->db,key->key);
    /* TODO: if (key->iter) RM_KeyIteratorStop(kp); */
    RM_ZsetRangeStop(key);
    decrRefCount(key->key);
    autoMemoryFreed(key->ctx,REDISMODULE_AM_KEY,key);
    zfree(key);
}