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
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * token; } ;
typedef  int /*<<< orphan*/  SeafRepoManager ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  REPO_PROP_TOKEN ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_repo_manager_del_repo_property_by_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
seaf_repo_manager_remove_repo_token (SeafRepoManager *manager,
                                     SeafRepo *repo)
{
    g_free (repo->token);
    repo->token = NULL;
    seaf_repo_manager_del_repo_property_by_key(manager, repo->id, REPO_PROP_TOKEN);
    return 0;
}