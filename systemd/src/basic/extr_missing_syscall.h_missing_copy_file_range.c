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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  __NR_copy_file_range ; 
 int /*<<< orphan*/  errno ; 
 int syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,unsigned int) ; 

__attribute__((used)) static inline ssize_t missing_copy_file_range(int fd_in, loff_t *off_in,
                                              int fd_out, loff_t *off_out,
                                              size_t len,
                                              unsigned int flags) {
#  ifdef __NR_copy_file_range
        return syscall(__NR_copy_file_range, fd_in, off_in, fd_out, off_out, len, flags);
#  else
        errno = ENOSYS;
        return -1;
#  endif
}