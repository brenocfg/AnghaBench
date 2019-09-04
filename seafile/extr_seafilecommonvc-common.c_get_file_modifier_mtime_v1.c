#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_14__ {int /*<<< orphan*/  fs_mgr; int /*<<< orphan*/  commit_mgr; } ;
struct TYPE_13__ {TYPE_1__* data; struct TYPE_13__* next; } ;
struct TYPE_12__ {int /*<<< orphan*/  root_id; } ;
struct TYPE_11__ {TYPE_4__* entries; } ;
struct TYPE_10__ {char* name; char* modifier; int /*<<< orphan*/  mtime; } ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ SeafDir ;
typedef  TYPE_3__ SeafCommit ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_basename (char const*) ; 
 char* g_path_get_dirname (char const*) ; 
 char* g_strdup (char*) ; 
 TYPE_9__* seaf ; 
 TYPE_3__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,char const*,int,char const*) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_2__*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir_by_path (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
get_file_modifier_mtime_v1 (const char *repo_id, const char *store_id, int version,
                            const char *head, const char *path,
                            char **modifier, gint64 *mtime)
{
    SeafCommit *commit = NULL;
    SeafDir *dir = NULL;
    SeafDirent *dent = NULL;
    int ret = 0;

    commit = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                             repo_id, version,
                                             head);
    if (!commit) {
        seaf_warning ("Failed to get commit %s.\n", head);
        return -1;
    }

    char *parent = g_path_get_dirname (path);
    if (strcmp(parent, ".") == 0) {
        g_free (parent);
        parent = g_strdup("");
    }
    char *filename = g_path_get_basename (path);

    dir = seaf_fs_manager_get_seafdir_by_path (seaf->fs_mgr,
                                               store_id, version,
                                               commit->root_id,
                                               parent, NULL);
    if (!dir) {
        seaf_warning ("dir %s doesn't exist in repo %s.\n", parent, repo_id);
        ret = -1;
        goto out;
    }

    GList *p;
    for (p = dir->entries; p; p = p->next) {
        SeafDirent *d = p->data;
        if (strcmp (d->name, filename) == 0) {
            dent = d;
            break;
        }
    }

    if (!dent) {
        goto out;
    }

    *modifier = g_strdup(dent->modifier);
    *mtime = dent->mtime;

out:
    g_free (parent);
    g_free (filename);
    seaf_commit_unref (commit);
    seaf_dir_free (dir);

    return ret;
}