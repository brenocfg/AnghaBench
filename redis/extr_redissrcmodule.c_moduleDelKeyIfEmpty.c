#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ robj ;
struct TYPE_9__ {int mode; TYPE_1__* value; int /*<<< orphan*/  key; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ RedisModuleKey ;

/* Variables and functions */
#define  OBJ_HASH 131 
#define  OBJ_LIST 130 
#define  OBJ_SET 129 
#define  OBJ_ZSET 128 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  dbDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashTypeLength (TYPE_1__*) ; 
 int /*<<< orphan*/  listTypeLength (TYPE_1__*) ; 
 int /*<<< orphan*/  setTypeSize (TYPE_1__*) ; 
 int /*<<< orphan*/  zsetLength (TYPE_1__*) ; 

int moduleDelKeyIfEmpty(RedisModuleKey *key) {
    if (!(key->mode & REDISMODULE_WRITE) || key->value == NULL) return 0;
    int isempty;
    robj *o = key->value;

    switch(o->type) {
    case OBJ_LIST: isempty = listTypeLength(o) == 0; break;
    case OBJ_SET: isempty = setTypeSize(o) == 0; break;
    case OBJ_ZSET: isempty = zsetLength(o) == 0; break;
    case OBJ_HASH : isempty = hashTypeLength(o) == 0; break;
    default: isempty = 0;
    }

    if (isempty) {
        dbDelete(key->db,key->key);
        key->value = NULL;
        return 1;
    } else {
        return 0;
    }
}