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
 int /*<<< orphan*/ * convert_repo_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_repo_list (int /*<<< orphan*/ ,int,int) ; 

GList*
seafile_get_repo_list (int start, int limit, GError **error)
{
    GList *repos = seaf_repo_manager_get_repo_list(seaf->repo_mgr, start, limit);
    GList *ret = NULL;

    ret = convert_repo_list (repos);

    g_list_free (repos);

    return ret;
}