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
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 

int is_dir_fd(int fd) {
        struct stat st;

        if (fstat(fd, &st) < 0)
                return -errno;

        return !!S_ISDIR(st.st_mode);
}