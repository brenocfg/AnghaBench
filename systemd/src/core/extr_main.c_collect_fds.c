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
typedef  char const FDSet ;

/* Variables and functions */
 scalar_t__ arg_serialization ; 
 int /*<<< orphan*/  assert (char const**) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  fdset_cloexec (char const*,int) ; 
 int fdset_new_fill (char const**) ; 
 scalar_t__ fdset_remove (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (scalar_t__) ; 
 int log_emergency_errno (int,char*) ; 

__attribute__((used)) static int collect_fds(FDSet **ret_fds, const char **ret_error_message) {
        int r;

        assert(ret_fds);
        assert(ret_error_message);

        r = fdset_new_fill(ret_fds);
        if (r < 0) {
                *ret_error_message = "Failed to allocate fd set";
                return log_emergency_errno(r, "Failed to allocate fd set: %m");
        }

        fdset_cloexec(*ret_fds, true);

        if (arg_serialization)
                assert_se(fdset_remove(*ret_fds, fileno(arg_serialization)) >= 0);

        return 0;
}