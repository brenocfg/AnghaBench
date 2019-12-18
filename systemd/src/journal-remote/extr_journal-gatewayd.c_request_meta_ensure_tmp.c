#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tmp; } ;
typedef  TYPE_1__ RequestMeta ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 scalar_t__ fdopen (int,char*) ; 
 int open_tmpfile_unlinkable (char*,int) ; 
 int /*<<< orphan*/  rewind (scalar_t__) ; 
 int /*<<< orphan*/  safe_close (int) ; 

__attribute__((used)) static int request_meta_ensure_tmp(RequestMeta *m) {
        assert(m);

        if (m->tmp)
                rewind(m->tmp);
        else {
                int fd;

                fd = open_tmpfile_unlinkable("/tmp", O_RDWR|O_CLOEXEC);
                if (fd < 0)
                        return fd;

                m->tmp = fdopen(fd, "w+");
                if (!m->tmp) {
                        safe_close(fd);
                        return -errno;
                }
        }

        return 0;
}