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
struct TYPE_9__ {int type; } ;
struct TYPE_8__ {TYPE_2__* value; } ;
typedef  TYPE_1__ RedisModuleKey ;

/* Variables and functions */
#define  OBJ_HASH 132 
#define  OBJ_LIST 131 
#define  OBJ_SET 130 
#define  OBJ_STRING 129 
#define  OBJ_ZSET 128 
 size_t hashTypeLength (TYPE_2__*) ; 
 size_t listTypeLength (TYPE_2__*) ; 
 size_t setTypeSize (TYPE_2__*) ; 
 size_t stringObjectLen (TYPE_2__*) ; 
 size_t zsetLength (TYPE_2__*) ; 

size_t RM_ValueLength(RedisModuleKey *key) {
    if (key == NULL || key->value == NULL) return 0;
    switch(key->value->type) {
    case OBJ_STRING: return stringObjectLen(key->value);
    case OBJ_LIST: return listTypeLength(key->value);
    case OBJ_SET: return setTypeSize(key->value);
    case OBJ_ZSET: return zsetLength(key->value);
    case OBJ_HASH: return hashTypeLength(key->value);
    default: return 0;
    }
}