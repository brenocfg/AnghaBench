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
struct TYPE_3__ {int type; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  rio ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_ENCODING_HT ; 
 int /*<<< orphan*/  OBJ_ENCODING_INTSET ; 
 int /*<<< orphan*/  OBJ_ENCODING_QUICKLIST ; 
 int /*<<< orphan*/  OBJ_ENCODING_SKIPLIST ; 
 int /*<<< orphan*/  OBJ_ENCODING_ZIPLIST ; 
#define  OBJ_HASH 134 
#define  OBJ_LIST 133 
#define  OBJ_MODULE 132 
#define  OBJ_SET 131 
#define  OBJ_STREAM 130 
#define  OBJ_STRING 129 
#define  OBJ_ZSET 128 
 int /*<<< orphan*/  RDB_TYPE_HASH ; 
 int /*<<< orphan*/  RDB_TYPE_HASH_ZIPLIST ; 
 int /*<<< orphan*/  RDB_TYPE_LIST_QUICKLIST ; 
 int /*<<< orphan*/  RDB_TYPE_MODULE_2 ; 
 int /*<<< orphan*/  RDB_TYPE_SET ; 
 int /*<<< orphan*/  RDB_TYPE_SET_INTSET ; 
 int /*<<< orphan*/  RDB_TYPE_STREAM_LISTPACKS ; 
 int /*<<< orphan*/  RDB_TYPE_STRING ; 
 int /*<<< orphan*/  RDB_TYPE_ZSET_2 ; 
 int /*<<< orphan*/  RDB_TYPE_ZSET_ZIPLIST ; 
 int rdbSaveType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int rdbSaveObjectType(rio *rdb, robj *o) {
    switch (o->type) {
    case OBJ_STRING:
        return rdbSaveType(rdb,RDB_TYPE_STRING);
    case OBJ_LIST:
        if (o->encoding == OBJ_ENCODING_QUICKLIST)
            return rdbSaveType(rdb,RDB_TYPE_LIST_QUICKLIST);
        else
            serverPanic("Unknown list encoding");
    case OBJ_SET:
        if (o->encoding == OBJ_ENCODING_INTSET)
            return rdbSaveType(rdb,RDB_TYPE_SET_INTSET);
        else if (o->encoding == OBJ_ENCODING_HT)
            return rdbSaveType(rdb,RDB_TYPE_SET);
        else
            serverPanic("Unknown set encoding");
    case OBJ_ZSET:
        if (o->encoding == OBJ_ENCODING_ZIPLIST)
            return rdbSaveType(rdb,RDB_TYPE_ZSET_ZIPLIST);
        else if (o->encoding == OBJ_ENCODING_SKIPLIST)
            return rdbSaveType(rdb,RDB_TYPE_ZSET_2);
        else
            serverPanic("Unknown sorted set encoding");
    case OBJ_HASH:
        if (o->encoding == OBJ_ENCODING_ZIPLIST)
            return rdbSaveType(rdb,RDB_TYPE_HASH_ZIPLIST);
        else if (o->encoding == OBJ_ENCODING_HT)
            return rdbSaveType(rdb,RDB_TYPE_HASH);
        else
            serverPanic("Unknown hash encoding");
    case OBJ_STREAM:
        return rdbSaveType(rdb,RDB_TYPE_STREAM_LISTPACKS);
    case OBJ_MODULE:
        return rdbSaveType(rdb,RDB_TYPE_MODULE_2);
    default:
        serverPanic("Unknown object type");
    }
    return -1; /* avoid warning */
}