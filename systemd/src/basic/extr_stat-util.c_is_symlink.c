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

/* Variables and functions */
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 scalar_t__ lstat (char const*,struct stat*) ; 

int is_symlink(const char *path) {
        struct stat info;

        assert(path);

        if (lstat(path, &info) < 0)
                return -errno;

        return !!S_ISLNK(info.st_mode);
}