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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  scalar_t__ SeafPathPerm ;

/* Variables and functions */
 scalar_t__ SEAF_PATH_PERM_RO ; 
 scalar_t__ SEAF_PATH_PERM_RW ; 
 int /*<<< orphan*/  S_IWUSR ; 
 scalar_t__ chmod (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
seaf_set_path_permission (const char *path, SeafPathPerm perm, gboolean recursive)
{
    struct stat st;
    mode_t new_mode;

    if (stat (path, &st) < 0) {
        seaf_warning ("Failed to stat %s: %s\n", path, strerror(errno));
        return -1;
    }

    new_mode = st.st_mode;
    if (perm == SEAF_PATH_PERM_RO)
        new_mode &= ~(S_IWUSR);
    else if (perm == SEAF_PATH_PERM_RW)
        new_mode |= S_IWUSR;

    if (chmod (path, new_mode) < 0) {
        seaf_warning ("Failed to chmod %s to %d: %s\n", path, new_mode, strerror(errno));
        return -1;
    }

    return 0;
}