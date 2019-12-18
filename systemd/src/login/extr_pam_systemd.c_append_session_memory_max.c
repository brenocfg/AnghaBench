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
typedef  unsigned int uint64_t ;
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 unsigned int UINT32_MAX ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  pam_syslog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int parse_permille (char const*) ; 
 int parse_size (char const*,int,unsigned int*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,unsigned int) ; 
 scalar_t__ streq (char const*,char*) ; 
 char const* strerror_safe (int) ; 

__attribute__((used)) static int append_session_memory_max(pam_handle_t *handle, sd_bus_message *m, const char *limit) {
        uint64_t val;
        int r;

        if (isempty(limit))
                return 0;

        if (streq(limit, "infinity")) {
                r = sd_bus_message_append(m, "(sv)", "MemoryMax", "t", (uint64_t)-1);
                if (r < 0) {
                        pam_syslog(handle, LOG_ERR, "Failed to append to bus message: %s", strerror_safe(r));
                        return r;
                }
        } else {
                r = parse_permille(limit);
                if (r >= 0) {
                        r = sd_bus_message_append(m, "(sv)", "MemoryMaxScale", "u", (uint32_t) (((uint64_t) r * UINT32_MAX) / 1000U));
                        if (r < 0) {
                                pam_syslog(handle, LOG_ERR, "Failed to append to bus message: %s", strerror_safe(r));
                                return r;
                        }
                } else {
                        r = parse_size(limit, 1024, &val);
                        if (r >= 0) {
                                r = sd_bus_message_append(m, "(sv)", "MemoryMax", "t", val);
                                if (r < 0) {
                                        pam_syslog(handle, LOG_ERR, "Failed to append to bus message: %s", strerror_safe(r));
                                        return r;
                                }
                        } else
                                pam_syslog(handle, LOG_WARNING, "Failed to parse systemd.memory_max: %s, ignoring.", limit);
                }
        }

        return 0;
}