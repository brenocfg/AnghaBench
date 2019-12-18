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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  __NR_keyctl ; 
 int /*<<< orphan*/  errno ; 
 long syscall (int /*<<< orphan*/ ,int,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline long missing_keyctl(int cmd, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5) {
#  if defined __NR_keyctl && __NR_keyctl > 0
        return syscall(__NR_keyctl, cmd, arg2, arg3, arg4, arg5);
#  else
        errno = ENOSYS;
        return -1;
#  endif

#  define keyctl missing_keyctl
}