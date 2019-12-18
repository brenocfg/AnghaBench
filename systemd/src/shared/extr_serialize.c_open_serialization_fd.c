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
 int /*<<< orphan*/  MFD_CLOEXEC ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int getpid_cached () ; 
 int /*<<< orphan*/  log_debug (char*,char const*,...) ; 
 int memfd_create (char const*,int /*<<< orphan*/ ) ; 
 int open_tmpfile_unlinkable (char const*,int) ; 

int open_serialization_fd(const char *ident) {
        int fd;

        fd = memfd_create(ident, MFD_CLOEXEC);
        if (fd < 0) {
                const char *path;

                path = getpid_cached() == 1 ? "/run/systemd" : "/tmp";
                fd = open_tmpfile_unlinkable(path, O_RDWR|O_CLOEXEC);
                if (fd < 0)
                        return fd;

                log_debug("Serializing %s to %s.", ident, path);
        } else
                log_debug("Serializing %s to memfd.", ident);

        return fd;
}