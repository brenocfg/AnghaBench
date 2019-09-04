#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_15__ {TYPE_2__* db; int /*<<< orphan*/ ** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_18__ {int /*<<< orphan*/  dirty; scalar_t__ lazyfree_lazy_expire; int /*<<< orphan*/  masterhost; int /*<<< orphan*/  loading; } ;
struct TYPE_17__ {int /*<<< orphan*/  cone; int /*<<< orphan*/ * del; int /*<<< orphan*/ * unlink; int /*<<< orphan*/  czero; } ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int UNIT_SECONDS ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dbAsyncDelete (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int dbSyncDelete (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_1__*,int /*<<< orphan*/ *,long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyWrite (TYPE_2__*,int /*<<< orphan*/ *) ; 
 long long mstime () ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteClientCommandVector (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setExpire (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,long long) ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_2__*,int /*<<< orphan*/ *) ; 

void expireGenericCommand(client *c, long long basetime, int unit) {
    robj *key = c->argv[1], *param = c->argv[2];
    long long when; /* unix time in milliseconds when the key will expire. */

    if (getLongLongFromObjectOrReply(c, param, &when, NULL) != C_OK)
        return;

    if (unit == UNIT_SECONDS) when *= 1000;
    when += basetime;

    /* No key, return zero. */
    if (lookupKeyWrite(c->db,key) == NULL) {
        addReply(c,shared.czero);
        return;
    }

    /* EXPIRE with negative TTL, or EXPIREAT with a timestamp into the past
     * should never be executed as a DEL when load the AOF or in the context
     * of a slave instance.
     *
     * Instead we take the other branch of the IF statement setting an expire
     * (possibly in the past) and wait for an explicit DEL from the master. */
    if (when <= mstime() && !server.loading && !server.masterhost) {
        robj *aux;

        int deleted = server.lazyfree_lazy_expire ? dbAsyncDelete(c->db,key) :
                                                    dbSyncDelete(c->db,key);
        serverAssertWithInfo(c,key,deleted);
        server.dirty++;

        /* Replicate/AOF this as an explicit DEL or UNLINK. */
        aux = server.lazyfree_lazy_expire ? shared.unlink : shared.del;
        rewriteClientCommandVector(c,2,aux,key);
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
        addReply(c, shared.cone);
        return;
    } else {
        setExpire(c,c->db,key,when);
        addReply(c,shared.cone);
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent(NOTIFY_GENERIC,"expire",key,c->db->id);
        server.dirty++;
        return;
    }
}