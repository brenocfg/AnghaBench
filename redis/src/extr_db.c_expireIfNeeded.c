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
typedef  int /*<<< orphan*/  robj ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ redisDb ;
struct TYPE_9__ {scalar_t__ lazyfree_lazy_expire; int /*<<< orphan*/  stat_expiredkeys; int /*<<< orphan*/ * masterhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_EXPIRED ; 
 int dbAsyncDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int dbSyncDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyIsExpired (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagateExpire (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__ server ; 

int expireIfNeeded(redisDb *db, robj *key) {
    if (!keyIsExpired(db,key)) return 0;

    /* If we are running in the context of a slave, instead of
     * evicting the expired key from the database, we return ASAP:
     * the slave key expiration is controlled by the master that will
     * send us synthesized DEL operations for expired keys.
     *
     * Still we try to return the right information to the caller,
     * that is, 0 if we think the key should be still valid, 1 if
     * we think the key is expired at this time. */
    if (server.masterhost != NULL) return 1;

    /* Delete the key */
    server.stat_expiredkeys++;
    propagateExpire(db,key,server.lazyfree_lazy_expire);
    notifyKeyspaceEvent(NOTIFY_EXPIRED,
        "expired",key,db->id);
    return server.lazyfree_lazy_expire ? dbAsyncDelete(db,key) :
                                         dbSyncDelete(db,key);
}