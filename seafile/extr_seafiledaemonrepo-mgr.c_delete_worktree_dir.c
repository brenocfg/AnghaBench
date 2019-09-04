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

/* Variables and functions */
 int /*<<< orphan*/  delete_worktree_dir_recursive (struct index_state*,char const*,char*) ; 
 char* g_build_path (char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 

__attribute__((used)) static void
delete_worktree_dir (struct index_state *istate,
                     const char *worktree,
                     const char *path)
{
    char *full_path = g_build_path ("/", worktree, path, NULL);

#ifdef WIN32
    wchar_t *full_path_w = win32_long_path (full_path);
    delete_worktree_dir_recursive_win32 (istate, path, full_path_w);
    g_free (full_path_w);
#else
    delete_worktree_dir_recursive(istate, path, full_path);
#endif

    g_free (full_path);
}