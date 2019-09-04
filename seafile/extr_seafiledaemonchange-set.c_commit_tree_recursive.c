#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_16__ {int /*<<< orphan*/  fs_mgr; } ;
struct TYPE_15__ {int /*<<< orphan*/  version; int /*<<< orphan*/  dir_id; int /*<<< orphan*/  dents; } ;
struct TYPE_14__ {char* dir_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  id; TYPE_4__* subdir; } ;
typedef  TYPE_2__ SeafDir ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  TYPE_1__ ChangeSetDirent ;
typedef  TYPE_4__ ChangeSetDir ;

/* Variables and functions */
 TYPE_2__* changeset_dir_to_seaf_dir (TYPE_4__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__**) ; 
 char* g_strdup (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_7__* seaf ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_2__*) ; 
 scalar_t__ seaf_dir_save (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_fs_manager_object_exists (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,char const*) ; 

__attribute__((used)) static char *
commit_tree_recursive (const char *repo_id, ChangeSetDir *dir, gint64 *new_mtime)
{
    ChangeSetDirent *dent;
    GHashTableIter iter;
    gpointer key, value;
    char *new_id;
    gint64 subdir_new_mtime;
    gint64 dir_mtime = 0;
    SeafDir *seaf_dir;
    char *ret = NULL;

    g_hash_table_iter_init (&iter, dir->dents);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        dent = value;
        if (dent->subdir) {
            new_id = commit_tree_recursive (repo_id, dent->subdir, &subdir_new_mtime);
            if (!new_id)
                return NULL;

            memcpy (dent->id, new_id, 40);
            dent->mtime = subdir_new_mtime;
            g_free (new_id);
        }
        if (dir_mtime < dent->mtime)
            dir_mtime = dent->mtime;
    }

    seaf_dir = changeset_dir_to_seaf_dir (dir);

    memcpy (dir->dir_id, seaf_dir->dir_id, 40);

    if (!seaf_fs_manager_object_exists (seaf->fs_mgr,
                                        repo_id, dir->version,
                                        seaf_dir->dir_id)) {
        if (seaf_dir_save (seaf->fs_mgr, repo_id, dir->version, seaf_dir) < 0) {
            seaf_warning ("Failed to save dir object %s to repo %s.\n",
                          seaf_dir->dir_id, repo_id);
            goto out;
        }
    }

    ret = g_strdup(seaf_dir->dir_id);

out:
    if (ret != NULL)
        *new_mtime = dir_mtime;

    seaf_dir_free (seaf_dir);
    return ret;
}