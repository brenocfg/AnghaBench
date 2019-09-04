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
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_11__ {int /*<<< orphan*/  list_compress_depth; int /*<<< orphan*/  list_max_ziplist_size; } ;
struct TYPE_10__ {int mode; TYPE_1__* value; int /*<<< orphan*/  key; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ RedisModuleKey ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
#define  REDISMODULE_KEYTYPE_HASH 130 
#define  REDISMODULE_KEYTYPE_LIST 129 
#define  REDISMODULE_KEYTYPE_ZSET 128 
 int REDISMODULE_OK ; 
 int REDISMODULE_WRITE ; 
 TYPE_1__* createHashObject () ; 
 TYPE_1__* createQuicklistObject () ; 
 TYPE_1__* createZsetZiplistObject () ; 
 int /*<<< orphan*/  dbAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  quicklistSetOptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 

int moduleCreateEmptyKey(RedisModuleKey *key, int type) {
    robj *obj;

    /* The key must be open for writing and non existing to proceed. */
    if (!(key->mode & REDISMODULE_WRITE) || key->value)
        return REDISMODULE_ERR;

    switch(type) {
    case REDISMODULE_KEYTYPE_LIST:
        obj = createQuicklistObject();
        quicklistSetOptions(obj->ptr, server.list_max_ziplist_size,
                            server.list_compress_depth);
        break;
    case REDISMODULE_KEYTYPE_ZSET:
        obj = createZsetZiplistObject();
        break;
    case REDISMODULE_KEYTYPE_HASH:
        obj = createHashObject();
        break;
    default: return REDISMODULE_ERR;
    }
    dbAdd(key->db,key->key,obj);
    key->value = obj;
    return REDISMODULE_OK;
}