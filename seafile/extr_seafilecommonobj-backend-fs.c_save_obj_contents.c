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
typedef  scalar_t__ gboolean ;

/* Variables and functions */
 int SEAF_PATH_MAX ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fsync_obj_contents (int) ; 
 int g_mkstemp (char*) ; 
 scalar_t__ g_rename (char*,char const*) ; 
 scalar_t__ rename_and_sync (char*,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ writen (int,void const*,int) ; 

__attribute__((used)) static int
save_obj_contents (const char *path, const void *data, int len, gboolean need_sync)
{
    char tmp_path[SEAF_PATH_MAX];
    int fd;

    snprintf (tmp_path, SEAF_PATH_MAX, "%s.XXXXXX", path);
    fd = g_mkstemp (tmp_path);
    if (fd < 0) {
        seaf_warning ("[obj backend] Failed to open tmp file %s: %s.\n",
                      tmp_path, strerror(errno));
        return -1;
    }

    if (writen (fd, data, len) < 0) {
        seaf_warning ("[obj backend] Failed to write obj %s: %s.\n",
                      tmp_path, strerror(errno));
        return -1;
    }

    if (need_sync && fsync_obj_contents (fd) < 0)
        return -1;

    /* Close may return error, especially in NFS. */
    if (close (fd) < 0) {
        seaf_warning ("[obj backend Failed close obj %s: %s.\n",
                      tmp_path, strerror(errno));
        return -1;
    }

    if (need_sync) {
        if (rename_and_sync (tmp_path, path) < 0)
            return -1;
    } else {
        if (g_rename (tmp_path, path) < 0) {
            seaf_warning ("[obj backend] Failed to rename %s: %s.\n",
                          path, strerror(errno));
            return -1;
        }
    }

    return 0;
}