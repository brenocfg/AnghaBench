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

/* Variables and functions */
 int VIRTUALIZATION_NONE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int detect_virtualization () ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * virtualization_to_string (int) ; 

__attribute__((used)) static int property_get_virtualization(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        int v;

        assert(bus);
        assert(reply);

        v = detect_virtualization();

        /* Make sure to return the empty string when we detect no virtualization, as that is the API.
         *
         * https://github.com/systemd/systemd/issues/1423
         */

        return sd_bus_message_append(
                        reply, "s",
                        v == VIRTUALIZATION_NONE ? NULL : virtualization_to_string(v));
}