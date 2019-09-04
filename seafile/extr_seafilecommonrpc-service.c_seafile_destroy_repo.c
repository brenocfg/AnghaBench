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
typedef  int /*<<< orphan*/  SeafRepo ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int do_unsync_repo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_uuid_valid (char const*) ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 

int
seafile_destroy_repo (const char *repo_id, GError **error)
{
    if (!repo_id) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Argument should not be null");
        return -1;
    }
    if (!is_uuid_valid (repo_id)) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Invalid repo id");
        return -1;
    }

    SeafRepo *repo;

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "No such repository");
        return -1;
    }

    return do_unsync_repo(repo);
}