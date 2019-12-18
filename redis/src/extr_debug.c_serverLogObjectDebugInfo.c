#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* zsl; } ;
typedef  TYPE_2__ zset ;
typedef  int sds ;
struct TYPE_12__ {int type; int encoding; int refcount; scalar_t__ ptr; } ;
typedef  TYPE_3__ robj ;
struct TYPE_10__ {scalar_t__ level; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ OBJ_ENCODING_SKIPLIST ; 
 scalar_t__ OBJ_HASH ; 
 scalar_t__ OBJ_LIST ; 
 scalar_t__ OBJ_SET ; 
 scalar_t__ OBJ_STRING ; 
 scalar_t__ OBJ_ZSET ; 
 scalar_t__ hashTypeLength (TYPE_3__ const*) ; 
 scalar_t__ listTypeLength (TYPE_3__ const*) ; 
 scalar_t__ sdsEncodedObject (TYPE_3__ const*) ; 
 int sdscatrepr (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int) ; 
 int sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setTypeSize (TYPE_3__ const*) ; 
 scalar_t__ zsetLength (TYPE_3__ const*) ; 

void serverLogObjectDebugInfo(const robj *o) {
    serverLog(LL_WARNING,"Object type: %d", o->type);
    serverLog(LL_WARNING,"Object encoding: %d", o->encoding);
    serverLog(LL_WARNING,"Object refcount: %d", o->refcount);
    if (o->type == OBJ_STRING && sdsEncodedObject(o)) {
        serverLog(LL_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
        if (sdslen(o->ptr) < 4096) {
            sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));
            serverLog(LL_WARNING,"Object raw string content: %s", repr);
            sdsfree(repr);
        }
    } else if (o->type == OBJ_LIST) {
        serverLog(LL_WARNING,"List length: %d", (int) listTypeLength(o));
    } else if (o->type == OBJ_SET) {
        serverLog(LL_WARNING,"Set size: %d", (int) setTypeSize(o));
    } else if (o->type == OBJ_HASH) {
        serverLog(LL_WARNING,"Hash size: %d", (int) hashTypeLength(o));
    } else if (o->type == OBJ_ZSET) {
        serverLog(LL_WARNING,"Sorted set size: %d", (int) zsetLength(o));
        if (o->encoding == OBJ_ENCODING_SKIPLIST)
            serverLog(LL_WARNING,"Skiplist level: %d", (int) ((const zset*)o->ptr)->zsl->level);
    }
}