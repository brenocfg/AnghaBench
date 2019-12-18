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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 scalar_t__ copy_file_range (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,unsigned int) ; 
 scalar_t__ errno ; 

__attribute__((used)) static ssize_t try_copy_file_range(
                int fd_in, loff_t *off_in,
                int fd_out, loff_t *off_out,
                size_t len,
                unsigned flags) {

        static int have = -1;
        ssize_t r;

        if (have == 0)
                return -ENOSYS;

        r = copy_file_range(fd_in, off_in, fd_out, off_out, len, flags);
        if (have < 0)
                have = r >= 0 || errno != ENOSYS;
        if (r < 0)
                return -errno;

        return r;
}