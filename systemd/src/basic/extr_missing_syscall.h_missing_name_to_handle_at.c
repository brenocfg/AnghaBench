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
struct file_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  __NR_name_to_handle_at ; 
 int /*<<< orphan*/  errno ; 
 int syscall (int /*<<< orphan*/ ,int,char const*,struct file_handle*,int*,int) ; 

__attribute__((used)) static inline int missing_name_to_handle_at(int fd, const char *name, struct file_handle *handle, int *mnt_id, int flags) {
#  ifdef __NR_name_to_handle_at
        return syscall(__NR_name_to_handle_at, fd, name, handle, mnt_id, flags);
#  else
        errno = ENOSYS;
        return -1;
#  endif
}