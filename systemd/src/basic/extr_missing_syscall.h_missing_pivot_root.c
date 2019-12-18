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
 int /*<<< orphan*/  __NR_pivot_root ; 
 int syscall (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static inline int missing_pivot_root(const char *new_root, const char *put_old) {
        return syscall(__NR_pivot_root, new_root, put_old);
}