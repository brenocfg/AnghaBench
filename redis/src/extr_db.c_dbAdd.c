#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_13__ {int /*<<< orphan*/  dict; } ;
typedef  TYPE_2__ redisDb ;
struct TYPE_14__ {scalar_t__ cluster_enabled; } ;

/* Variables and functions */
 int DICT_OK ; 
 scalar_t__ OBJ_LIST ; 
 scalar_t__ OBJ_ZSET ; 
 int dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sdsdup (int /*<<< orphan*/ ) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  signalKeyAsReady (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  slotToKeyAdd (TYPE_1__*) ; 

void dbAdd(redisDb *db, robj *key, robj *val) {
    sds copy = sdsdup(key->ptr);
    int retval = dictAdd(db->dict, copy, val);

    serverAssertWithInfo(NULL,key,retval == DICT_OK);
    if (val->type == OBJ_LIST ||
        val->type == OBJ_ZSET)
        signalKeyAsReady(db, key);
    if (server.cluster_enabled) slotToKeyAdd(key);
}