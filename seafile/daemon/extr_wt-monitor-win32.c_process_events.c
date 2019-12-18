#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {scalar_t__ NextEntryOffset; } ;
struct TYPE_6__ {int /*<<< orphan*/  worktree; } ;
typedef  TYPE_1__ RepoWatchInfo ;
typedef  TYPE_2__* PFILE_NOTIFY_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  process_one_event (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static gboolean
process_events (const char *repo_id, RepoWatchInfo *info,
                char *event_buf, unsigned int buf_size)
{
    PFILE_NOTIFY_INFORMATION event;

    int offset = 0;
    while (1) {
        event = (PFILE_NOTIFY_INFORMATION)&event_buf[offset];
        offset += event->NextEntryOffset;

        process_one_event (info, info->worktree,
                           event, (event->NextEntryOffset == 0));

        if (!event->NextEntryOffset)
            break;
    }

    return TRUE;
}