#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_11__ {TYPE_1__* client; } ;
struct TYPE_10__ {int mode; int /*<<< orphan*/ * iter; int /*<<< orphan*/ * value; int /*<<< orphan*/ * key; int /*<<< orphan*/  db; TYPE_3__* ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ RedisModuleKey ;
typedef  TYPE_3__ RedisModuleCtx ;

/* Variables and functions */
 int LOOKUP_NOTOUCH ; 
 int /*<<< orphan*/  REDISMODULE_AM_KEY ; 
 int REDISMODULE_OPEN_KEY_NOTOUCH ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  autoMemoryAdd (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyReadWithFlags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lookupKeyWriteWithFlags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* zmalloc (int) ; 
 int /*<<< orphan*/  zsetKeyReset (TYPE_2__*) ; 

void *RM_OpenKey(RedisModuleCtx *ctx, robj *keyname, int mode) {
    RedisModuleKey *kp;
    robj *value;
    int flags = mode & REDISMODULE_OPEN_KEY_NOTOUCH? LOOKUP_NOTOUCH: 0;

    if (mode & REDISMODULE_WRITE) {
        value = lookupKeyWriteWithFlags(ctx->client->db,keyname, flags);
    } else {
        value = lookupKeyReadWithFlags(ctx->client->db,keyname, flags);
        if (value == NULL) {
            return NULL;
        }
    }

    /* Setup the key handle. */
    kp = zmalloc(sizeof(*kp));
    kp->ctx = ctx;
    kp->db = ctx->client->db;
    kp->key = keyname;
    incrRefCount(keyname);
    kp->value = value;
    kp->iter = NULL;
    kp->mode = mode;
    zsetKeyReset(kp);
    autoMemoryAdd(ctx,REDISMODULE_AM_KEY,kp);
    return (void*)kp;
}