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
struct TYPE_2__ {int /*<<< orphan*/  filelock_mgr; } ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* g_strdup (char const*) ; 
 TYPE_1__* seaf ; 
 int seaf_filelock_manager_mark_file_unlocked (int /*<<< orphan*/ ,char const*,char const*) ; 
 int strlen (char*) ; 

int
seafile_mark_file_unlocked (const char *repo_id, const char *path, GError **error)
{
    char *canon_path = NULL;
    int len;
    int ret;

    if (!repo_id || !path) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Argument should not be null");
        return -1;
    }

    if (*path == '/')
        ++path;

    if (path[0] == 0) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Invalid path");
        return -1;
    }

    canon_path = g_strdup(path);
    len = strlen(canon_path);
    if (canon_path[len-1] == '/')
        canon_path[len-1] = 0;

    ret = seaf_filelock_manager_mark_file_unlocked (seaf->filelock_mgr,
                                                    repo_id, path);

    g_free (canon_path);
    return ret;
}