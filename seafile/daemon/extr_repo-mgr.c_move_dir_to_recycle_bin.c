#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  worktree_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  SEAFILE_RECYCLE_BIN_FOLDER ; 
 scalar_t__ checkdir_with_mkdir (char*) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_basename (char const*) ; 
 char* g_strdup_printf (char*,char*,int) ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*,char const*,char*) ; 
 scalar_t__ seaf_util_rename (char const*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
move_dir_to_recycle_bin (const char *dir_path)
{
    char *trash_folder = g_build_path ("/", seaf->worktree_dir, SEAFILE_RECYCLE_BIN_FOLDER, NULL);
    if (checkdir_with_mkdir (trash_folder) < 0) {
        seaf_warning ("Seafile trash folder %s doesn't exist and cannot be created.\n",
                      trash_folder);
        g_free (trash_folder);
        return -1;
    }
    g_free (trash_folder);

    char *basename = g_path_get_basename (dir_path);
    char *dst_path = g_build_path ("/", seaf->worktree_dir, SEAFILE_RECYCLE_BIN_FOLDER, basename, NULL);
    int ret = 0;

    int n;
    char *tmp_path;
    for (n = 1; n < 10; ++n) {
        if (g_file_test (dst_path, G_FILE_TEST_EXISTS)) {
            tmp_path = g_strdup_printf ("%s(%d)", dst_path, n);
            g_free (dst_path);
            dst_path = tmp_path;
            continue;
        }
        break;
    }

    if (seaf_util_rename (dir_path, dst_path) < 0) {
        seaf_warning ("Failed to move %s to Seafile recycle bin %s: %s\n",
                      dir_path, dst_path, strerror(errno));
        ret = -1;
        goto out;
    }

    seaf_message ("Moved folder %s to Seafile recyle bin %s.\n",
                  dir_path, dst_path);

out:
    g_free (basename);
    g_free (dst_path);
    return ret;
}