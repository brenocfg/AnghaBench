#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SeafWTMonitor ;
typedef  int /*<<< orphan*/  FSEventStreamRef ;

/* Variables and functions */
 int /*<<< orphan*/  add_watch (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int
handle_add_repo (SeafWTMonitor *monitor, const char *repo_id, const char *worktree)
{
    FSEventStreamRef stream = add_watch (monitor, repo_id, worktree);
    if (!stream)
        return -1;
    return 0;
}