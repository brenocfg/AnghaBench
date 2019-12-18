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
typedef  char const* sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 scalar_t__ LOG_INFO ; 
 scalar_t__ LOG_PRI (unsigned int) ; 
 scalar_t__ arg_quiet ; 
 int /*<<< orphan*/  assert (char const**) ; 
 int /*<<< orphan*/  bus_log_parse_error (int) ; 
 int /*<<< orphan*/  log_full (unsigned int,char*,char const*) ; 
 int /*<<< orphan*/  sd_bus_message_get_path (char const**) ; 
 int sd_bus_message_read (char const**,char*,unsigned int*,char const**) ; 
 int /*<<< orphan*/  streq_ptr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_log_message(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        const char **our_path = userdata, *line;
        unsigned priority;
        int r;

        assert(m);
        assert(our_path);

        r = sd_bus_message_read(m, "us", &priority, &line);
        if (r < 0) {
                bus_log_parse_error(r);
                return 0;
        }

        if (!streq_ptr(*our_path, sd_bus_message_get_path(m)))
                return 0;

        if (arg_quiet && LOG_PRI(priority) >= LOG_INFO)
                return 0;

        log_full(priority, "%s", line);
        return 0;
}