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
typedef  scalar_t__ usec_t ;
struct stat {int /*<<< orphan*/  st_mtim; } ;

/* Variables and functions */
 scalar_t__ PATH_STARTSWITH_SET (char const*,char*,char*) ; 
 int /*<<< orphan*/  null_or_empty (struct stat*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ timespec_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fragment_mtime_newer(const char *path, usec_t mtime, bool path_masked) {
        struct stat st;

        if (!path)
                return false;

        /* If the source is some virtual kernel file system, then we assume we watch it anyway, and hence pretend we
         * are never out-of-date. */
        if (PATH_STARTSWITH_SET(path, "/proc", "/sys"))
                return false;

        if (stat(path, &st) < 0)
                /* What, cannot access this anymore? */
                return true;

        if (path_masked)
                /* For masked files check if they are still so */
                return !null_or_empty(&st);
        else
                /* For non-empty files check the mtime */
                return timespec_load(&st.st_mtim) > mtime;

        return false;
}