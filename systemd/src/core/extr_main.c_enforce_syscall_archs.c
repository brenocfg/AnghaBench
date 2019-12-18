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
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int /*<<< orphan*/  arg_syscall_archs ; 
 int /*<<< orphan*/  is_seccomp_available () ; 
 int log_error_errno (int,char*) ; 
 int seccomp_restrict_archs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enforce_syscall_archs(Set *archs) {
#if HAVE_SECCOMP
        int r;

        if (!is_seccomp_available())
                return 0;

        r = seccomp_restrict_archs(arg_syscall_archs);
        if (r < 0)
                return log_error_errno(r, "Failed to enforce system call architecture restrication: %m");
#endif
        return 0;
}