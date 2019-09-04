#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  clone_mgr; } ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 TYPE_1__* seaf ; 
 int seaf_clone_manager_cancel_task (int /*<<< orphan*/ ,char const*) ; 

int
seafile_cancel_clone_task (const char *repo_id, GError **error)
{
    return seaf_clone_manager_cancel_task (seaf->clone_mgr, repo_id);
}