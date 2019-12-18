#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* pl_private; } ;
struct TYPE_9__ {TYPE_6__ procfs_list; scalar_t__ size; } ;
struct TYPE_7__ {TYPE_3__ read_history; } ;
struct TYPE_8__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_2__ spa_t ;
typedef  TYPE_3__ spa_history_list_t ;

/* Variables and functions */
 char* kmem_asprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_list_install (char*,char*,int,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_read_history_clear ; 
 int /*<<< orphan*/  spa_read_history_show ; 
 int /*<<< orphan*/  spa_read_history_show_header ; 
 int /*<<< orphan*/  spa_read_history_t ; 
 int /*<<< orphan*/  srh_node ; 

__attribute__((used)) static void
spa_read_history_init(spa_t *spa)
{
	spa_history_list_t *shl = &spa->spa_stats.read_history;
	char *module;

	shl->size = 0;

	module = kmem_asprintf("zfs/%s", spa_name(spa));

	shl->procfs_list.pl_private = shl;
	procfs_list_install(module,
	    "reads",
	    0600,
	    &shl->procfs_list,
	    spa_read_history_show,
	    spa_read_history_show_header,
	    spa_read_history_clear,
	    offsetof(spa_read_history_t, srh_node));

	kmem_strfree(module);
}