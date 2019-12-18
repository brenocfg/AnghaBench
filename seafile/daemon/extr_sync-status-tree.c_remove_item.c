#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dirents; } ;
typedef  TYPE_1__ SyncStatusDir ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* seaf ; 
 int /*<<< orphan*/  seaf_sync_manager_add_refresh_path (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
remove_item (SyncStatusDir *dir, const char *dname, const char *fullpath)
{
    g_hash_table_remove (dir->dirents, dname);
#ifdef WIN32
    seaf_sync_manager_add_refresh_path (seaf->sync_mgr, fullpath);
#endif
}