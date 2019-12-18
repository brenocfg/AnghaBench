#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_8__ {int /*<<< orphan*/  worktree; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  info_hash; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;
typedef  TYPE_2__ SeafWTMonitor ;
typedef  TYPE_3__ RepoWatchInfo ;
typedef  int /*<<< orphan*/  FSEventStreamEventId ;
typedef  int /*<<< orphan*/  FSEventStreamEventFlags ;
typedef  scalar_t__ ConstFSEventStreamRef ;

/* Variables and functions */
 scalar_t__ CFRunLoopGetCurrent () ; 
 TYPE_3__* g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_one_event (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  seaf_debug (char*,long,int /*<<< orphan*/  const,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

__attribute__((used)) static void
stream_callback (ConstFSEventStreamRef streamRef,
                      void *clientCallBackInfo,
                      size_t numEvents,
                      void *eventPaths,
                      const FSEventStreamEventFlags eventFlags[],
                      const FSEventStreamEventId eventIds[])
{
    RepoWatchInfo *info;
    SeafWTMonitor *monitor = (SeafWTMonitor *)clientCallBackInfo;
    SeafWTMonitorPriv *priv = monitor->priv;
    char **paths = (char **)eventPaths;

    info = g_hash_table_lookup (priv->info_hash, (gpointer)(long)streamRef);
    if (!info) {
        seaf_warning ("Repo watch info not found.\n");
        return;
    }

    int i;
    for (i = 0; i < numEvents; i++) {
        seaf_debug("%ld Change %llu in %s, flags %x\n", (long)CFRunLoopGetCurrent(),
                   eventIds[i], paths[i], eventFlags[i]);
        process_one_event (paths[i], info, info->worktree,
                           eventIds[i], eventFlags[i]);
    }
}