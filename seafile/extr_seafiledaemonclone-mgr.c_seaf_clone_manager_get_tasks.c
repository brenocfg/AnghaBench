#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tasks; } ;
typedef  TYPE_1__ SeafCloneManager ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/ * g_hash_table_get_values (int /*<<< orphan*/ ) ; 

GList *
seaf_clone_manager_get_tasks (SeafCloneManager *mgr)
{
    return g_hash_table_get_values (mgr->tasks);
}