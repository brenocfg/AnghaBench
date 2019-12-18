#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  procfs_list; } ;
typedef  TYPE_1__ spa_history_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  procfs_list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfs_list_uninstall (int /*<<< orphan*/ *) ; 
 TYPE_1__* spa_import_progress_list ; 
 int /*<<< orphan*/  spa_import_progress_truncate (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_import_progress_destroy(void)
{
	spa_history_list_t *shl = spa_import_progress_list;
	procfs_list_uninstall(&shl->procfs_list);
	spa_import_progress_truncate(shl, 0);
	procfs_list_destroy(&shl->procfs_list);
	kmem_free(shl, sizeof (spa_history_list_t));
}