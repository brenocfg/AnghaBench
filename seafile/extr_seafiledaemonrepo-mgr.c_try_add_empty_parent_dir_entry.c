#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  SeafStat ;

/* Variables and functions */
 int /*<<< orphan*/  add_empty_dir_to_index_with_check (struct index_state*,char*,int /*<<< orphan*/ *) ; 
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_dirname (char const*) ; 
 int /*<<< orphan*/ * index_name_exists (struct index_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_stat (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
try_add_empty_parent_dir_entry (const char *worktree,
                                struct index_state *istate,
                                const char *path)
{
    if (index_name_exists (istate, path, strlen(path), 0) != NULL)
        return;

    char *parent_dir = g_path_get_dirname (path);

    /* Parent dir is the worktree dir. */
    if (strcmp (parent_dir, ".") == 0) {
        g_free (parent_dir);
        return;
    }

    char *full_dir = g_build_filename (worktree, parent_dir, NULL);
    SeafStat st;
    if (seaf_stat (full_dir, &st) < 0) {
        goto out;
    }

    add_empty_dir_to_index_with_check (istate, parent_dir, &st);

out:
    g_free (parent_dir);
    g_free (full_dir);
}