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
typedef  int /*<<< orphan*/  guint32 ;
struct TYPE_9__ {TYPE_1__* data; struct TYPE_9__* next; } ;
struct TYPE_8__ {TYPE_3__* entries; } ;
struct TYPE_7__ {char const* id; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ SeafDir ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_GENERAL ; 
 int /*<<< orphan*/  SEAF_ERR_PATH_NO_EXIST ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  g_error_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_propagate_error (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  is_object_id_valid (char const*) ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_2__*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir_by_path (int /*<<< orphan*/ *,char const*,int,char const*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

char *
seaf_fs_manager_path_to_obj_id (SeafFSManager *mgr,
                                const char *repo_id,
                                int version,
                                const char *root_id,
                                const char *path,
                                guint32 *mode,
                                GError **error)
{
    char *copy = g_strdup (path);
    int off = strlen(copy) - 1;
    char *slash, *name;
    SeafDir *base_dir = NULL;
    SeafDirent *dent;
    GList *p;
    char *obj_id = NULL;

    while (off >= 0 && copy[off] == '/')
        copy[off--] = 0;

    if (strlen(copy) == 0) {
        /* the path is root "/" */
        if (mode) {
            *mode = S_IFDIR;
        }
        obj_id = g_strdup(root_id);
        goto out;
    }

    slash = strrchr (copy, '/');
    if (!slash) {
        base_dir = seaf_fs_manager_get_seafdir (mgr, repo_id, version, root_id);
        if (!base_dir) {
            seaf_warning ("Failed to find root dir %s.\n", root_id);
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL, " ");
            goto out;
        }
        name = copy;
    } else {
        *slash = 0;
        name = slash + 1;
        GError *tmp_error = NULL;
        base_dir = seaf_fs_manager_get_seafdir_by_path (mgr,
                                                        repo_id,
                                                        version,
                                                        root_id,
                                                        copy,
                                                        &tmp_error);
        if (tmp_error &&
            !g_error_matches(tmp_error,
                             SEAFILE_DOMAIN,
                             SEAF_ERR_PATH_NO_EXIST)) {
            seaf_warning ("Failed to get dir for %s.\n", copy);
            g_propagate_error (error, tmp_error);
            goto out;
        }

        /* The path doesn't exist in this commit. */
        if (!base_dir) {
            g_propagate_error (error, tmp_error);
            goto out;
        }
    }

    for (p = base_dir->entries; p != NULL; p = p->next) {
        dent = p->data;

        if (!is_object_id_valid (dent->id))
            continue;

        if (strcmp (dent->name, name) == 0) {
            obj_id = g_strdup (dent->id);
            if (mode) {
                *mode = dent->mode;
            }
            break;
        }
    }

out:
    if (base_dir)
        seaf_dir_free (base_dir);
    g_free (copy);
    return obj_id;
}