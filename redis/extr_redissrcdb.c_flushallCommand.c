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
typedef  int /*<<< orphan*/  rdbSaveInfo ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_4__ {int dirty; int rdb_child_pid; scalar_t__ saveparamslen; int /*<<< orphan*/  rdb_filename; } ;
struct TYPE_3__ {int /*<<< orphan*/  ok; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  addReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ emptyDb (int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ getFlushCommandFlags (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  killRDBChild () ; 
 int /*<<< orphan*/ * rdbPopulateSaveInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdbSave (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 
 TYPE_1__ shared ; 
 int /*<<< orphan*/  signalFlushedDb (int) ; 

void flushallCommand(client *c) {
    int flags;

    if (getFlushCommandFlags(c,&flags) == C_ERR) return;
    signalFlushedDb(-1);
    server.dirty += emptyDb(-1,flags,NULL);
    addReply(c,shared.ok);
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
}