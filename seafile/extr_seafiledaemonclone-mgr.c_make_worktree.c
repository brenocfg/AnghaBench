#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  int /*<<< orphan*/  SeafCloneManager ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_GENERAL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ is_worktree_of_repo (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  remove_trail_slash (char*) ; 
 int seaf_stat (char*,TYPE_1__*) ; 
 char* try_worktree (char*) ; 

__attribute__((used)) static char *
make_worktree (SeafCloneManager *mgr,
               const char *worktree,
               gboolean dry_run,
               GError **error)
{
    char *wt = g_strdup (worktree);
    SeafStat st;
    int rc;
    char *ret;

    remove_trail_slash (wt);

    rc = seaf_stat (wt, &st);
    if (rc < 0) {
        ret = wt;
        return ret;
    } else if (!S_ISDIR(st.st_mode)) {
        if (!dry_run) {
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                         "Invalid local directory");
            g_free (wt);
            return NULL;
        }
        ret = try_worktree (wt);
        g_free (wt);
        return ret;
    }

    /* OK, wt is an existing dir. Let's see if it's the worktree for
     * another repo. */
    if (is_worktree_of_repo (mgr, wt)) {
        if (!dry_run) {
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                         "Already in sync");
            g_free (wt);
            return NULL;
        }
        ret = try_worktree (wt);
        g_free (wt);
    } else {
        return wt;
    }

    return ret;
}