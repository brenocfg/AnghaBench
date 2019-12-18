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
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int) ; 

void close_and_munmap(int fd, void *address, size_t size) {
        if (size > 0)
                assert_se(munmap(address, PAGE_ALIGN(size)) >= 0);

        safe_close(fd);
}