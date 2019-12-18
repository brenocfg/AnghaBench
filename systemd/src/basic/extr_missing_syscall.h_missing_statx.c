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
struct statx {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  __NR_statx ; 
 int /*<<< orphan*/  errno ; 
 int syscall (int /*<<< orphan*/ ,int,char const*,unsigned int,unsigned int,struct statx*) ; 

__attribute__((used)) static inline ssize_t missing_statx(int dfd, const char *filename, unsigned flags, unsigned int mask, struct statx *buffer) {
#  ifdef __NR_statx
        return syscall(__NR_statx, dfd, filename, flags, mask, buffer);
#  else
        errno = ENOSYS;
        return -1;
#  endif
}