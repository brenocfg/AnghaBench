#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ SeafWTMonitor ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  add_handle_to_iocp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * add_watch (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static int handle_add_repo (SeafWTMonitor *monitor,
                            const char *repo_id,
                            const char *worktree)
{
    HANDLE handle;

    handle = add_watch (monitor->priv, repo_id, worktree);
    if (handle == NULL ||
        !add_handle_to_iocp(monitor, handle)) {
        return -1;
    }

    return 0;
}