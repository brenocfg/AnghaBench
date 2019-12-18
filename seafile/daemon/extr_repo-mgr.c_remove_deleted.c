#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct index_state {unsigned int cache_nr; struct cache_entry** cache; } ;
struct TYPE_5__ {scalar_t__ sec; } ;
struct cache_entry {char* name; int /*<<< orphan*/  ce_flags; TYPE_1__ ce_ctime; int /*<<< orphan*/  ce_mode; } ;
typedef  scalar_t__ gboolean ;
struct TYPE_7__ {int /*<<< orphan*/  filelock_mgr; } ;
struct TYPE_6__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__ SeafStat ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */
 int /*<<< orphan*/  CE_REMOVE ; 
 int /*<<< orphan*/  DIFF_STATUS_DELETED ; 
 int /*<<< orphan*/  DIFF_STATUS_DIR_DELETED ; 
 scalar_t__ ENOENT ; 
 scalar_t__ FALSE ; 
 int SEAF_PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ ce_stage (struct cache_entry*) ; 
 scalar_t__ check_locked_file_before_remove (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_empty_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_path_writable (char const*,scalar_t__,char*) ; 
 int /*<<< orphan*/  remove_from_changeset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  remove_marked_cache_entries (struct index_state*) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_debug (char*,char*) ; 
 scalar_t__ seaf_filelock_manager_is_file_locked (int /*<<< orphan*/ ,char const*,char*) ; 
 int seaf_stat (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
remove_deleted (struct index_state *istate, const char *worktree, const char *prefix,
                GList *ignore_list, LockedFileSet *fset,
                const char *repo_id, gboolean is_repo_ro,
                ChangeSet *changeset)
{
    struct cache_entry **ce_array = istate->cache;
    struct cache_entry *ce;
    char path[SEAF_PATH_MAX];
    unsigned int i;
    SeafStat st;
    int ret;
    gboolean not_exist;

    char *full_prefix = g_strconcat (prefix, "/", NULL);
    int len = strlen(full_prefix);

    for (i = 0; i < istate->cache_nr; ++i) {
        ce = ce_array[i];

        if (!is_path_writable (repo_id, is_repo_ro, ce->name))
            continue;

        if (seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                                  repo_id, ce->name)) {
            seaf_debug ("Remove deleted: %s is locked on server, ignore.\n", ce->name);
            continue;
        }

        if (prefix[0] != 0 && strcmp (ce->name, prefix) != 0 &&
            strncmp (ce->name, full_prefix, len) != 0)
            continue;

        snprintf (path, SEAF_PATH_MAX, "%s/%s", worktree, ce->name);
        not_exist = FALSE;
        ret = seaf_stat (path, &st);
        if (ret < 0 && errno == ENOENT)
            not_exist = TRUE;

        if (S_ISDIR (ce->ce_mode)) {
            if (ce->ce_ctime.sec != 0 || ce_stage(ce) != 0) {
                if (not_exist || (ret == 0 && !S_ISDIR (st.st_mode))) {
                    /* Add to changeset only if dir is removed. */
                    ce->ce_flags |= CE_REMOVE;
                    if (changeset)
                        /* Remove the parent dir from change set if it becomes
                         * empty. If in the work tree the empty dir still exist,
                         * we'll add it back to changeset in add_recursive() later.
                         */
                        remove_from_changeset (changeset,
                                               DIFF_STATUS_DIR_DELETED,
                                               ce->name,
                                               TRUE,
                                               prefix);
                } else if (!is_empty_dir (path, ignore_list)) {
                    /* Don't add to changeset if empty dir became non-empty. */
                    ce->ce_flags |= CE_REMOVE;
                }
            }
        } else {
            /* If ce->ctime is 0 and stage is 0, it was not successfully checked out.
             * In this case we don't want to mistakenly remove the file
             * from the repo.
             */
            if ((not_exist || (ret == 0 && !S_ISREG (st.st_mode))) &&
                (ce->ce_ctime.sec != 0 || ce_stage(ce) != 0) &&
                check_locked_file_before_remove (fset, ce->name))
            {
                ce_array[i]->ce_flags |= CE_REMOVE;
                if (changeset)
                    remove_from_changeset (changeset,
                                           DIFF_STATUS_DELETED,
                                           ce->name,
                                           TRUE,
                                           prefix);
            }
        }
    }

    remove_marked_cache_entries (istate);

    g_free (full_prefix);
}