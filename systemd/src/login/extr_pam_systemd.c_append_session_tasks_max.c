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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  pam_syslog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int safe_atou64 (char const*,int /*<<< orphan*/ *) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,char*) ; 
 char const* strerror_safe (int) ; 

__attribute__((used)) static int append_session_tasks_max(pam_handle_t *handle, sd_bus_message *m, const char *limit) {
        uint64_t val;
        int r;

        /* No need to parse "infinity" here, it will be set unconditionally later in manager_start_scope() */
        if (isempty(limit) || streq(limit, "infinity"))
                return 0;

        r = safe_atou64(limit, &val);
        if (r >= 0) {
                r = sd_bus_message_append(m, "(sv)", "TasksMax", "t", val);
                if (r < 0) {
                        pam_syslog(handle, LOG_ERR, "Failed to append to bus message: %s", strerror_safe(r));
                        return r;
                }
        } else
                pam_syslog(handle, LOG_WARNING, "Failed to parse systemd.tasks_max: %s, ignoring.", limit);

        return 0;
}