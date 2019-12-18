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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  UnitWriteFlags ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int /*<<< orphan*/  UNIT_WRITE_FLAGS_NOOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int /*<<< orphan*/  asynchronous_close (int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static int bus_set_transient_std_fd(
                Unit *u,
                const char *name,
                int *p,
                bool *b,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        int fd, r;

        assert(p);
        assert(b);

        r = sd_bus_message_read(message, "h", &fd);
        if (r < 0)
                return r;

        if (!UNIT_WRITE_FLAGS_NOOP(flags)) {
                int copy;

                copy = fcntl(fd, F_DUPFD_CLOEXEC, 3);
                if (copy < 0)
                        return -errno;

                asynchronous_close(*p);
                *p = copy;
                *b = true;
        }

        return 1;
}