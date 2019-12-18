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

/* Variables and functions */
 int /*<<< orphan*/  create_upper_paths_hook ; 
 int /*<<< orphan*/  get_relation_info_hook ; 
 int /*<<< orphan*/  planner_hook ; 
 int /*<<< orphan*/  prev_create_upper_paths_hook ; 
 int /*<<< orphan*/  prev_get_relation_info_hook ; 
 int /*<<< orphan*/  prev_planner_hook ; 
 int /*<<< orphan*/  prev_set_rel_pathlist_hook ; 
 int /*<<< orphan*/  set_rel_pathlist_hook ; 

void
_planner_fini(void)
{
	planner_hook = prev_planner_hook;
	set_rel_pathlist_hook = prev_set_rel_pathlist_hook;
	get_relation_info_hook = prev_get_relation_info_hook;
	create_upper_paths_hook = prev_create_upper_paths_hook;
}