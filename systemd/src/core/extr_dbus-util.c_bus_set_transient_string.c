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
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int UnitWriteFlags ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int UNIT_ESCAPE_SPECIFIERS ; 
 int /*<<< orphan*/  UNIT_WRITE_FLAGS_NOOP (int) ; 
 int /*<<< orphan*/  assert (char**) ; 
 int /*<<< orphan*/  empty_to_null (char const*) ; 
 int free_and_strdup (char**,int /*<<< orphan*/ ) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  strempty (char const*) ; 
 int /*<<< orphan*/  unit_write_settingf (int /*<<< orphan*/ *,int,char const*,char*,char const*,int /*<<< orphan*/ ) ; 

int bus_set_transient_string(
                Unit *u,
                const char *name,
                char **p,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        const char *v;
        int r;

        assert(p);

        r = sd_bus_message_read(message, "s", &v);
        if (r < 0)
                return r;

        if (!UNIT_WRITE_FLAGS_NOOP(flags)) {
                r = free_and_strdup(p, empty_to_null(v));
                if (r < 0)
                        return r;

                unit_write_settingf(u, flags|UNIT_ESCAPE_SPECIFIERS, name,
                                    "%s=%s", name, strempty(v));
        }

        return 1;
}