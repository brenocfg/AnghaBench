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
typedef  scalar_t__ UnitFileChangeType ;
typedef  int /*<<< orphan*/  UnitFileChange ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_TYPE_ARRAY ; 
 int /*<<< orphan*/  assert (size_t*) ; 
 int bus_log_parse_error (int) ; 
 int /*<<< orphan*/  log_notice (char*,char const*,char const*) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**,char const**) ; 
 scalar_t__ unit_file_change_type_from_string (char const*) ; 
 int unit_file_changes_add (int /*<<< orphan*/ **,size_t*,scalar_t__,char const*,char const*) ; 
 int /*<<< orphan*/  unit_file_dump_changes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 

int bus_deserialize_and_dump_unit_file_changes(sd_bus_message *m, bool quiet, UnitFileChange **changes, size_t *n_changes) {
        const char *type, *path, *source;
        int r;

        /* changes is dereferenced when calling unit_file_dump_changes() later,
         * so we have to make sure this is not NULL. */
        assert(changes);
        assert(n_changes);

        r = sd_bus_message_enter_container(m, SD_BUS_TYPE_ARRAY, "(sss)");
        if (r < 0)
                return bus_log_parse_error(r);

        while ((r = sd_bus_message_read(m, "(sss)", &type, &path, &source)) > 0) {
                /* We expect only "success" changes to be sent over the bus.
                   Hence, reject anything negative. */
                UnitFileChangeType ch = unit_file_change_type_from_string(type);

                if (ch < 0) {
                        log_notice("Manager reported unknown change type \"%s\" for path \"%s\", ignoring.", type, path);
                        continue;
                }

                r = unit_file_changes_add(changes, n_changes, ch, path, source);
                if (r < 0)
                        return r;
        }
        if (r < 0)
                return bus_log_parse_error(r);

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return bus_log_parse_error(r);

        unit_file_dump_changes(0, NULL, *changes, *n_changes, quiet);
        return 0;
}