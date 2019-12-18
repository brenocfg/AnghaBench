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
struct TYPE_2__ {int /*<<< orphan*/  repo_mgr; } ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 TYPE_1__* seaf ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_file_sync_errors (int /*<<< orphan*/ ,int,int) ; 

GList *
seafile_get_file_sync_errors (int offset, int limit, GError **error)
{
    return seaf_repo_manager_get_file_sync_errors (seaf->repo_mgr, offset, limit);
}