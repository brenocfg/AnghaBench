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
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  SPECIAL_GLYPH_ARROW ; 
 scalar_t__ arg_quiet ; 
 int bus_log_parse_error (int) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_error (char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*,...) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,char,char*) ; 
 int sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**,char const**) ; 
 int /*<<< orphan*/  special_glyph (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int print_changes(sd_bus_message *m) {
        int r;

        if (arg_quiet)
                return 0;

        r = sd_bus_message_enter_container(m, 'a', "(sss)");
        if (r < 0)
                return bus_log_parse_error(r);

        for (;;) {
                const char *type, *path, *source;

                r = sd_bus_message_read(m, "(sss)", &type, &path, &source);
                if (r < 0)
                        return bus_log_parse_error(r);
                if (r == 0)
                        break;

                if (streq(type, "symlink"))
                        log_info("Created symlink %s %s %s.", path, special_glyph(SPECIAL_GLYPH_ARROW), source);
                else if (streq(type, "copy")) {
                        if (isempty(source))
                                log_info("Copied %s.", path);
                        else
                                log_info("Copied %s %s %s.", source, special_glyph(SPECIAL_GLYPH_ARROW), path);
                } else if (streq(type, "unlink"))
                        log_info("Removed %s.", path);
                else if (streq(type, "write"))
                        log_info("Written %s.", path);
                else if (streq(type, "mkdir"))
                        log_info("Created directory %s.", path);
                else
                        log_error("Unexpected change: %s/%s/%s", type, path, source);
        }

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        return 0;
}