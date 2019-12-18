#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  fs_mgr; } ;
struct TYPE_21__ {char* repo_id; TYPE_2__* tree_root; } ;
struct TYPE_20__ {int /*<<< orphan*/  dents_i; int /*<<< orphan*/  version; int /*<<< orphan*/  dents; } ;
struct TYPE_19__ {char* name; int /*<<< orphan*/  mode; TYPE_2__* subdir; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SeafStat ;
typedef  int /*<<< orphan*/  SeafDir ;
typedef  TYPE_1__ ChangeSetDirent ;
typedef  TYPE_2__ ChangeSetDir ;
typedef  TYPE_3__ ChangeSet ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_dent_to_dir (TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* create_intermediate_dir (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  create_new_dent (TYPE_2__*,char*,unsigned char*,int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_1__* g_hash_table_lookup (int /*<<< orphan*/ ,char*) ; 
 char* g_strdup (char*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char** g_strsplit (char const*,char*,int /*<<< orphan*/ ) ; 
 int g_strv_length (char**) ; 
 char* g_utf8_strdown (char*,int) ; 
 int /*<<< orphan*/  handle_case_conflict (TYPE_3__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  remove_dent_from_dir (TYPE_2__*,char*) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_dir_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* seaf_dir_to_changeset_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_fs_manager_get_seafdir (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_file (TYPE_1__*,unsigned char*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
add_to_tree (ChangeSet *changeset,
             unsigned char *sha1,
             SeafStat *st,
             const char *modifier,
             const char *path,
             ChangeSetDirent *new_dent)
{
    char *repo_id = changeset->repo_id;
    ChangeSetDir *root = changeset->tree_root;
    char **parts, *dname;
    int n, i;
    ChangeSetDir *dir;
    ChangeSetDirent *dent;
    SeafDir *seaf_dir;

    parts = g_strsplit (path, "/", 0);
    n = g_strv_length(parts);
    dir = root;
    for (i = 0; i < n; i++) {
#if defined WIN32 || defined __APPLE__
    try_again:
#endif
        dname = parts[i];
        dent = g_hash_table_lookup (dir->dents, dname);

        if (dent) {
            if (S_ISDIR(dent->mode)) {
                if (i == (n-1))
                    /* Don't need to update empty dir */
                    break;

                if (!dent->subdir) {
                    seaf_dir = seaf_fs_manager_get_seafdir(seaf->fs_mgr,
                                                           repo_id,
                                                           root->version,
                                                           dent->id);
                    if (!seaf_dir) {
                        seaf_warning ("Failed to load seafdir %s:%s\n",
                                      repo_id, dent->id);
                        break;
                    }
                    dent->subdir = seaf_dir_to_changeset_dir (seaf_dir);
                    seaf_dir_free (seaf_dir);
                }
                dir = dent->subdir;
            } else if (S_ISREG(dent->mode)) {
                if (i == (n-1)) {
                    /* File exists, update it. */
                    update_file (dent, sha1, st, modifier);
                    break;
                }
            }
        } else {
#if defined WIN32 || defined __APPLE__
            /* Only effective for add operation, not applicable to rename. */
            if (!new_dent) {
                char *search_key = g_utf8_strdown (dname, -1);
                dent = g_hash_table_lookup (dir->dents_i, search_key);
                g_free (search_key);
                if (dent) {
                    remove_dent_from_dir (dir, dent->name);

                    g_free (dent->name);
                    dent->name = g_strdup(dname);
                    add_dent_to_dir (dir, dent);

                    goto try_again;
                }

                handle_case_conflict (changeset, dir, dname);
            }
#endif

            if (i == (n-1)) {
                create_new_dent (dir, dname, sha1, st, modifier, new_dent);
            } else {
                dir = create_intermediate_dir (dir, dname);
            }
        }
    }

    g_strfreev (parts);
}