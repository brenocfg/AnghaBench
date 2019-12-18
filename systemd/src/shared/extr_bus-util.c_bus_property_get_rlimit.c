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
struct rlimit {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
typedef  scalar_t__ rlim_t ;

/* Variables and functions */
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 char* endswith (char const*,char*) ; 
 int /*<<< orphan*/  getrlimit (int,struct rlimit*) ; 
 int rlimit_from_string (char const*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char const* strndupa (char const*,int) ; 
 char* strstr (char const*,char*) ; 

int bus_property_get_rlimit(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        const char *is_soft;
        struct rlimit *rl;
        uint64_t u;
        rlim_t x;

        assert(bus);
        assert(reply);
        assert(userdata);

        is_soft = endswith(property, "Soft");

        rl = *(struct rlimit**) userdata;
        if (rl)
                x = is_soft ? rl->rlim_cur : rl->rlim_max;
        else {
                struct rlimit buf = {};
                const char *s, *p;
                int z;

                /* Chop off "Soft" suffix */
                s = is_soft ? strndupa(property, is_soft - property) : property;

                /* Skip over any prefix, such as "Default" */
                assert_se(p = strstr(s, "Limit"));

                z = rlimit_from_string(p + 5);
                assert(z >= 0);

                (void) getrlimit(z, &buf);
                x = is_soft ? buf.rlim_cur : buf.rlim_max;
        }

        /* rlim_t might have different sizes, let's map RLIMIT_INFINITY to (uint64_t) -1, so that it is the same on all
         * archs */
        u = x == RLIM_INFINITY ? (uint64_t) -1 : (uint64_t) x;

        return sd_bus_message_append(reply, "t", u);
}