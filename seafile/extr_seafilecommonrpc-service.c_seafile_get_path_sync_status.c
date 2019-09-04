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
struct TYPE_2__ {int /*<<< orphan*/  sync_mgr; } ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* g_strdup (char const*) ; 
 TYPE_1__* seaf ; 
 char* seaf_sync_manager_get_path_sync_status (int /*<<< orphan*/ ,char const*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 

char *
seafile_get_path_sync_status (const char *repo_id,
                              const char *path,
                              int is_dir,
                              GError **error)
{
    char *canon_path = NULL;
    int len;
    char *status;

    if (!repo_id || !path) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Argument should not be null");
        return NULL;
    }

    /* Empty path means to get status of the worktree folder. */
    if (strcmp (path, "") != 0) {
        if (*path == '/')
            ++path;
        canon_path = g_strdup(path);
        len = strlen(canon_path);
        if (canon_path[len-1] == '/')
            canon_path[len-1] = 0;
    } else {
        canon_path = g_strdup(path);
    }

    status = seaf_sync_manager_get_path_sync_status (seaf->sync_mgr,
                                                     repo_id,
                                                     canon_path,
                                                     is_dir);
    g_free (canon_path);
    return status;
}