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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int getpid_cached () ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 

int fd_warn_permissions(const char *path, int fd) {
        struct stat st;

        if (fstat(fd, &st) < 0)
                return -errno;

        /* Don't complain if we are reading something that is not a file, for example /dev/null */
        if (!S_ISREG(st.st_mode))
                return 0;

        if (st.st_mode & 0111)
                log_warning("Configuration file %s is marked executable. Please remove executable permission bits. Proceeding anyway.", path);

        if (st.st_mode & 0002)
                log_warning("Configuration file %s is marked world-writable. Please remove world writability permission bits. Proceeding anyway.", path);

        if (getpid_cached() == 1 && (st.st_mode & 0044) != 0044)
                log_warning("Configuration file %s is marked world-inaccessible. This has no effect as configuration data is accessible via APIs without restrictions. Proceeding anyway.", path);

        return 0;
}