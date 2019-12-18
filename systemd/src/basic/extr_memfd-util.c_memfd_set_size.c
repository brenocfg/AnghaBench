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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 

int memfd_set_size(int fd, uint64_t sz) {
        int r;

        assert(fd >= 0);

        r = ftruncate(fd, sz);
        if (r < 0)
                return -errno;

        return 0;
}