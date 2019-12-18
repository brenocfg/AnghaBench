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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  le64_t ;
typedef  int /*<<< orphan*/  le ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ fsetxattr (int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 

int fd_setcrtime(int fd, usec_t usec) {
        le64_t le;

        assert(fd >= 0);

        if (IN_SET(usec, 0, USEC_INFINITY))
                usec = now(CLOCK_REALTIME);

        le = htole64((uint64_t) usec);
        if (fsetxattr(fd, "user.crtime_usec", &le, sizeof(le), 0) < 0)
                return -errno;

        return 0;
}