#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_15__ {int id; } ;
typedef  TYPE_1__ redisDb ;
struct TYPE_16__ {int /*<<< orphan*/ * argv; TYPE_1__* db; } ;
typedef  TYPE_2__ client ;
struct TYPE_18__ {int /*<<< orphan*/  dirty; scalar_t__ cluster_enabled; } ;
struct TYPE_17__ {int /*<<< orphan*/  cone; int /*<<< orphan*/  czero; int /*<<< orphan*/  sameobjecterr; int /*<<< orphan*/  outofrangeerr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 long long INT_MAX ; 
 long long INT_MIN ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dbAdd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbDelete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 long long getExpire (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongLongFromObject (int /*<<< orphan*/ ,long long*) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyWrite (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ selectDb (TYPE_2__*,int) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  setExpire (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,long long) ; 
 TYPE_3__ shared ; 

void moveCommand(client *c) {
    robj *o;
    redisDb *src, *dst;
    int srcid;
    long long dbid, expire;

    if (server.cluster_enabled) {
        addReplyError(c,"MOVE is not allowed in cluster mode");
        return;
    }

    /* Obtain source and target DB pointers */
    src = c->db;
    srcid = c->db->id;

    if (getLongLongFromObject(c->argv[2],&dbid) == C_ERR ||
        dbid < INT_MIN || dbid > INT_MAX ||
        selectDb(c,dbid) == C_ERR)
    {
        addReply(c,shared.outofrangeerr);
        return;
    }
    dst = c->db;
    selectDb(c,srcid); /* Back to the source DB */

    /* If the user is moving using as target the same
     * DB as the source DB it is probably an error. */
    if (src == dst) {
        addReply(c,shared.sameobjecterr);
        return;
    }

    /* Check if the element exists and get a reference */
    o = lookupKeyWrite(c->db,c->argv[1]);
    if (!o) {
        addReply(c,shared.czero);
        return;
    }
    expire = getExpire(c->db,c->argv[1]);

    /* Return zero if the key already exists in the target DB */
    if (lookupKeyWrite(dst,c->argv[1]) != NULL) {
        addReply(c,shared.czero);
        return;
    }
    dbAdd(dst,c->argv[1],o);
    if (expire != -1) setExpire(c,dst,c->argv[1],expire);
    incrRefCount(o);

    /* OK! key moved, free the entry in the source DB */
    dbDelete(src,c->argv[1]);
    server.dirty++;
    addReply(c,shared.cone);
}