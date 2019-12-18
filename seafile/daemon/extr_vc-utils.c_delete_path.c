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
typedef  scalar_t__ gint64 ;
struct TYPE_3__ {scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;

/* Variables and functions */
 int SEAF_PATH_MAX ; 
 int /*<<< orphan*/  S_ISDIR (unsigned int) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  is_eml_file (char const*) ; 
 scalar_t__ seaf_remove_empty_dir (char*) ; 
 scalar_t__ seaf_stat (char*,TYPE_1__*) ; 
 scalar_t__ seaf_util_unlink (char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int
delete_path (const char *worktree, const char *name,
             unsigned int mode, gint64 old_mtime)
{
    char path[SEAF_PATH_MAX];
    SeafStat st;
    int len = strlen(name);

    if (!len) {
        seaf_warning ("entry name should not be empty.\n");
        return -1;
    }

    snprintf (path, SEAF_PATH_MAX, "%s/%s", worktree, name);

    if (!S_ISDIR(mode)) {
        /* file doesn't exist in work tree */
        if (seaf_stat (path, &st) < 0 || !S_ISREG(st.st_mode)) {
            return 0;
        }

        /* file has been changed. */
        if (!is_eml_file (name) && (old_mtime != st.st_mtime)) {
            seaf_warning ("File %s is changed. Skip removing the file.\n", path);
            return -1;
        }

        /* first unlink the file. */
        if (seaf_util_unlink (path) < 0) {
            seaf_warning ("Failed to remove %s: %s.\n", path, strerror(errno));
            return -1;
        }
    } else {
        if (seaf_remove_empty_dir (path) < 0) {
            seaf_warning ("Failed to remove dir %s: %s.\n", path, strerror(errno));
            return -1;
        }
    }

    /* then remove all empty directories upwards. */
    /* offset = base_len + len; */
    /* do { */
    /*     if (path[offset] == '/') { */
    /*         path[offset] = '\0'; */
    /*         int ret = seaf_remove_empty_dir (path); */
    /*         if (ret < 0) { */
    /*             break; */
    /*         } */
    /*     } */
    /* } while (--offset > base_len); */

    return 0;
}