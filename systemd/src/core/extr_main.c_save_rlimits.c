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
struct rlimit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  assert (struct rlimit*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  log_warning_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void save_rlimits(struct rlimit *saved_rlimit_nofile,
                         struct rlimit *saved_rlimit_memlock) {

        assert(saved_rlimit_nofile);
        assert(saved_rlimit_memlock);

        if (getrlimit(RLIMIT_NOFILE, saved_rlimit_nofile) < 0)
                log_warning_errno(errno, "Reading RLIMIT_NOFILE failed, ignoring: %m");

        if (getrlimit(RLIMIT_MEMLOCK, saved_rlimit_memlock) < 0)
                log_warning_errno(errno, "Reading RLIMIT_MEMLOCK failed, ignoring: %m");
}