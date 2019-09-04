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
typedef  char gchar ;
struct TYPE_5__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_REPO ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* seaf ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 char* seaf_repo_manager_get_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

gchar *
seafile_get_repo_property (const char *repo_id,
                           const char *key,
                           GError **error)
{
    char *value = NULL;

    if (!repo_id || !key) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Arguments should not be empty");
        return NULL;
    }

    SeafRepo *repo;
    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_REPO, "Can't find Repo %s", repo_id);
        return NULL;
    }

    value = seaf_repo_manager_get_repo_property (seaf->repo_mgr, repo->id, key);
    return value;
}