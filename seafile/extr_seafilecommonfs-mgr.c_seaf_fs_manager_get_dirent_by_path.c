#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* data; struct TYPE_12__* next; } ;
struct TYPE_11__ {TYPE_3__* entries; } ;
struct TYPE_10__ {char* name; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ SeafDir ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_DIR_MISSING ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_basename (char const*) ; 
 char* g_path_get_dirname (char const*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_2__*) ; 
 TYPE_1__* seaf_dirent_dup (TYPE_1__*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir_by_path (int /*<<< orphan*/ *,char const*,int,char const*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 

SeafDirent *
seaf_fs_manager_get_dirent_by_path (SeafFSManager *mgr,
                                    const char *repo_id,
                                    int version,
                                    const char *root_id,
                                    const char *path,
                                    GError **error)
{
    SeafDirent *dent = NULL;
    SeafDir *dir = NULL;
    char *parent_dir = NULL;
    char *file_name = NULL;

    parent_dir  = g_path_get_dirname(path);
    file_name = g_path_get_basename(path);

    if (strcmp (parent_dir, ".") == 0) {
        dir = seaf_fs_manager_get_seafdir (mgr, repo_id, version, root_id);
        if (!dir) {
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_DIR_MISSING, "directory is missing");
        }
    } else
        dir = seaf_fs_manager_get_seafdir_by_path (mgr, repo_id, version,
                                                   root_id, parent_dir, error);

    if (!dir) {
        seaf_warning ("dir %s doesn't exist in repo %.8s.\n", parent_dir, repo_id);
        goto out;
    }

    GList *p;
    for (p = dir->entries; p; p = p->next) {
        SeafDirent *d = p->data;
        if (strcmp (d->name, file_name) == 0) {
            dent = seaf_dirent_dup(d);
            break;
        }
    }

out:
    if (dir)
        seaf_dir_free (dir);
    g_free (parent_dir);
    g_free (file_name);

    return dent;
}