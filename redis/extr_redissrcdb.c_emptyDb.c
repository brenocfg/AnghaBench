#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  expires; int /*<<< orphan*/  dict; } ;
struct TYPE_3__ {int dbnum; scalar_t__ cluster_enabled; TYPE_2__* db; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int EMPTYDB_ASYNC ; 
 int /*<<< orphan*/  dictEmpty (int /*<<< orphan*/ ,void (*) (void*)) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emptyDbAsync (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  flushSlaveKeysWithExpireList () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  slotToKeyFlush () ; 
 int /*<<< orphan*/  slotToKeyFlushAsync () ; 

long long emptyDb(int dbnum, int flags, void(callback)(void*)) {
    int async = (flags & EMPTYDB_ASYNC);
    long long removed = 0;

    if (dbnum < -1 || dbnum >= server.dbnum) {
        errno = EINVAL;
        return -1;
    }

    int startdb, enddb;
    if (dbnum == -1) {
        startdb = 0;
        enddb = server.dbnum-1;
    } else {
        startdb = enddb = dbnum;
    }

    for (int j = startdb; j <= enddb; j++) {
        removed += dictSize(server.db[j].dict);
        if (async) {
            emptyDbAsync(&server.db[j]);
        } else {
            dictEmpty(server.db[j].dict,callback);
            dictEmpty(server.db[j].expires,callback);
        }
    }
    if (server.cluster_enabled) {
        if (async) {
            slotToKeyFlushAsync();
        } else {
            slotToKeyFlush();
        }
    }
    if (dbnum == -1) flushSlaveKeysWithExpireList();
    return removed;
}