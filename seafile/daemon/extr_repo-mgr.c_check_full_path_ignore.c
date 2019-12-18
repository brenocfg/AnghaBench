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
typedef  size_t guint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* g_build_path (char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char** g_strsplit (char const*,char*,int /*<<< orphan*/ ) ; 
 size_t g_strv_length (char**) ; 
 scalar_t__ seaf_repo_check_ignore_file (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ should_ignore (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
check_full_path_ignore (const char *worktree, const char *path, GList *ignore_list)
{
    char **tokens;
    guint i;
    guint n;
    gboolean ret = FALSE;

    tokens = g_strsplit (path, "/", 0);
    n = g_strv_length (tokens);
    for (i = 0; i < n; ++i) {
        /* don't check ignore_list */
        if (should_ignore (NULL, tokens[i], ignore_list)) {
            ret = TRUE;
            goto out;
        }
    }

    char *full_path = g_build_path ("/", worktree, path, NULL);
    if (seaf_repo_check_ignore_file (ignore_list, full_path))
        ret = TRUE;
    g_free (full_path);

out:
    g_strfreev (tokens);
    return ret;
}