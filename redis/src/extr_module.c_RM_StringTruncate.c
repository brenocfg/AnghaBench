#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_10__ {int mode; TYPE_1__* value; int /*<<< orphan*/  key; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ RedisModuleKey ;

/* Variables and functions */
 scalar_t__ OBJ_STRING ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int REDISMODULE_WRITE ; 
 TYPE_1__* createObject (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* dbUnshareStringValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  sdsRemoveFreeSpace (int /*<<< orphan*/ ) ; 
 size_t sdsavail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsgrowzero (int /*<<< orphan*/ ,size_t) ; 
 size_t sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  setKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

int RM_StringTruncate(RedisModuleKey *key, size_t newlen) {
    if (!(key->mode & REDISMODULE_WRITE)) return REDISMODULE_ERR;
    if (key->value && key->value->type != OBJ_STRING) return REDISMODULE_ERR;
    if (newlen > 512*1024*1024) return REDISMODULE_ERR;

    /* Empty key and new len set to 0. Just return REDISMODULE_OK without
     * doing anything. */
    if (key->value == NULL && newlen == 0) return REDISMODULE_OK;

    if (key->value == NULL) {
        /* Empty key: create it with the new size. */
        robj *o = createObject(OBJ_STRING,sdsnewlen(NULL, newlen));
        setKey(key->db,key->key,o);
        key->value = o;
        decrRefCount(o);
    } else {
        /* Unshare and resize. */
        key->value = dbUnshareStringValue(key->db, key->key, key->value);
        size_t curlen = sdslen(key->value->ptr);
        if (newlen > curlen) {
            key->value->ptr = sdsgrowzero(key->value->ptr,newlen);
        } else if (newlen < curlen) {
            sdsrange(key->value->ptr,0,newlen-1);
            /* If the string is too wasteful, reallocate it. */
            if (sdslen(key->value->ptr) < sdsavail(key->value->ptr))
                key->value->ptr = sdsRemoveFreeSpace(key->value->ptr);
        }
    }
    return REDISMODULE_OK;
}