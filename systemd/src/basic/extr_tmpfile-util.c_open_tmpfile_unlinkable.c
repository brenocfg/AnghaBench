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

/* Variables and functions */
 int EINVAL ; 
 int O_EXCL ; 
 int O_TMPFILE ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 scalar_t__ isempty (char const*) ; 
 int mkostemp_safe (char*) ; 
 int open (char const*,int,int) ; 
 char* strjoina (char const*,char*) ; 
 int tmp_dir (char const**) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int open_tmpfile_unlinkable(const char *directory, int flags) {
        char *p;
        int fd, r;

        if (!directory) {
                r = tmp_dir(&directory);
                if (r < 0)
                        return r;
        } else if (isempty(directory))
                return -EINVAL;

        /* Returns an unlinked temporary file that cannot be linked into the file system anymore */

        /* Try O_TMPFILE first, if it is supported */
        fd = open(directory, flags|O_TMPFILE|O_EXCL, S_IRUSR|S_IWUSR);
        if (fd >= 0)
                return fd;

        /* Fall back to unguessable name + unlinking */
        p = strjoina(directory, "/systemd-tmp-XXXXXX");

        fd = mkostemp_safe(p);
        if (fd < 0)
                return fd;

        (void) unlink(p);

        return fd;
}