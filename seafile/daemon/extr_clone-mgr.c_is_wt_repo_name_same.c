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
typedef  int gboolean ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_basename (char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static gboolean
is_wt_repo_name_same (const char *worktree, const char *repo_name)
{
    char *basename = g_path_get_basename (worktree);
    gboolean ret = FALSE;
    ret = (strcmp (basename, repo_name) == 0);
    g_free (basename);
    return ret;
}