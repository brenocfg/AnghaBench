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

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MOVEFILE_REPLACE_EXISTING ; 
 int MOVEFILE_WRITE_THROUGH ; 
 int /*<<< orphan*/  MoveFileExW (char*,char*,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fsync (int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_dirname (char const*) ; 
 char* g_utf8_to_utf16 (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rename (char const*,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int
rename_and_sync (const char *tmp_path, const char *obj_path)
{
#ifdef __linux__
    char *parent_dir;
    int ret = 0;

    if (rename (tmp_path, obj_path) < 0) {
        seaf_warning ("Failed to rename from %s to %s: %s.\n",
                      tmp_path, obj_path, strerror(errno));
        return -1;
    }

    parent_dir = g_path_get_dirname (obj_path);
    int dir_fd = open (parent_dir, O_RDONLY);
    if (dir_fd < 0) {
        seaf_warning ("Failed to open dir %s: %s.\n", parent_dir, strerror(errno));
        goto out;
    }

    /* Some file systems don't support fsyncing a directory. Just ignore the error.
     */
    if (fsync (dir_fd) < 0) {
        if (errno != EINVAL) {
            seaf_warning ("Failed to fsync dir %s: %s.\n",
                          parent_dir, strerror(errno));
            ret = -1;
        }
        goto out;
    }

out:
    g_free (parent_dir);
    if (dir_fd >= 0)
        close (dir_fd);
    return ret;
#endif

#ifdef __APPLE__
    /*
     * OS X garantees an existence of obj_path always exists,
     * even when the system crashes.
     */
    if (rename (tmp_path, obj_path) < 0) {
        seaf_warning ("Failed to rename from %s to %s: %s.\n",
                      tmp_path, obj_path, strerror(errno));
        return -1;
    }
    return 0;
#endif

#ifdef WIN32
    wchar_t *w_tmp_path = g_utf8_to_utf16 (tmp_path, -1, NULL, NULL, NULL);
    wchar_t *w_obj_path = g_utf8_to_utf16 (obj_path, -1, NULL, NULL, NULL);
    int ret = 0;

    if (!MoveFileExW (w_tmp_path, w_obj_path,
                      MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        seaf_warning ("MoveFilExW failed: %lu.\n", GetLastError());
        ret = -1;
        goto out;
    }

out:
    g_free (w_tmp_path);
    g_free (w_obj_path);
    return ret;
#endif
}