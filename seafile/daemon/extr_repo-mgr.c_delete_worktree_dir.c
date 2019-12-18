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
typedef  char wchar_t ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_REMOVE_UNCOMMITTED_FOLDER ; 
 int /*<<< orphan*/  delete_worktree_dir_recursive (struct index_state*,char const*,char*) ; 
 int /*<<< orphan*/  delete_worktree_dir_recursive_win32 (struct index_state*,char const*,char*) ; 
 char* g_build_path (char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ move_dir_to_recycle_bin (char*) ; 
 int /*<<< orphan*/  send_file_sync_error_notification (char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 char* win32_long_path (char*) ; 

__attribute__((used)) static void
delete_worktree_dir (const char *repo_id,
                     const char *repo_name,
                     struct index_state *istate,
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

    /* If for some reason the dir cannot be removed, try to move it to a trash folder
     * under Seafile folder. Otherwise the removed folder will be created agian on the
     * server, which will confuse the users.
     */
    if (g_file_test (full_path, G_FILE_TEST_EXISTS)) {
        if (move_dir_to_recycle_bin (full_path) == 0)
            send_file_sync_error_notification (repo_id, repo_name, path,
                                               SYNC_ERROR_ID_REMOVE_UNCOMMITTED_FOLDER);
    }

    g_free (full_path);
}