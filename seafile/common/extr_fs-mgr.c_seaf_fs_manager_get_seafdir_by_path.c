#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* data; struct TYPE_9__* next; } ;
struct TYPE_8__ {TYPE_3__* entries; } ;
struct TYPE_7__ {char* id; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ SeafDir ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_DIR_MISSING ; 
 int /*<<< orphan*/  SEAF_ERR_PATH_NO_EXIST ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_2__*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

SeafDir *
seaf_fs_manager_get_seafdir_by_path (SeafFSManager *mgr,
                                     const char *repo_id,
                                     int version,
                                     const char *root_id,
                                     const char *path,
                                     GError **error)
{
    SeafDir *dir;
    SeafDirent *dent;
    const char *dir_id = root_id;
    char *name, *saveptr;
    char *tmp_path = g_strdup(path);

    dir = seaf_fs_manager_get_seafdir (mgr, repo_id, version, dir_id);
    if (!dir) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_DIR_MISSING, "directory is missing");
        g_free (tmp_path);
        return NULL;
    }

    name = strtok_r (tmp_path, "/", &saveptr);
    while (name != NULL) {
        GList *l;
        for (l = dir->entries; l != NULL; l = l->next) {
            dent = l->data;

            if (strcmp(dent->name, name) == 0 && S_ISDIR(dent->mode)) {
                dir_id = dent->id;
                break;
            }
        }

        if (!l) {
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_PATH_NO_EXIST,
                         "Path does not exists %s", path);
            seaf_dir_free (dir);
            dir = NULL;
            break;
        }

        SeafDir *prev = dir;
        dir = seaf_fs_manager_get_seafdir (mgr, repo_id, version, dir_id);
        seaf_dir_free (prev);

        if (!dir) {
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_DIR_MISSING,
                         "directory is missing");
            break;
        }

        name = strtok_r (NULL, "/", &saveptr);
    }

    g_free (tmp_path);
    return dir;
}