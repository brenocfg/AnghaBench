#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; scalar_t__ encoding; char* ptr; } ;
struct TYPE_5__ {TYPE_2__* value; int /*<<< orphan*/  key; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_RAW ; 
 scalar_t__ OBJ_STRING ; 
 int REDISMODULE_WRITE ; 
 TYPE_2__* dbUnshareStringValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t sdslen (char*) ; 

char *RM_StringDMA(RedisModuleKey *key, size_t *len, int mode) {
    /* We need to return *some* pointer for empty keys, we just return
     * a string literal pointer, that is the advantage to be mapped into
     * a read only memory page, so the module will segfault if a write
     * attempt is performed. */
    char *emptystring = "<dma-empty-string>";
    if (key->value == NULL) {
        *len = 0;
        return emptystring;
    }

    if (key->value->type != OBJ_STRING) return NULL;

    /* For write access, and even for read access if the object is encoded,
     * we unshare the string (that has the side effect of decoding it). */
    if ((mode & REDISMODULE_WRITE) || key->value->encoding != OBJ_ENCODING_RAW)
        key->value = dbUnshareStringValue(key->db, key->key, key->value);

    *len = sdslen(key->value->ptr);
    return key->value->ptr;
}