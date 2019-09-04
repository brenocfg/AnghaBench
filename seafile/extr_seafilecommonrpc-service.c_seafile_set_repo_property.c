#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_REPO ; 
 int /*<<< orphan*/  SEAF_ERR_INTERNAL ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* seaf ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 int seaf_repo_manager_set_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 

int
seafile_set_repo_property (const char *repo_id,
                           const char *key,
                           const char *value,
                           GError **error)
{
    int ret;

    if (repo_id == NULL || key == NULL || value == NULL) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Arguments should not be empty");
        return -1;
    }

    SeafRepo *repo;
    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_REPO, "Can't find Repo %s", repo_id);
        return -1;
    }

    ret = seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                               repo->id, key, value);
    if (ret < 0) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_INTERNAL,
                     "Failed to set key for repo %s", repo_id);
        return -1;
    }

    return 0;
}