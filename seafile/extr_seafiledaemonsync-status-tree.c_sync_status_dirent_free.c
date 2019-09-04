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
struct TYPE_4__ {int /*<<< orphan*/  subdir; struct TYPE_4__* name; } ;
typedef  TYPE_1__ SyncStatusDirent ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sync_status_dir_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sync_status_dirent_free (SyncStatusDirent *dirent)
{
    if (!dirent)
        return;
    g_free (dirent->name);
    sync_status_dir_free (dirent->subdir);
    g_free (dirent);
}