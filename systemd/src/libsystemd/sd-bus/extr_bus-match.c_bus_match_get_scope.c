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
struct bus_match_component {scalar_t__ type; int /*<<< orphan*/  value_str; } ;
typedef  enum bus_match_scope { ____Placeholder_bus_match_scope } bus_match_scope ;

/* Variables and functions */
 int BUS_MATCH_DRIVER ; 
 int BUS_MATCH_GENERIC ; 
 scalar_t__ BUS_MATCH_INTERFACE ; 
 int BUS_MATCH_LOCAL ; 
 scalar_t__ BUS_MATCH_PATH ; 
 scalar_t__ BUS_MATCH_SENDER ; 
 int /*<<< orphan*/  assert (struct bus_match_component const*) ; 
 scalar_t__ streq_ptr (int /*<<< orphan*/ ,char*) ; 

enum bus_match_scope bus_match_get_scope(const struct bus_match_component *components, unsigned n_components) {
        bool found_driver = false;
        unsigned i;

        if (n_components <= 0)
                return BUS_MATCH_GENERIC;

        assert(components);

        /* Checks whether the specified match can only match the
         * pseudo-service for local messages, which we detect by
         * sender, interface or path. If a match is not restricted to
         * local messages, then we check if it only matches on the
         * driver. */

        for (i = 0; i < n_components; i++) {
                const struct bus_match_component *c = components + i;

                if (c->type == BUS_MATCH_SENDER) {
                        if (streq_ptr(c->value_str, "org.freedesktop.DBus.Local"))
                                return BUS_MATCH_LOCAL;

                        if (streq_ptr(c->value_str, "org.freedesktop.DBus"))
                                found_driver = true;
                }

                if (c->type == BUS_MATCH_INTERFACE && streq_ptr(c->value_str, "org.freedesktop.DBus.Local"))
                        return BUS_MATCH_LOCAL;

                if (c->type == BUS_MATCH_PATH && streq_ptr(c->value_str, "/org/freedesktop/DBus/Local"))
                        return BUS_MATCH_LOCAL;
        }

        return found_driver ? BUS_MATCH_DRIVER : BUS_MATCH_GENERIC;

}