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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ getpid_cached () ; 
 scalar_t__ parse_pid (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  program_invocation_short_name ; 
 scalar_t__ streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_us(const char *identifier, const char *pid) {
        pid_t pid_num;

        if (!identifier || !pid)
                return false;

        if (parse_pid(pid, &pid_num) < 0)
                return false;

        return pid_num == getpid_cached() &&
               streq(identifier, program_invocation_short_name);
}