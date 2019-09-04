#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_13__ {int /*<<< orphan*/  new_name; int /*<<< orphan*/  name; int /*<<< orphan*/  status; } ;
struct TYPE_12__ {TYPE_2__* data; struct TYPE_12__* next; } ;
typedef  int /*<<< orphan*/  SeafileDiffEntry ;
typedef  int /*<<< orphan*/  SeafRepo ;
typedef  TYPE_1__ GList ;
typedef  int /*<<< orphan*/  GError ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAFILE_TYPE_DIFF_ENTRY ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  diff_entry_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 
 TYPE_1__* g_list_prepend (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* g_list_reverse (TYPE_1__*) ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  get_diff_status_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_id_valid (char const*) ; 
 int /*<<< orphan*/  is_uuid_valid (char const*) ; 
 TYPE_5__* seaf ; 
 TYPE_1__* seaf_repo_diff (int /*<<< orphan*/ *,char const*,char const*,int,char**) ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 

GList *
seafile_diff (const char *repo_id, const char *arg1, const char *arg2, int fold_dir_diff, GError **error)
{
    SeafRepo *repo;
    char *err_msgs = NULL;
    GList *diff_entries, *p;
    GList *ret = NULL;

    if (!repo_id || !arg1 || !arg2) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Argument should not be null");
        return NULL;
    }

    if (!is_uuid_valid (repo_id)) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Invalid repo id");
        return NULL;
    }

    if ((arg1[0] != 0 && !is_object_id_valid (arg1)) || !is_object_id_valid(arg2)) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Invalid commit id");
        return NULL;
    }

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "No such repository");
        return NULL;
    }

    diff_entries = seaf_repo_diff (repo, arg1, arg2, fold_dir_diff, &err_msgs);
    if (err_msgs) {
        g_set_error (error, SEAFILE_DOMAIN, -1, "%s", err_msgs);
        g_free (err_msgs);
        return NULL;
    }

    for (p = diff_entries; p != NULL; p = p->next) {
        DiffEntry *de = p->data;
        SeafileDiffEntry *entry = g_object_new (
            SEAFILE_TYPE_DIFF_ENTRY,
            "status", get_diff_status_str(de->status),
            "name", de->name,
            "new_name", de->new_name,
            NULL);
        ret = g_list_prepend (ret, entry);
    }

    for (p = diff_entries; p != NULL; p = p->next) {
        DiffEntry *de = p->data;
        diff_entry_free (de);
    }
    g_list_free (diff_entries);

    return g_list_reverse (ret);
}