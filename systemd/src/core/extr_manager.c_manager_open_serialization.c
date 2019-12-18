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
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int open_serialization_fd (char*) ; 
 int /*<<< orphan*/  safe_close (int) ; 

int manager_open_serialization(Manager *m, FILE **_f) {
        int fd;
        FILE *f;

        assert(_f);

        fd = open_serialization_fd("systemd-state");
        if (fd < 0)
                return fd;

        f = fdopen(fd, "w+");
        if (!f) {
                safe_close(fd);
                return -errno;
        }

        *_f = f;
        return 0;
}