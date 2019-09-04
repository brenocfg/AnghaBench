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
struct index_state {int cache_changed; } ;
struct TYPE_7__ {scalar_t__ sec; } ;
struct cache_entry {unsigned int ce_mode; int /*<<< orphan*/  sha1; TYPE_1__ ce_mtime; } ;
struct TYPE_9__ {int /*<<< orphan*/  email; int /*<<< orphan*/ * changeset; } ;
struct TYPE_8__ {scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__ SeafStat ;
typedef  TYPE_3__ SeafRepo ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_MODIFIED ; 
 int /*<<< orphan*/  add_to_changeset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 unsigned int create_ce_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 struct cache_entry* index_name_exists (struct index_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_stat (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
update_attributes (SeafRepo *repo,
                   struct index_state *istate,
                   const char *worktree,
                   const char *path)
{
    ChangeSet *changeset = repo->changeset;
    char *full_path;
    struct cache_entry *ce;
    SeafStat st;

    ce = index_name_exists (istate, path, strlen(path), 0);
    if (!ce)
        return;

    full_path = g_build_filename (worktree, path, NULL);
    if (seaf_stat (full_path, &st) < 0) {
        seaf_warning ("Failed to stat %s: %s.\n", full_path, strerror(errno));
        g_free (full_path);
        return;
    }

    unsigned int new_mode = create_ce_mode (st.st_mode);
    if (new_mode != ce->ce_mode || st.st_mtime != ce->ce_mtime.sec) {
        ce->ce_mode = new_mode;
        ce->ce_mtime.sec = st.st_mtime;
        istate->cache_changed = 1;
        add_to_changeset (changeset,
                          DIFF_STATUS_MODIFIED,
                          ce->sha1,
                          &st,
                          repo->email,
                          path,
                          NULL);
    }
    g_free (full_path);
}