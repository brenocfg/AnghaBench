#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_17__ {size_t resp; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_18__ {int /*<<< orphan*/ * null; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_ZSET ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,long) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_2__*) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupKeyReadOrReply (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsEncodedObject (TYPE_1__*) ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ shared ; 
 long zsetRank (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void zrankGenericCommand(client *c, int reverse) {
    robj *key = c->argv[1];
    robj *ele = c->argv[2];
    robj *zobj;
    long rank;

    if ((zobj = lookupKeyReadOrReply(c,key,shared.null[c->resp])) == NULL ||
        checkType(c,zobj,OBJ_ZSET)) return;

    serverAssertWithInfo(c,ele,sdsEncodedObject(ele));
    rank = zsetRank(zobj,ele->ptr,reverse);
    if (rank >= 0) {
        addReplyLongLong(c,rank);
    } else {
        addReplyNull(c);
    }
}