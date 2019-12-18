#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_5__ {int /*<<< orphan*/  buttons; } ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Button ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACTION_REMOVE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  button_free (int /*<<< orphan*/ *) ; 
 int button_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  button_set_seat (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ device_for_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashmap_get (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ isempty (char const*) ; 
 int manager_add_button (TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 

int manager_process_button_device(Manager *m, sd_device *d) {
        const char *sysname;
        Button *b;
        int r;

        assert(m);

        r = sd_device_get_sysname(d, &sysname);
        if (r < 0)
                return r;

        if (device_for_action(d, DEVICE_ACTION_REMOVE)) {

                b = hashmap_get(m->buttons, sysname);
                if (!b)
                        return 0;

                button_free(b);

        } else {
                const char *sn;

                r = manager_add_button(m, sysname, &b);
                if (r < 0)
                        return r;

                if (sd_device_get_property_value(d, "ID_SEAT", &sn) < 0 || isempty(sn))
                        sn = "seat0";

                button_set_seat(b, sn);

                r = button_open(b);
                if (r < 0) /* event device doesn't have any keys or switches relevant to us? (or any other error
                            * opening the device?) let's close the button again. */
                        button_free(b);
        }

        return 0;
}