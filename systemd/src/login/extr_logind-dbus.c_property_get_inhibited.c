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
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  InhibitWhat ;

/* Variables and functions */
 int /*<<< orphan*/  INHIBIT_BLOCK ; 
 int /*<<< orphan*/  INHIBIT_DELAY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inhibit_what_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_inhibit_what (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int property_get_inhibited(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        InhibitWhat w;

        assert(bus);
        assert(reply);
        assert(m);

        w = manager_inhibit_what(m, streq(property, "BlockInhibited") ? INHIBIT_BLOCK : INHIBIT_DELAY);

        return sd_bus_message_append(reply, "s", inhibit_what_to_string(w));
}