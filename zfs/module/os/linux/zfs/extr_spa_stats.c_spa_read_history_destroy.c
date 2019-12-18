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
struct TYPE_8__ {int /*<<< orphan*/  procfs_list; } ;
struct TYPE_6__ {TYPE_3__ read_history; } ;
struct TYPE_7__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_2__ spa_t ;
typedef  TYPE_3__ spa_history_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  procfs_list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfs_list_uninstall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_read_history_truncate (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_read_history_destroy(spa_t *spa)
{
	spa_history_list_t *shl = &spa->spa_stats.read_history;
	procfs_list_uninstall(&shl->procfs_list);
	spa_read_history_truncate(shl, 0);
	procfs_list_destroy(&shl->procfs_list);
}