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
 int cg_weight_parse (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  pam_syslog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,char*) ; 
 char const* strerror_safe (int) ; 

__attribute__((used)) static int append_session_cg_weight(pam_handle_t *handle, sd_bus_message *m, const char *limit, const char *field) {
        uint64_t val;
        int r;

        if (isempty(limit))
                return 0;

        r = cg_weight_parse(limit, &val);
        if (r >= 0) {
                r = sd_bus_message_append(m, "(sv)", field, "t", val);
                if (r < 0) {
                        pam_syslog(handle, LOG_ERR, "Failed to append to bus message: %s", strerror_safe(r));
                        return r;
                }
        } else if (streq(field, "CPUWeight"))
                pam_syslog(handle, LOG_WARNING, "Failed to parse systemd.cpu_weight: %s, ignoring.", limit);
        else
                pam_syslog(handle, LOG_WARNING, "Failed to parse systemd.io_weight: %s, ignoring.", limit);

        return 0;
}