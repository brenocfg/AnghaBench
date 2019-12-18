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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_open ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int real_open(const char *path, int flags, mode_t mode) {
        /* glibc internally calls openat() when open() is requested. Let's hence define our own wrapper for
         * testing purposes that calls the real syscall, on architectures where SYS_open is defined. On
         * other architectures, let's just fall back to the glibc call. */

#if defined __NR_open && __NR_open > 0
        return (int) syscall(__NR_open, path, flags, mode);
#else
        return open(path, flags, mode);
#endif
}