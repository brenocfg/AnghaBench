#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rdbSaveInfo ;
struct TYPE_2__ {int dirty; int rdb_child_pid; scalar_t__ saveparamslen; int /*<<< orphan*/  rdb_filename; } ;

/* Variables and functions */
 int EMPTYDB_ASYNC ; 
 scalar_t__ emptyDb (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jemalloc_purge () ; 
 int /*<<< orphan*/  killRDBChild () ; 
 int /*<<< orphan*/ * rdbPopulateSaveInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdbSave (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

void flushAllDataAndResetRDB(int flags) {
    server.dirty += emptyDb(-1,flags,NULL);
    if (server.rdb_child_pid != -1) killRDBChild();
    if (server.saveparamslen > 0) {
        /* Normally rdbSave() will reset dirty, but we don't want this here
         * as otherwise FLUSHALL will not be replicated nor put into the AOF. */
        int saved_dirty = server.dirty;
        rdbSaveInfo rsi, *rsiptr;
        rsiptr = rdbPopulateSaveInfo(&rsi);
        rdbSave(server.rdb_filename,rsiptr);
        server.dirty = saved_dirty;
    }
    server.dirty++;
#if defined(USE_JEMALLOC)
    /* jemalloc 5 doesn't release pages back to the OS when there's no traffic.
     * for large databases, flushdb blocks for long anyway, so a bit more won't
     * harm and this way the flush and purge will be synchroneus. */
    if (!(flags & EMPTYDB_ASYNC))
        jemalloc_purge();
#endif
}