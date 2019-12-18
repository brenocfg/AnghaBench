#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
struct TYPE_6__ {scalar_t__ sec; } ;
struct cache_entry {TYPE_1__ ce_mtime; } ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {int /*<<< orphan*/  message; } ;
struct TYPE_7__ {scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__ SeafStat ;
typedef  TYPE_3__ GError ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_NORMALIZE_NFC ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_path (char*,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char const*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_rmdir (char const*) ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 struct cache_entry* index_name_exists (struct index_state*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_built_in_ignored_file (char*) ; 
 scalar_t__ lstat (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_message (char*,char*) ; 
 scalar_t__ seaf_util_unlink (char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
delete_worktree_dir_recursive (struct index_state *istate,
                               const char *path,
                               const char *full_path)
{
    GDir *dir;
    const char *dname;
    char *dname_nfc;
    GError *error = NULL;
    char *sub_path, *full_sub_path;
    SeafStat st;
    int ret = 0;
    gboolean builtin_ignored = FALSE;

    dir = g_dir_open (full_path, 0, &error);
    if (!dir) {
        seaf_warning ("Failed to open dir %s: %s.\n", full_path, error->message);
        return -1;
    }

    while ((dname = g_dir_read_name (dir)) != NULL) {
        dname_nfc = g_utf8_normalize (dname, -1, G_NORMALIZE_NFC);
        sub_path = g_build_path ("/", path, dname_nfc, NULL);
        full_sub_path = g_build_path ("/", full_path, dname_nfc, NULL);
        builtin_ignored = is_built_in_ignored_file (dname_nfc);
        g_free (dname_nfc);

        if (lstat (full_sub_path, &st) < 0) {
            seaf_warning ("Failed to stat %s.\n", full_sub_path);
            g_free (sub_path);
            g_free (full_sub_path);
            ret = -1;
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            if (delete_worktree_dir_recursive (istate, sub_path, full_sub_path) < 0)
                ret = -1;
        } else {
            struct cache_entry *ce;
            /* Files like .DS_Store and Thumbs.db should be deleted any way. */
            if (!builtin_ignored) {
                ce = index_name_exists (istate, sub_path, strlen(sub_path), 0);
                if (!ce || ce->ce_mtime.sec != st.st_mtime) {
                    seaf_message ("File %s is changed, skip deleting it.\n", full_sub_path);
                    g_free (sub_path);
                    g_free (full_sub_path);
                    ret = -1;
                    continue;
                }
            }

            /* Delete all other file types. */
            if (seaf_util_unlink (full_sub_path) < 0) {
                seaf_warning ("Failed to delete file %s: %s.\n",
                              full_sub_path, strerror(errno));
                ret = -1;
            }
        }

        g_free (sub_path);
        g_free (full_sub_path);
    }

    g_dir_close (dir);

    if (ret < 0)
        return ret;

    if (g_rmdir (full_path) < 0) {
        seaf_warning ("Failed to delete dir %s: %s.\n", full_path, strerror(errno));
        ret = -1;
    }

    return ret;
}