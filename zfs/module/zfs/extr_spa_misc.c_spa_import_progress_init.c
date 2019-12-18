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
typedef  int /*<<< orphan*/  spa_history_list_t ;
struct TYPE_5__ {TYPE_1__* pl_private; } ;
struct TYPE_4__ {TYPE_2__ procfs_list; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_list_install (char*,char*,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smh_node ; 
 TYPE_1__* spa_import_progress_list ; 
 int /*<<< orphan*/  spa_import_progress_show ; 
 int /*<<< orphan*/  spa_import_progress_show_header ; 
 int /*<<< orphan*/  spa_import_progress_t ; 

__attribute__((used)) static void
spa_import_progress_init(void)
{
	spa_import_progress_list = kmem_zalloc(sizeof (spa_history_list_t),
	    KM_SLEEP);

	spa_import_progress_list->size = 0;

	spa_import_progress_list->procfs_list.pl_private =
	    spa_import_progress_list;

	procfs_list_install("zfs",
	    "import_progress",
	    0644,
	    &spa_import_progress_list->procfs_list,
	    spa_import_progress_show,
	    spa_import_progress_show_header,
	    NULL,
	    offsetof(spa_import_progress_t, smh_node));
}