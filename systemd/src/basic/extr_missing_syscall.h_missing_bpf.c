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
typedef  union bpf_attr {int dummy; } bpf_attr ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  __NR_bpf ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int,union bpf_attr*,size_t) ; 

__attribute__((used)) static inline int missing_bpf(int cmd, union bpf_attr *attr, size_t size) {
#ifdef __NR_bpf
        return (int) syscall(__NR_bpf, cmd, attr, size);
#else
        errno = ENOSYS;
        return -1;
#endif
}