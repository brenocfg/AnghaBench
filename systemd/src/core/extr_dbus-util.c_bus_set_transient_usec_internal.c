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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ts ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  UnitWriteFlags ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  UNIT_WRITE_FLAGS_NOOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_timespan (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 char* strndupa (char const*,scalar_t__) ; 
 int /*<<< orphan*/  unit_write_settingf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*,char*,int /*<<< orphan*/ ) ; 

int bus_set_transient_usec_internal(
                Unit *u,
                const char *name,
                usec_t *p,
                bool fix_0,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        uint64_t v;
        int r;

        assert(p);

        r = sd_bus_message_read(message, "t", &v);
        if (r < 0)
                return r;

        if (!UNIT_WRITE_FLAGS_NOOP(flags)) {
                char *n, ts[FORMAT_TIMESPAN_MAX];

                if (fix_0)
                        *p = v != 0 ? v: USEC_INFINITY;
                else
                        *p = v;

                n = strndupa(name, strlen(name) - 4);
                unit_write_settingf(u, flags, name, "%sSec=%s", n,
                                    format_timespan(ts, sizeof(ts), v, USEC_PER_MSEC));
        }

        return 1;
}