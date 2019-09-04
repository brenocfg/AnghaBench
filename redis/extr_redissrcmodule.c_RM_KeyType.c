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
struct TYPE_5__ {TYPE_1__* value; } ;
struct TYPE_4__ {int type; } ;
typedef  TYPE_2__ RedisModuleKey ;

/* Variables and functions */
#define  OBJ_HASH 133 
#define  OBJ_LIST 132 
#define  OBJ_MODULE 131 
#define  OBJ_SET 130 
#define  OBJ_STRING 129 
#define  OBJ_ZSET 128 
 int REDISMODULE_KEYTYPE_EMPTY ; 
 int REDISMODULE_KEYTYPE_HASH ; 
 int REDISMODULE_KEYTYPE_LIST ; 
 int REDISMODULE_KEYTYPE_MODULE ; 
 int REDISMODULE_KEYTYPE_SET ; 
 int REDISMODULE_KEYTYPE_STRING ; 
 int REDISMODULE_KEYTYPE_ZSET ; 

int RM_KeyType(RedisModuleKey *key) {
    if (key == NULL || key->value ==  NULL) return REDISMODULE_KEYTYPE_EMPTY;
    /* We map between defines so that we are free to change the internal
     * defines as desired. */
    switch(key->value->type) {
    case OBJ_STRING: return REDISMODULE_KEYTYPE_STRING;
    case OBJ_LIST: return REDISMODULE_KEYTYPE_LIST;
    case OBJ_SET: return REDISMODULE_KEYTYPE_SET;
    case OBJ_ZSET: return REDISMODULE_KEYTYPE_ZSET;
    case OBJ_HASH: return REDISMODULE_KEYTYPE_HASH;
    case OBJ_MODULE: return REDISMODULE_KEYTYPE_MODULE;
    default: return 0;
    }
}