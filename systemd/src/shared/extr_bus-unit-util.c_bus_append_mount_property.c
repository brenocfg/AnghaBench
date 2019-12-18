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
 scalar_t__ STR_IN_SET (char const*,char*,char*,char*,...) ; 
 int bus_append_parse_boolean (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_parse_mode (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_parse_sec_rename (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int bus_append_mount_property(sd_bus_message *m, const char *field, const char *eq) {

        if (STR_IN_SET(field, "What", "Where", "Options", "Type"))
                return bus_append_string(m, field, eq);

        if (streq(field, "TimeoutSec"))
                return bus_append_parse_sec_rename(m, field, eq);

        if (streq(field, "DirectoryMode"))
                return bus_append_parse_mode(m, field, eq);

        if (STR_IN_SET(field, "SloppyOptions", "LazyUnmount", "ForceUnmount"))
                return bus_append_parse_boolean(m, field, eq);

        return 0;
}